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
 * @file  stat.h
 * @brief File statistics.
 * 
 * @details Provides functions and structures for obtaining file status information, 
 * such as file size, permissions, and etc.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   09.06.2024
 */

#ifndef _NOS_KERNEL_STAT_H_
#define _NOS_KERNEL_STAT_H_

#include <nos/types.h>

/** @brief File types. */
#define S_IFMT   0xF000 ///< Bits that determine file type.
#define S_IFIFO  0x1000 ///< FIFO.
#define S_IFCHR  0x2000 ///< Character device.
#define S_IFDIR  0x4000 ///< Directory.
#define S_IFBLK  0x6000 ///< Block device.
#define S_IFREG  0x8000 ///< Regular file.
#define S_IFLNK  0xA000 ///< Symbolic link.
#define S_IFSOCK 0xC000 ///< Unix socket.

/** @brief File permissions. */
#define S_IRUSR  0x100 ///< User—read permission.
#define S_IWUSR  0x080 ///< User—write permission.
#define S_IXUSR  0x040 ///< User—execute permission.

#define S_IRGRP  0x020 ///< Group—read permission.
#define S_IWGRP  0x010 ///< Group—write permission.
#define S_IXGRP  0x008 ///< Group—execute permission.

#define S_IROTH  0x004 ///< Other—read permission.
#define S_IWOTH  0x002 ///< Other—write permission.
#define S_IXOTH  0x001 ///< Other—execute permission.

typedef struct {
    char    name[64]; ///< Name of the file.
    u32     size;     ///< Size of the file in bytes.
    mode_t  mode;     ///< File permissions.
    s32     fd;       ///< File descriptor.
    u32     type;     ///< File type.
} stat_t;

#endif /* _NOS_KERNEL_STAT_H_ */