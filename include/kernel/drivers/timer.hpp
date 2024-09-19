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
 * @file  timer.hpp
 * @brief Contains functions related to timer operations.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   17.05.2024 
 */

#ifndef _KERNEL_DRIVER_TIMER_HPP_
#define _KERNEL_DRIVER_TIMER_HPP_

#include <kernel/arch/x86/irq.hpp>


namespace kernel {
namespace driver {
namespace driver {

/** @brief Initialize the timer.*/
void init(void) noexcept;

/** @brief Interrupt service routine for IRQ0.*/
void on_irq0(arch::x86::int_reg_t *regs) noexcept;

/**
 * @brief Delay time. 
 * 
 * @param [in] seconds - given number of seconds to delay.
 */
void delay(u32 seconds) noexcept;

} // namespace driver
} // namespace driver
} // namespace kernel

#endif // _KERNEL_DRIVER_TIMER_HPP_