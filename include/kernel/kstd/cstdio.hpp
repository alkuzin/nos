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
 * @file  cstdio.hpp
 * @brief Defines general input/output functions.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   19.09.2024
 */

#ifndef _KERNEL_KSTD_CSTDIO_HPP_
#define _KERNEL_KSTD_CSTDIO_HPP_

#include <kernel/kstd/stdarg.hpp>
#include <kernel/kstd/types.hpp>
#include <kernel/gfx/gfx.hpp>


namespace kernel {
namespace kstd {

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
 * @brief Print colored string and a trailing newline.
 * 
 * @param [in] str - given null terminated string 
 * @param [in] fg - given foreground color.
 * @param [in] bg - given background color.
 */
void putk(const char *str, gfx::rgb fg, gfx::rgb bg);

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

} // namespace kstd
} // namespace kernel

#endif // _KERNEL_KSTD_CSTDIO_HPP_