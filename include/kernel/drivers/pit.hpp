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
 * @file  pit.hpp
 * @brief Contains functions related to PIT (Programmable Interval Timer) operations.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   17.05.2024 
 */

#ifndef _KERNEL_DRIVER_PIT_HPP_
#define _KERNEL_DRIVER_PIT_HPP_

#include <kernel/drivers/driver.hpp>


namespace kernel {
namespace driver {

class PIT : public Driver
{
    u32 m_frequency;
    u32 m_divisor;

public:
    PIT(void) noexcept;

    /** @brief Enable driver.*/
    void initialize(void) noexcept override;
    
    /** @brief Handle driver interrupt.*/
    void handle_interrupt(void) const noexcept override;

    /**
     * @brief Delay time.
     * 
     * @param [in] msec - given numbers of milliseconds to delay.
     */
    void delay(usize msec) const noexcept;

    /**
     * @brief Get timer ticks.
     * 
     * @return timer ticks.
     */
    usize ticks(void) const noexcept;
};

extern PIT timer;

} // namespace driver
} // namespace kernel

#endif // _KERNEL_DRIVER_PIT_HPP_