/**
 * The Null Operating System (NOS).
 * Copyright (C) 2024  Alexander (@alkuzin).
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <kernel/kstd/cstdlib.hpp>
#include <kernel/kstd/cstring.hpp>
#include <kernel/fs/initrd.hpp>
#include <kernel/kstd/cstdio.hpp>
#include <kernel/kstd/types.hpp>
#include <kernel/fs/vfs.hpp>


namespace kernel {
namespace fs {
namespace initrd {

static vfs::fs_adapter  initrd_adapter; ///< Initrd adapter for VFS.
static initrd_t _initrd;         ///< Main initrd structure.
static u8               *initrd_buffer; ///< Temporary buffer for file operations.
static s32              initrd_next_fd;
static u32              cur_file_index; /* for initrd_opendir() */


void init(void)
{
    _initrd.files = (file *)kstd::kmalloc(sizeof(file) * INITRD_MAX_FILES);

    if (!_initrd.files)
        kstd::panic("%s\n", "kmalloc error");

    initrd_next_fd = 0;
    _initrd.count  = 0;

    initrd_adapter.open   = open;
    initrd_adapter.close  = close;
    initrd_adapter.creat  = creat;
    initrd_adapter.unlink = unlink;
    initrd_adapter.read   = read;
    initrd_adapter.write  = write;
}

void free(void)
{
    kstd::kfree(_initrd.files);
}

s32 creat(const char* pathname, mode_t mode)
{
    file *file;
    
    /* handle exceeding total files limit */
    if (_initrd.count + 1 > INITRD_MAX_FILES)
        return -1; /* file creation error */

    /* handle incorrect path/existed path */
    if (!pathname || get_index(pathname) != -1)
        return -1; /* file creation error */

    file = &_initrd.files[_initrd.count];

    kstd::strncpy(file->name, pathname, INITRD_MAX_NAME_SIZE);
    kstd::bzero(file->data, INITRD_FILE_SIZE);
    file->size  = 0;
    file->mode  = mode;
    file->type  = S_IFREG;
    file->fd    = set_fd();
    file->flags = 0;

    _initrd.count++;
    return file->fd;
}

s32 unlink(const char* pathname)
{
    file *file;
    s32 file_index; /* index of the file in files structure */
    
    /* handle incorrect path */
    if (!pathname)
        return -1; /* file unlink error */
    
    /* handle missing files */
    if (_initrd.count == 0)
        return -1; /* file unlink error */
    
    file_index = get_index(pathname);
    
    if (file_index == -1)
        return -1; /* file unlink error */

    file = &_initrd.files[file_index];

    if (file->state == INITRD_FILE_OPENED)
        close(file->fd);

    kstd::bzero(file->data, INITRD_FILE_SIZE);

    /* shift remaining files to fill the gap */
    for (u32 j = file_index; j < _initrd.count - 1; j++)
        _initrd.files[j] = _initrd.files[j + 1];

    _initrd.count--;    
    return 0;
}

s32 write(s32 fd, void *buf, usize count)
{
    file *file;
    s32   file_index; /* index of the file in files structure */
    u8    *buffer;
    usize i, j;

    file_index = get_index_by_fd(fd);

    if (file_index == -1)
        return -1; /* file writing error */
    
    file = &_initrd.files[file_index];

    if (file->state == INITRD_FILE_CLOSED)
        return -1; /* error to write into closed file */

    buffer = (u8 *)buf;

    if (!buffer)
        return -1;
    
    /* check if file has write permissions */
    if (!(file->flags | O_RDONLY) || !(file->mode & S_IWUSR))
        return -1; /* no write perrmissions */

    i = 0;
    j = 0;
    
    if (file->flags & O_APPEND) {
        while (initrd_buffer[i])
            i++;
        
        while (j < count && ((i + j) < INITRD_FILE_SIZE - 1)) {
            initrd_buffer[i] = buffer[j];
            i++;
            j++;
        }
    }
    else {
        while (i < count && i < INITRD_FILE_SIZE - 1) {
            initrd_buffer[i] = buffer[i];
            i++;
        }
    }
        
    while (initrd_buffer[i])
        i++;
    
    initrd_buffer[i] = '\0';
    _initrd.files[file_index].size = i - 1;
    return i - 1;
}

