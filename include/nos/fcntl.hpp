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

#ifndef _NOS_KERNEL_FCNTL_HPP_
#define _NOS_KERNEL_FCNTL_HPP_


namespace kernel {
namespace fs {

/* file open flags */
#define O_RDONLY  0x000 ///< open for read only.
#define O_WRONLY  0x001 ///< open for write only.
#define O_RDWR	  0x002 ///< open for read & write.
#define O_CREAT	  0x040 ///< create a file.
/* file will only be created if it does not already exist. */
#define O_EXCL	  0x080 ///< create a file exclusively (in conjunction with O_CREAT).
#define O_APPEND  0x400 ///< open for writing in the end of the file.

} // namespace fs
} // namespace kernel

#endif /* _NOS_KERNEL_FCNTL_HPP_ */