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
 * @file  version.hpp
 * @brief Contains declarations for kernel functions and structures.
 * 
 * @details This header file includes constants, definitions related to the OS information.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   29.06.2024 
 */

#ifndef _KERNEL_INFO_VERSION_HPP_
#define _KERNEL_INFO_VERSION_HPP_

#include <kernel/kstd/stdlib.hpp> // TODO: replace with stdio


namespace kernel {
namespace info {

extern const char *__os_name__;
extern const char *__os_arch__;
extern const char *__os_author__;
extern const char *__os_build_date__;
extern const char *__os_build_time__;
extern const char *__os_compiler_version__;
extern const u32   __os_version_major__;
extern const u32   __os_version_minor__;
extern const u32   __os_version_lower__;

/** @brief Display main OS info: name, version and architecture.*/
constexpr inline void display_general_info(void) noexcept
{
    kstd::printk("%s (v%d.%d.%d %s) %s - 2024\n",
    __os_name__, 
    __os_version_major__,
    __os_version_minor__,
    __os_version_lower__,
    __os_arch__,
    __os_author__
    );
}

/** @brief Display OS build info: build date and time.*/
constexpr inline void display_build_info(void) noexcept
{
    kstd::printk("build time: %s %s [g++-%s]\n",
    __os_build_time__,
    __os_build_date__,
    __os_compiler_version__
    );
}

} // namespace info
} // namespace kernel

#endif // _KERNEL_INFO_VERSION_HPP_