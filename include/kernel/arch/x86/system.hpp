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
 * @file  system.hpp
 * @brief Contains some general inline assembly macros and functions.
 *
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   17.05.2024 
 */

#ifndef _KERNEL_ARCH_X86_SYSTEM_HPP_
#define _KERNEL_ARCH_X86_SYSTEM_HPP_

namespace kernel {
namespace arch {
namespace x86 {

/** @brief Insert a no-operation (nop) instruction.*/
constexpr inline void nop(void) noexcept
{
    __asm__ volatile ("nop");
}
 
/** @brief Enable interrupts.*/
constexpr inline void sti(void) noexcept
{
    __asm__ volatile ("sti");
}

/** @brief Disable interrupts.*/
constexpr inline void cli(void) noexcept 
{
    __asm__ volatile ("cli");
}

constexpr inline void enable_paging(void) noexcept
{
    __asm__ volatile ("movl %cr0, %eax; orl $0x80000001, %eax; movl %eax, %cr0;");
}

} // namespace x86
} // namespace arch
} // namespace kernel

#endif // _KERNEL_ARCH_X86_SYSTEM_HPP_