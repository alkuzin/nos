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
 * @file  klog.hpp
 * @brief Contains declarations for kernel logging.
 * 
 * @details This header file includes macro related to the VBE mode font.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   20.09.2024
 */

#ifndef _KERNEL_LOG_HPP_
#define _KERNEL_LOG_HPP_

#include <kernel/kstd/cstdio.hpp>


namespace kernel {
namespace log {

/** @brief Kernel message type.*/
enum class kmessage {
    success,
    error,
    debug
};

/**
 * @brief Print kernel success log.
 * 
 * @param [in] fmt - given format string.
 * @param [in] args - given variable number of arguments.
 */
void success(const char *fmt, ...) noexcept;

/**
 * @brief Print kernel debug log.
 * 
 * @param [in] fmt - given format string.
 * @param [in] args - given variable number of arguments.
 */
void debug(const char *fmt, ...) noexcept;

/**
 * @brief Print kernel error log.
 * 
 * @param [in] fmt - given format string.
 * @param [in] args - given variable number of arguments.
 */
void error(const char *fmt, ...) noexcept;

/**
 * @brief Print kernel component initialization message.
 * 
 * @param [in] type - given message type. 
 * @param [in] fmt - given format string.
 * @param [in] args - given variable number of arguments.
 */
void klog(kmessage type, const char *fmt, va_list args) noexcept;


} // namespace log
} // namespace kernel

#endif // _KERNEL_LOG_HPP_