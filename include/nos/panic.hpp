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
 * @file  panic.hpp
 * @brief Kernel error output functions.
 *
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   29.06.2024 
 */

#ifndef _NOS_KERNEL_PANIC_HPP_
#define _NOS_KERNEL_PANIC_HPP_

#include <nos/stdarg.hpp>
#include <nos/types.hpp>


namespace kernel {
namespace lib {

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
    
} // namespace lib
} // namespace kernel

#endif /* _NOS_KERNEL_PANIC_HPP_ */