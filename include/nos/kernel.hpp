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
 * @file  kernel.hpp
 * @brief Contains declarations for kernel functions and structures.
 * 
 * @details This header file includes functions related to kernel setup & kernel entry point.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   17.05.2024 
 */

#ifndef _NOS_KERNEL_HPP_
#define _NOS_KERNEL_HPP_

#include <nos/multiboot.hpp>
#include <nos/types.hpp>


namespace kernel {
namespace core {

/**
 * @brief Setup kernel.
 * 
 * Initializes kernel components such as TTY, GDT, 
 * IDT, timer and etc.
 * 
 * @param [in] magic - given magic number.
 * @param [in] mboot - given multiboot information structure.
 */
void kboot(u32 magic, const multiboot_t& mboot);

} // namespace core
} // namespace kernel

/**
 * @brief Kernel entry point.
 * 
 * @param [in] magic - given magic number.
 * @param [in] mboot - given multiboot information structure.
 */
extern "C" void kmain(kernel::u32 magic, multiboot_t *mboot);

#endif // _NOS_KERNEL_HPP_