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
 * @file  memlayout.hpp
 * @brief Kernel memory layout.
 * 
 * @details Contains kernel memory map addresses.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   25.06.2024
 */

#ifndef _NOS_KERNEL_MEMLAYOUT_HPP_
#define _NOS_KERNEL_MEMLAYOUT_HPP_

#include <nos/types.hpp>


extern kernel::u32 kernel_phys_start;
extern kernel::u32 kernel_phys_end;

namespace kernel {
namespace info {
    
#define KERNEL_START_PADDR ((u32) &kernel_phys_start)
#define KERNEL_END_PADDR   ((u32) &kernel_phys_end)
#define KERNEL_SIZE        (KERNEL_END_PADDR - KERNEL_START_PADDR)

} // namespace info
} // namespace kernel


#endif /* _NOS_KERNEL_MEMLAYOUT_HPP_ */