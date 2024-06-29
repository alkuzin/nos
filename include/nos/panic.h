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
 * @file  panic.h
 * @brief Kernel error output functions.
 *
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   29.06.2024 
 */

#ifndef _NOS_KERNEL_PANIC_H_
#define _NOS_KERNEL_PANIC_H_

#include <nos/stdarg.h>
#include <nos/types.h>

/**
 * @brief Macro for kernel panic (detecting an internal fatal error).
 * 
 * It displaying error message, file, function and line where error occured.
 * 
 * @param [in] fmt - given format string.
 * @param [in] ... - given variable number of arguments.
 */
#define panic(fmt, ...) __panic(__FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)

/* detatiled kernel panic */
/**
 * @brief Detailed kernel panic function.
 * 
 * It displaying error message, file, function and line where error occured.
 * 
 * @param [in] file - given filename, where error occured.
 * @param [in] func - given function name, where error occured.
 * @param [in] line - given line number, where error occured.
 * @param [in] fmt - given format string.
 * @param [in] ... - given variable number of arguments.
 */
void __panic(const char *file, const char *func, u32 line, const char *fmt, ...);

#endif /* _NOS_KERNEL_H_ */