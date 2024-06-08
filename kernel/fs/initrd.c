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
#include <nos/vfs.h>

static vfs_adapter_t initrd_adapter;
static initrd_t      initrd;


void initrd_init(void)
{
    initrd.files = (initrd_file_t *)kmalloc(sizeof(initrd_file_t) * INITRD_MAX_FILES);

    if (!initrd.files)
        panic("%s\n", "kmalloc error");

    initrd.count = 0;

    initrd_adapter.open   = nullptr;
    initrd_adapter.close  = nullptr;
    initrd_adapter.creat  = initrd_creat;
    initrd_adapter.unlink = initrd_unlink;
    initrd_adapter.read   = nullptr;
    initrd_adapter.write  = initrd_write;
    
    initrd_creat("temp.tmp", 0);
    initrd_creat("program.c", 0);
    initrd_creat("README.md", 0);
    
    initrd_write(0, "Hello, World!", 14);

    printk(" data: \"%s\"\n", initrd.files[0].data);
    
    // TODO: VFS mount initrd
}

void initrd_ls(void)
{
    for (u32 i = 0; i < initrd.count; i++) {
        printk(" %s (%u bytes)\n", initrd.files[i].name, initrd.files[i].size);
    }

    printk(" \n total files: %u/%u\n", initrd.count, INITRD_MAX_FILES);
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
    if (!pathname || initrd_is_path(pathname) != -1)
        return -1; /* file creation error */

    file = &initrd.files[initrd.count];

    strncpy(file->name, pathname, INITRD_MAX_NAME_SIZE);
    bzero(file->data, INITRD_FILE_SIZE);
    file->size = 0;
    file->mode = mode;
    
    return initrd.count++;
}

s32 initrd_unlink(const char* pathname)
{
    s32 fd;

    /* handle missing files */
    if (initrd.count == 0)
        return -1; /* file unlink error */

    fd = initrd_is_path(pathname);

    /* handle incorrect path/non existed path */
    if (fd == -1)
        return -1; /* file unlink error */

    bzero(initrd.files[fd].data, INITRD_FILE_SIZE);

    /* shift remaining files to fill the gap */
    for (u32 j = fd; j < initrd.count - 1; j++)
        initrd.files[j] = initrd.files[j + 1];

    initrd.count--;    
    return 0;
}

s32 initrd_is_path(const char *pathname)
{
    /* handle incorrect path */
    if (!pathname)
        return -1;

    for (u32 i = 0; i < initrd.count; i++) {
        if (strncmp(initrd.files[i].name, pathname, INITRD_FILE_SIZE) == 0)
            return i;
    }
    
    return -1;
}

s32 initrd_write(s32 fd, void *buf, usize count)
{
    u8    *buffer;
    usize i;

    /* handle incorrect file descriptor */
    if (fd < 0 || (u32)fd >= initrd.count)
        return -1;
    
    buffer = (u8 *)buf;

    if (!buffer)
        return -1;

    i = 0;

    while (initrd.files[fd].data[i])
        i++;

    while (i < count - 1 && i < INITRD_FILE_SIZE) {
        initrd.files[fd].data[i] = buffer[i];
        i++;
    }
    
    initrd.files[fd].data[i] = '\0';
    initrd.files[fd].size += (i + 1);

    return i;
}

vfs_adapter_t *initrd_get_adapter(void)
{
    return &initrd_adapter;
}