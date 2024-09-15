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
 * @file  errno.hpp
 * @brief Contains kernel errors enumeration.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   27.06.2024
 */

#ifndef _NOS_KERNEL_ERRNO_HPP_
#define _NOS_KERNEL_ERRNO_HPP_

#include <nos/types.hpp>

namespace kernel {
namespace error {

extern s32 errno;

enum class ERRNO : s32 {
    E2BIG		  = 1,   // Arg list too long.
    EACCES		  = 2,   // Permission denied.
    EAGAIN		  = 3,   // Try again.
    EBADF		  = 4,   // Bad file number.
    EBUSY		  = 5,   // Device or resource busy.
    ECHILD		  = 6,   // No child processes.
    EDEADLK		  = 7,   // Resource deadlock would occur.
    EDOM		  = 8,   // Math argument out of domain of func.
    EEXIST		  = 9,   // File exists.
    EFAULT		  = 10,  // Bad address.
    EFBIG		  = 11,  // File too large.
    EINTR		  = 12,  // Interrupted system call.
    EINVAL		  = 13,  // Invalid argument.
    EIO		      = 14,  // I/O error.
    EISDIR		  = 15,  // Is a directory.
    EMFILE		  = 16,  // Too many open files.
    EMLINK		  = 17,  // Too many links.
    ENAMETOOLONG  = 18,  // File name too long.
    ENFILE		  = 19,  // File table overflow.
    ENODEV		  = 20,  // No such device.
    ENOENT		  = 21,  // No such file or directory.
    ENOEXEC		  = 22,  // Exec format error.
    ENOLCK		  = 23,  // No record locks available.
    ENOMEM		  = 24,  // Out of memory.
    ENOSPC		  = 25,  // No space left on device.
    ENOSYS		  = 26,  // Function not implemented.
    ENOTDIR		  = 27,  // Not a directory.
    ENOTEMPTY	  = 28,  // Directory not empty.
    ENOTTY		  = 29,  // Not a typewriter.
    ENXIO		  = 30,  // No such device or address.
    EPERM		  = 31,  // Operation not permitted.
    EPIPE		  = 32,  // Broken pipe.
    ERANGE		  = 33,  // Math result not representable.
    EROFS		  = 34,  // Read-only file system.
    ESPIPE		  = 35,  // Illegal seek.
    ESRCH		  = 36,  // No such process.
    EXDEV		  = 37   // Cross-device link.
};
} // namespace error
} // namespace kernel

#endif /* _NOS_KERNEL_ERRNO_HPP_ */