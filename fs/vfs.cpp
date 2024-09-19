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

#include <nos/string.hpp>
#include <nos/printk.hpp>
#include <nos/panic.hpp>
#include <nos/types.hpp>
#include <nos/vfs.hpp>


namespace kernel {
namespace fs {

static vfs_t vfs;

void vfs_init(fs_type_t type, vfs_adapter_t *fs_adapter)
{
    vfs_register(type, fs_adapter);
}

void vfs_register(fs_type_t type, vfs_adapter_t *fs_adapter)
{
    switch (type) {
        
        case fs_type_t::INITRD:
            lib::kmesg(true, "VFS: set filesystem %d (INITRD)\n", type);
            break;

        case fs_type_t::EXT2:
            lib::kmesg(true, "VFS: set filesystem %d (EXT2)\n", type);
            break;
        
        default:
            lib::kmesg(false, "Unknown file system: %d\n", type);
            lib::panic("%s\n", "VFS error");
            break;
    };

    lib::bzero(&vfs, sizeof(vfs_t));

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

} // namespace fs
} // namespace kernel