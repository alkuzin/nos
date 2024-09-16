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
 * @file  printk.hpp
 * @brief Kernel output functions.
 *
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   29.06.2024 
 */

#ifndef _NOS_KERNEL_PRINTK_HPP_
#define _NOS_KERNEL_PRINTK_HPP_

#include <nos/stdarg.hpp>
#include <nos/types.hpp>
#include <nos/gfx.hpp>


namespace kernel {
namespace lib {

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
void putk(const char *str, gfx::rgb fg, gfx::rgb bg);

} // namespace lib
} // namespace kernel

#endif /* _NOS_KERNEL_PRINTK_HPP_ */