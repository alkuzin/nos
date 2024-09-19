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

/**
 * @file  stat.hpp
 * @brief File statistics.
 * 
 * @details Provides functions and structures for obtaining file status information, 
 * such as file size, permissions, and etc.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   09.06.2024
 */

#ifndef _KERNEL_FS_STAT_HPP_
#define _KERNEL_FS_STAT_HPP_

#include <kernel/kstd/types.hpp>


namespace kernel {
namespace fs {

constexpr u32 MAX_FILENAME_SIZE {64};
constexpr u32 MAX_PATH_SIZE     {64};


enum class f_type {
    S_IFMT   = 0xF000, // Bits that determine file type.
    S_IFIFO  = 0x1000, // FIFO.
    S_IFCHR  = 0x2000, // Character device.
    S_IFDIR  = 0x4000, // Directory.
    S_IFBLK  = 0x6000, // Block device.
    S_IFREG  = 0x8000, // Regular file.
    S_IFLNK  = 0xA000, // Symbolic link.
    S_IFSOCK = 0xC000  // Unix socket.
};

enum class f_perm {
    S_IRUSR = 0x100, // User—read permission.
    S_IWUSR = 0x080, // User—write permission.
    S_IXUSR = 0x040, // User—execute permission.
    S_IRGRP = 0x020, // Group—read permission.
    S_IWGRP = 0x010, // Group—write permission.
    S_IXGRP = 0x008, // Group—execute permission.
    S_IROTH = 0x004, // Other—read permission.
    S_IWOTH = 0x002, // Other—write permission.
    S_IXOTH = 0x001  // Other—execute permission.
};

struct stat_t {
    char    name[MAX_FILENAME_SIZE]; ///< Name of the file.
    u32     size;     ///< Size of the file in bytes.
    mode_t  mode;     ///< File permissions.
    s32     fd;       ///< File descriptor.
    u32     type;     ///< File type.
};
    
} // namespace fs
} // namespace kernel

#endif // _KERNEL_FS_STAT_HPP_