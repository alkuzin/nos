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
 * @file  fcntl.h
 * @brief File control options.
 * 
 * @details Provides functions for performing file control operations on open files.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   09.06.2024
 */

#ifndef _NOS_KERNEL_FCNTL_H_
#define _NOS_KERNEL_FCNTL_H_

/* file open flags */
#define O_RDONLY  0x000 ///< open for read only.
#define O_WRONLY  0x001 ///< open for write only.
#define O_RDWR	  0x002 ///< open for read & write.
#define O_CREAT	  0x040 ///< create a file.
/* file will only be created if it does not already exist. */
#define O_EXCL	  0x080 ///< create a file exclusively (in conjunction with O_CREAT).
#define O_APPEND  0x400 ///< open for writing in the end of the file.

#endif /* _NOS_KERNEL_FCNTL_H_ */