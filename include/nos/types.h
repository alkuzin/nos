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
 * @file  types.h
 * @brief Provides definitions for various data types used in kernel programming. 
 * It includes typedefs for standard data types such as integers, characters, and etc.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   07.06.2024 
 */

#ifndef _NOS_TYPES_H_
#define _NOS_TYPES_H_

/* unsigned types */
typedef unsigned long   u64;
typedef unsigned int    u32;
typedef unsigned short  u16;
typedef unsigned char   u8;

/* signed types */
typedef long   s64;
typedef int    s32;
typedef short  s16;
typedef char   s8;

/* floating point types */
typedef double f64;
typedef float  f32;

#define usize  u64
#define ssize  s64

typedef s32 pid_t;  ///< PID (Process Identificator)
typedef u32 mode_t; ///< File permission bits.

///< Supported file systems type.
typedef enum {
    EXT2
} fs_type_t;

#endif /* _NOS_TYPES_H_ */