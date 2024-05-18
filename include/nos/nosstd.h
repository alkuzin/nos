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
 * @file  nosstd.h
 * @brief Contains diferent system functions.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   17.05.2024 
 */

#ifndef _NOS_NOSSTD_H_
#define _NOS_NOSSTD_H_

#include <stdint.h>
#include <stddef.h>

/**
 * @brief Kernel time delay in microseconds.
 * 
 * @param [in] microsec - given number of microseconds for kernel to sleep. 
 */
void __ksleep(u32 microsec);

/**
 * @brief Kernel time delay in seconds.
 * 
 * @param [in] sec - given number of seconds for kernel to sleep. 
 */
void ksleep(u32 sec);

///< Halt kernel.
void khalt(void); 

/**
 * @brief Allocates n bytes and returns a pointer
 * to the allocated memory.
 * 
 * @param [in] n - given number of bytes to allocate.
 * @return pointer to allocated memory in case of success.
 * @return null pointer otherwise.
 */
void *kmalloc(usize n);


/**
 * @brief Frees the memory space pointed to by ptr, 
 * which must have been returned by a previous call to kmalloc()
 * or related functions. Otherwise, or if ptr has already 
 * been freed, undefined behavior occurs. 
 * If ptr is null pointer, no operation is performed.
 * 
 * @param [in] ptr - given pointer to allocated memory.
 */
void kfree(void *ptr);

#endif /* _NOS_NOSSTD_H_ */