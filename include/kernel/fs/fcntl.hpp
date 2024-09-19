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
 * @file  fcntl.hpp
 * @brief File control options.
 * 
 * @details Provides functions for performing file control operations on open files.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   09.06.2024
 */

#ifndef _KERNEL_FS_FCNTL_HPP_
#define _KERNEL_FS_FCNTL_HPP_

namespace kernel {
namespace fs {

/* @brief File open flags enumeration.*/
enum class f_oflags {
    O_RDONLY = 0x000, // Open for read only.
    O_WRONLY = 0x001, // Open for write only.
    O_RDWR	 = 0x002, // Open for read & write.
    O_CREAT	 = 0x040, // Create a file.
    O_EXCL	 = 0x080, // Create a file exclusively (in conjunction with O_CREAT).
    O_APPEND = 0x400  // Open for writing in the end of the file.
};

} // namespace fs
} // namespace kernel

#endif // _KERNEL_FS_FCNTL_HPP_