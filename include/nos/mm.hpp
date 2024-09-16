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
 * @file  mm.hpp
 * @brief Contains declarations for memory management.
 * 
 * @details This header file includes functions related to the
 * physical and virtual memory management.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   17.05.2024 
 */

#ifndef _NOS_KERNEL_MM_HPP_
#define _NOS_KERNEL_MM_HPP_

#include <nos/multiboot.hpp>
#include <nos/pmm.hpp>
#include <nos/vmm.hpp>


namespace kernel {
namespace core {
namespace memory {
    
/**
 * @brief Initialize memory manager.
 * 
 * @param [in] mboot - given multiboot information structure.
 */
void memory_init(multiboot_t *mboot);

} // namespace memory
} // namespace core
} // namespace kernel

#endif /* _NOS_KERNEL_MM_HPP_ */