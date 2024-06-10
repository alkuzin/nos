/* MIT License
 *
 * Copyright (c) 2024 Alexander (@alkuzin)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. */

#include <string.h>

#include <nos/nosstd.h>
#include <nos/kernel.h>
#include <nos/initrd.h>
#include <nos/types.h>
#include <nos/fcntl.h>
#include <nos/stat.h>
#include <nos/vfs.h>

static vfs_adapter_t initrd_adapter; ///< Initrd adapter for VFS.
static initrd_t      initrd;         ///< Main initrd structure.
static u8            *initrd_buffer; ///< Temporary buffer for file operations.
static s32           initrd_next_fd;


void initrd_init(void)
{
    initrd.files = (initrd_file_t *)kmalloc(sizeof(initrd_file_t) * INITRD_MAX_FILES);

    if (!initrd.files)
        panic("%s\n", "kmalloc error");

    initrd_next_fd = 0;
    initrd.count   = 0;

    initrd_adapter.open   = initrd_open;
    initrd_adapter.close  = initrd_close;
    initrd_adapter.creat  = initrd_creat;
    initrd_adapter.unlink = initrd_unlink;
    initrd_adapter.read   = initrd_read;
    initrd_adapter.write  = initrd_write;
}

void initrd_free(void)
{
    kfree(initrd.files);
}

s32 initrd_creat(const char* pathname, mode_t mode)
{
    initrd_file_t *file;
    
    /* handle exceeding total files limit */
    if (initrd.count + 1 > INITRD_MAX_FILES)
        return -1; /* file creation error */

    /* handle incorrect path/existed path */
    if (!pathname || initrd_get_index(pathname) != -1)
        return -1; /* file creation error */

    file = &initrd.files[initrd.count];

    strncpy(file->name, pathname, INITRD_MAX_NAME_SIZE);
    bzero(file->data, INITRD_FILE_SIZE);
    file->size  = 0;
    file->mode  = mode;
    file->type  = S_IFREG;
    file->fd    = initrd_set_fd();
    file->flags = 0;

    initrd.count++;
    return file->fd;
}

s32 initrd_unlink(const char* pathname)
{
    initrd_file_t *file;
    s32 file_index; /* index of the file in files structure */
    
    /* handle incorrect path */
    if (!pathname)
        return -1; /* file opening error */
    
    /* handle missing files */
    if (initrd.count == 0)
        return -1; /* file unlink error */
    
    file_index = initrd_get_index(pathname);
    
    if (file_index == -1)
        return -1; /* file unlink error */

    file = &initrd.files[file_index];

    if (file->state == INITRD_FILE_OPENED)
        initrd_close(file->fd);

    bzero(file->data, INITRD_FILE_SIZE);

    /* shift remaining files to fill the gap */
    for (u32 j = file_index; j < initrd.count - 1; j++)
        initrd.files[j] = initrd.files[j + 1];

    initrd.count--;    
    return 0;
}

s32 initrd_write(s32 fd, void *buf, usize count)
{
    initrd_file_t *file;
    s32   file_index; /* index of the file in files structure */
    u8    *buffer;
    usize i, j;

    file_index = initrd_get_index_by_fd(fd);

    if (file_index == -1)
        return -1; /* file writing error */
    
    file = &initrd.files[file_index];

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
    initrd.files[file_index].size = i - 1;
    return i - 1;
}

s32 initrd_read(s32 fd, void *buf, usize count)
{
    initrd_file_t *file;
    s32   file_index; /* index of the file in files structure */
    u8    *buffer;
    usize i;

    file_index = initrd_get_index_by_fd(fd);

    if (file_index == -1)
        return -1; /* file reading error */
    
    file = &initrd.files[file_index];

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

s32 initrd_open(const char *pathname, s32 flags)
{
    initrd_file_t *file;
    s32 file_index; /* index of the file in files structure */
    
    /* handle incorrect path */
    if (!pathname)
        return -1; /* file opening error */
    
    file_index = initrd_get_index(pathname);
    
    /* create file if it doesn't exist */
    if (file_index == -1) {
        if (flags == (O_CREAT | O_EXCL))
            return initrd_creat(pathname, 0);
        else
            return -1;
    }
    
    file = &initrd.files[file_index];

    if (file->state == INITRD_FILE_OPENED)
        return file->fd;   

    file->state = INITRD_FILE_OPENED;
    file->flags = flags;
    
    initrd_buffer = (u8 *)kmalloc(INITRD_FILE_SIZE);

    memcpy(initrd_buffer, file->data, file->size);

    return file->fd;
}

s32 initrd_close(s32 fd)
{
    initrd_file_t *file;
    s32 file_index; /* index of the file in files structure */

    file_index = initrd_get_index_by_fd(fd);
    
    if (file_index == -1)
        return -1; /* file opening error */
    
    file = &initrd.files[file_index];

    /* handle already closed file */
    if (file->state == INITRD_FILE_CLOSED)
        return -1;
    
    file->state = INITRD_FILE_CLOSED;

    /* copy data from temporary buffer to file */
    for (u32 i = 0; i < INITRD_FILE_SIZE; i++)
        file->data[i] = initrd_buffer[i];

    kfree(initrd_buffer);
    return 0;
}

s32 initrd_get_index(const char *pathname)
{
    /* handle incorrect path */
    if (!pathname)
        return -1; /* get file index error */
    
    for (u32 i = 0; i < initrd.count; i++) {
        if (strncmp(initrd.files[i].name, pathname, INITRD_FILE_SIZE) == 0)
            return i;
    }

    return -1;
}

s32 initrd_get_index_by_fd(s32 fd)
{
    /* handle incorrect file descriptor */
    if (fd == -1)
        return -1; /* get file index error */
    
    for (u32 i = 0; i < initrd.count; i++) {
        if (initrd.files[i].fd == fd)
            return i;
    }

    return -1;
}

s32 initrd_set_fd(void)
{
    return initrd_next_fd++;
}

void initrd_ls(void)
{
    for (u32 i = 0; i < initrd.count; i++) {
        printk(" fd: %d  %s (%u bytes)\n", initrd.files[i].fd, initrd.files[i].name, initrd.files[i].size);
    }

    printk(" \n total files: %u/%u\n", initrd.count, INITRD_MAX_FILES);
}

vfs_adapter_t *initrd_get_adapter(void)
{
    return &initrd_adapter;
}