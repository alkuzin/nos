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
 * @file  driver.hpp
 * @brief Contains driver base class.
 * 
 * @details This header file includes macro related to the VBE mode font.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   22.09.2024
 */

#ifndef _KERNEL_DRIVER_HPP_
#define _KERNEL_DRIVER_HPP_

#include <kernel/arch/x86/irq.hpp>
#include <kernel/kstd/string.hpp>


namespace kernel {
namespace driver {

enum class dtype {
    device,
    graphics
};

class Driver
{
public:
    virtual ~Driver(void) = default;

    /** @brief Enable driver.*/
    virtual void initialize(void) noexcept = 0;
    
    /** @brief Disable driver.*/
    virtual void shutdown(void) noexcept = 0;

    /**
     * @brief Get driver name.
     * 
     * @return driver name.
     */
    virtual kstd::string name(void) const noexcept = 0;

    /**
     * @brief Driver type.
     * 
     * @return driver type. 
     */
    virtual dtype type(void) const noexcept = 0;

    /** @brief Handle driver interrupt.*/
    virtual void handle_interrupt(void) const noexcept = 0;
};

} // namespace driver
} // namespace kernel

#endif // _KERNEL_DRIVER_HPP_