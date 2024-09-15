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

#ifndef _NOS_KERNEL_TIMER_HPP_
#define _NOS_KERNEL_TIMER_HPP_

#include <nos/irq.hpp>


namespace kernel {
namespace driver {

/** @brief Initialize the timer. */
void timer_init(void);

/** @brief Interrupt service routine for IRQ0. */
void on_irq0(core::int_reg_t *regs);

/**
 * @brief Delay time. 
 * 
 * @param [in] seconds - given number of seconds to delay.
 */
void timer_delay(u32 seconds);

} // namespace driver
} // namespace kernel

#endif /* _NOS_KERNEL_TIMER_HPP_ */