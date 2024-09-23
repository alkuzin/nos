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
 * @file  keyboard.hpp
 * @brief Contains declarations for keyboard handeling functions and structures.
 * 
 * @details This header file includes definitions and functions
 * related to the managing of keyboard interrupts.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   17.05.2024 
 */

#ifndef _KERNEL_DRIVER_KEYBOARD_HPP_
#define _KERNEL_DRIVER_KEYBOARD_HPP_

#include <kernel/drivers/driver.hpp>
#include <kernel/arch/x86/io.hpp>


namespace kernel {
namespace driver {

constexpr u32 INPUT_BUFFER_SIZE {256};

/** @brief Keyboard special keys enumeration.*/
enum class key : u8 {
    esc         = 0x01,
    backspace   = 0x0E,
    tab         = 0x0F,
    enter       = 0x1C,
    lctrl       = 0x1D,
    lshft       = 0x2A,
    backslash   = 0x2B,
    lalt        = 0x38,
    space       = 0x39,
    caps_lock   = 0x3A,
    left_arrow  = 0x4B,
    right_arrow = 0x4D,
    up_arrow    = 0x48,
    down_arrow  = 0x50
};

class Keyboard : public Driver
{
    mutable bool m_is_caps;
    mutable bool m_is_caps_lock;

private:
    /** @brief Keyboard wait for user to press a key.*/
    void wait(void) const noexcept;

public:
    virtual ~Keyboard(void) noexcept = default;

    /** @brief Construct a new Keyboard object.*/
    Keyboard(void) noexcept;
    
    /** @brief Enable driver.*/
    void initialize(void) noexcept override;
    
    /** @brief Disable driver.*/
    void shutdown(void) noexcept override;

    /**
     * @brief Get driver name.
     * 
     * @return driver name.
     */
    kstd::string name(void) const noexcept override;

    /**
     * @brief Driver type.
     * 
     * @return driver type. 
     */
    driver::dtype type(void) const noexcept override;

    /**
     * @brief Handle driver interrupt.
     * 
     * @param [in] regs - given pointer to interrupt register state. 
     */
    void handle_interrupt(void) const noexcept override;
    
    /**
     * @brief Keyboard get character on key press.
     * 
     * @return Character read from the keyboard.
     */
    u8 getchar(void) const noexcept;
};

extern Keyboard keyboard;

} // namespace driver
} // namespace kernel

#endif // _KERNEL_DRIVER_KEYBOARD_HPP_