s32 read(s32 fd, void *buf, usize count)
{
    file *file;
    s32   file_index; /* index of the file in files structure */
    u8    *buffer;
    usize i;

    file_index = get_index_by_fd(fd);

    if (file_index == -1)
        return -1; /* file reading error */
    
    file = &_initrd.files[file_index];

    if (file->state == INITRD_FILE_CLOSED)
        return -1; /* error to read closed file */

    /* handle incorrect file descriptor */
    if (fd < 0)
        return -1;
    
    buffer = (u8 *)buf;

    if (!buffer)
        return -1;
    
    /* check if file has read permissions */
    if (file->flags & O_WRONLY || !(file->mode & S_IRUSR))
        return -1; /* no read perrmissions */

    i = 0;

    /* cannot read more data than file contain */
    if (count >= INITRD_FILE_SIZE)
        count = INITRD_FILE_SIZE;

    while (initrd_buffer[i] && i < count) {
        buffer[i] = initrd_buffer[i];
        i++;
    }

    buffer[i] = '\0';
    return i;
}

s32 open(const char *pathname, s32 flags)
{
    file *file;
    s32 file_index; /* index of the file in files structure */
    
    /* handle incorrect path */
    if (!pathname)
        return -1; /* file opening error */
    
    file_index = get_index(pathname);
    
    /* create file if it doesn't exist */
    if (file_index == -1) {
        if (flags == (O_CREAT | O_EXCL))
            return creat(pathname, 0);
        else
            return -1;
    }
    
    file = &_initrd.files[file_index];

    if (file->state == INITRD_FILE_OPENED)
        return file->fd;   

    file->state = INITRD_FILE_OPENED;
    file->flags = flags;
    
    initrd_buffer = (u8 *)kstd::kmalloc(INITRD_FILE_SIZE);

    kstd::bzero(initrd_buffer, INITRD_FILE_SIZE);
    kstd::memcpy(initrd_buffer, file->data, file->size);

    return file->fd;
}

s32 close(s32 fd)
{
    file *file;
    s32 file_index; /* index of the file in files structure */

    file_index = get_index_by_fd(fd);
    
    if (file_index == -1)
        return -1; /* file closing error */
    
    file = &_initrd.files[file_index];

    /* handle already closed file */
    if (file->state == INITRD_FILE_CLOSED)
        return -1;
    
    file->state = INITRD_FILE_CLOSED;

    /* copy data from temporary buffer to file */
    for (u32 i = 0; i < INITRD_FILE_SIZE; i++)
        file->data[i] = initrd_buffer[i];

    kstd::kfree(initrd_buffer);
    return 0;
}

s32 get_index(const char *pathname)
{
    /* handle incorrect path */
    if (!pathname)
        return -1; /* get file index error */
    
    for (u32 i = 0; i < _initrd.count; i++) {
        if (kstd::strncmp(_initrd.files[i].name, pathname, INITRD_FILE_SIZE) == 0)
            return i;
    }

    return -1;
}

s32 get_index_by_fd(s32 fd)
{
    /* handle incorrect file descriptor */
    if (fd == -1)
        return -1; /* get file index error */
    
    for (u32 i = 0; i < _initrd.count; i++) {
        if (_initrd.files[i].fd == fd)
            return i;
    }

    return -1;
}

s32 set_fd(void)
{
    return initrd_next_fd++;
}

vfs::fs_adapter *get_adapter(void)
{
    return &initrd_adapter;
}

s32 stat(const char *pathname, stat_t *sb)
{
    file *file;
    s32 file_index; /* index of the file in files structure */
    
    /* handle incorrect path */
    if (!pathname)
        return -1; /* get file stat error */
    
    file_index = get_index(pathname);
    
    if (file_index == -1)
        return -1; /* get file stat error */

    file = &_initrd.files[file_index];

    kstd::strncpy(sb->name, file->name, INITRD_MAX_NAME_SIZE);
    sb->size  = file->size;
    sb->mode  = file->mode;
    sb->type  = file->type;
    sb->fd    = file->fd;

    return 0;
}

u32 get_count(void)
{
    return _initrd.count;
}

s32 opendir(const char *pathname, stat_t *sb)
{
    file *file;
    s32 ret;

    // TODO: remove after implementing directories
    if (kstd::strncmp(".", pathname, 1) != 0) {
        kstd::printk("%s\n", "incorrect path");
        return -1;
    }
    
    if (cur_file_index >= _initrd.count)
        cur_file_index = 0;
    
    file = &_initrd.files[cur_file_index];

    ret = stat(file->name, sb);

    cur_file_index++;
    return ret;
}

} // namespace initrd
} // namespace fs
} // namespace kernel