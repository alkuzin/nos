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
 * @file  printk.h
 * @brief Kernel output functions.
 *
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   29.06.2024 
 */

#ifndef _NOS_KERNEL_PRINTK_H_
#define _NOS_KERNEL_PRINTK_H_

#include <nos/stdarg.h>
#include <nos/types.h>
#include <nos/gfx.h>

/**
 * @brief Formats and prints data.
 * 
 * @param [in] fmt - given format string.
 * @param [in] ... - given variable number of arguments.
 */
void printk(const char *fmt, ...);

/**
 * @brief Auxilar function for formating and printing data.
 * 
 * @param [in] fmt - given format string.
 * @param [in] args - given variable number of arguments.
 */
void vprintk(const char *fmt, va_list args);

/**
 * @brief Formats and prints data to buffer.
 * 
 * @param [out] buf - given buffer for containing formated result.
 * @param [in] size - given buffer size.
 * @param [in] fmt - given format string.
 * @param [in] args - given variable list of arguments.
 */
void vsnprintk(char *buf, usize size, const char *fmt, va_list args);

/**
 * @brief Print given string on the same line.
 * 
 * @param [in] str - given null terminated string
 */
void putk(const char *str);

/**
 * @brief Print kernel component initialization message.
 * 
 * @param [in] state - given initialization state (OK/ERR). 
 * @param [in] fmt - given format string.
 * @param [in] args - given variable number of arguments.
 */
void kmesg(bool state, const char *fmt, ...);

/**
 * @brief Print colored string and a trailing newline.
 * 
 * @param [in] str - given null terminated string 
 * @param [in] fg - given foreground color.
 * @param [in] bg - given background color.
 */
void cputk(const char *str, rgb_t fg, rgb_t bg);

#endif /* _NOS_KERNEL_PRINTK_H_ */