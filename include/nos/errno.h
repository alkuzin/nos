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

/**
 * @file  errno.h
 * @brief Contains macros of kernel errors.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   27.06.2024
 */

#ifndef _NOS_KERNEL_ERRNO_H_
#define _NOS_KERNEL_ERRNO_H_

#include <nos/types.h>

extern s32 errno;

#define	E2BIG		  1     /** Arg list too long. */
#define	EACCES		  2     /** Permission denied. */
#define	EAGAIN		  3     /** Try again. */
#define	EBADF		  4     /** Bad file number. */
#define	EBUSY		  5     /** Device or resource busy. */
#define	ECHILD		  6     /** No child processes. */
#define	EDEADLK		  7     /** Resource deadlock would occur. */
#define	EDOM		  8     /** Math argument out of domain of func. */
#define	EEXIST		  9     /** File exists. */
#define	EFAULT		  10    /** Bad address. */
#define	EFBIG		  11    /** File too large. */
#define	EINTR		  12    /** Interrupted system call. */
#define	EINVAL		  13    /** Invalid argument. */
#define	EIO		      14    /** I/O error. */
#define	EISDIR		  15    /** Is a directory. */
#define	EMFILE		  16    /** Too many open files. */
#define	EMLINK		  17    /** Too many links. */
#define	ENAMETOOLONG  18    /** File name too long. */
#define	ENFILE		  19    /** File table overflow. */
#define	ENODEV		  20    /** No such device. */
#define	ENOENT		  21    /** No such file or directory. */
#define	ENOEXEC		  22    /** Exec format error. */
#define	ENOLCK		  23    /** No record locks available. */
#define	ENOMEM		  24    /** Out of memory. */
#define	ENOSPC		  25    /** No space left on device. */
#define	ENOSYS		  26    /** Function not implemented. */
#define	ENOTDIR		  27    /** Not a directory. */
#define	ENOTEMPTY	  28    /** Directory not empty. */
#define	ENOTTY		  29    /** Not a typewriter. */
#define	ENXIO		  30    /** No such device or address. */
#define	EPERM		  31    /** Operation not permitted. */
#define	EPIPE		  32    /** Broken pipe. */
#define	ERANGE		  33    /** Math result not representable. */
#define	EROFS		  34    /** Read-only file system. */
#define	ESPIPE		  35    /** Illegal seek. */
#define	ESRCH		  36    /** No such process. */
#define	EXDEV		  37    /** Cross-device link. */

#endif /* _NOS_KERNEL_ERRNO_H_ */