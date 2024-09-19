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

#include <kernel/kstd/cstring.hpp>
#include <kernel/kstd/cstdio.hpp>
#include <kernel/fs/vfs.hpp>


namespace kernel {
namespace fs {

static vfs::fs_adapter _vfs;

void vfs::init(fs_type type, vfs::fs_adapter *fs_adapter)
{
    vfs::set(type, fs_adapter);
}

void vfs::set(fs_type type, vfs::fs_adapter *fs_adapter)
{
    switch (type) {
        
        case fs_type::INITRD:
            kstd::kmesg(true, "VFS: set filesystem %d (INITRD)\n", type);
            break;

        case fs_type::EXT2:
            kstd::kmesg(true, "VFS: set filesystem %d (EXT2)\n", type);
            break;
        
        default:
            kstd::kmesg(false, "Unknown file system: %d\n", type);
            kstd::panic("%s\n", "VFS error");
            break;
    };

    kstd::bzero(&_vfs, sizeof(vfs::fs_adapter));

    _vfs.open   = fs_adapter->open; 
    _vfs.close  = fs_adapter->close;
    _vfs.read   = fs_adapter->read;
    _vfs.write  = fs_adapter->write;
    _vfs.creat  = fs_adapter->creat;
    _vfs.unlink = fs_adapter->unlink;
}

s32 vfs::open(const char *pathname, s32 flags)
{
    if (!_vfs.open)
        return -1;
    
    return _vfs.open(pathname, flags);
}

s32 vfs::close(s32 fd)
{
    if (!_vfs.close)
        return -1;
    
    return _vfs.close(fd);
}

s32 vfs::read(s32 fd, void *buf, usize count)
{
    if (!_vfs.read)
        return -1;
    
    return _vfs.read(fd, buf, count);
}

s32 vfs::write(s32 fd, void *buf, usize count)
{
    if (!_vfs.write)
        return -1;
    
    return _vfs.write(fd, buf, count);
}

s32 vfs::creat(const char* pathname, mode_t mode)
{
    if (!_vfs.creat)
        return -1;
    
    return _vfs.creat(pathname, mode);
}

s32 vfs::unlink(const char* pathname)
{
    if (!_vfs.unlink)
        return -1;
    
    return _vfs.unlink(pathname);
}

} // namespace fs
} // namespace kernel