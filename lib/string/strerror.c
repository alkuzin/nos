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
#include <nos/errno.h>


char *strerror(s32 errnum)
{
    switch (errnum) {
        case E2BIG:
            return "Arg list too long";
        case EACCES:
            return "Permission denied";
        case EAGAIN:
            return "Try again";
        case EBADF:
            return "Bad file number";
        case EBUSY:
            return "Device or resource busy";
        case ECHILD:
            return "No child processes";
        case EDEADLK:
            return "Resource deadlock would occur";
        case EDOM:
            return "Math argument out of domain of func";
        case EEXIST:
            return "File exists";
        case EFAULT:
            return "Bad address";
        case EFBIG:
            return "File too large";
        case EINTR:
            return "Interrupted system call";
        case EINVAL:
            return "Invalid argument";
        case EIO:
            return "I/O error";
        case EISDIR:
            return "Is a directory";
        case EMFILE:
            return "Too many open files";
        case EMLINK:
            return "Too many links";
        case ENAMETOOLONG:
            return "File name too long";
        case ENFILE:
            return "File table overflow";
        case ENODEV:
            return "No such device";
        case ENOENT:
            return "No such file or directory";
        case ENOEXEC:
            return "Exec format error";
        case ENOLCK:
            return "No record locks available";
        case ENOMEM:
            return "Out of memory";
        case ENOSPC:
            return "No space left on device";
        case ENOSYS:
            return "Function not implemented";
        case ENOTDIR:
            return "Not a directory";
        case ENOTEMPTY:
            return "Directory not empty";
        case ENOTTY:
            return "Not a typewriter";
        case ENXIO:
            return "No such device or address";
        case EPERM:
            return "Operation not permitted";
        case EPIPE:
            return "Broken pipe";
        case ERANGE:
            return "Math result not representable";
        case EROFS:
            return "Read-only file system";
        case ESPIPE:
            return "Illegal seek";
        case ESRCH:
            return "No such process";
        case EXDEV:
            return "Cross-device link";
        default:
            return "Unknown error";
    }
}