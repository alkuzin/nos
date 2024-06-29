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

#include <nos/string.h>
#include <nos/printk.h>
#include <nos/panic.h>
#include <nos/types.h>
#include <nos/vfs.h>


static vfs_t vfs;

void vfs_init(fs_type_t type, vfs_adapter_t *fs_adapter)
{
    vfs_register(type, fs_adapter);
}

void vfs_register(fs_type_t type, vfs_adapter_t *fs_adapter)
{
    switch (type) {
        
        case INITRD:
            kmesg(true, "VFS: set filesystem %d (INITRD)\n", type);
            break;

        case EXT2:
            kmesg(true, "VFS: set filesystem %d (EXT2)\n", type);
            break;
        
        default:
            kmesg(false, "Unknown file system: %d\n", type);
            panic("%s\n", "VFS error");
            break;
    };

    bzero(&vfs, sizeof(vfs_t));

    vfs.open   = fs_adapter->open; 
    vfs.close  = fs_adapter->close;
    vfs.read   = fs_adapter->read;
    vfs.write  = fs_adapter->write;
    vfs.creat  = fs_adapter->creat;
    vfs.unlink = fs_adapter->unlink;
}

s32 vfs_open(const char *pathname, s32 flags)
{
    if (!vfs.open)
        return -1;
    
    return vfs.open(pathname, flags);
}

s32 vfs_close(s32 fd)
{
    if (!vfs.close)
        return -1;
    
    return vfs.close(fd);
}

s32 vfs_read(s32 fd, void *buf, usize count)
{
    if (!vfs.read)
        return -1;
    
    return vfs.read(fd, buf, count);
}

s32 vfs_write(s32 fd, void *buf, usize count)
{
    if (!vfs.write)
        return -1;
    
    return vfs.write(fd, buf, count);
}

s32 vfs_creat(const char* pathname, mode_t mode)
{
    if (!vfs.creat)
        return -1;
    
    return vfs.creat(pathname, mode);
}

s32 vfs_unlink(const char* pathname)
{
    if (!vfs.unlink)
        return -1;
    
    return vfs.unlink(pathname);
}