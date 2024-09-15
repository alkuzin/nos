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

#ifndef _NOS_KERNEL_KEYBOARD_HPP_
#define _NOS_KERNEL_KEYBOARD_HPP_

#include <arch/x86/io.hpp>
#include <nos/irq.hpp>


namespace kernel {
namespace driver {

constexpr u32 INPUT_BUFFER_SIZE {256};

/** @brief Keyboard special keys enumeration. */
enum class KEY : u8 {
    ESC         = 0x01,
    BACKSPACE   = 0x0E,
    TAB         = 0x0F,
    ENTER       = 0x1C,
    LCTRL       = 0x1D,
    LSHFT       = 0x2A,
    BACKSLASH   = 0x2B,
    LALT        = 0x38,
    SPACE       = 0x39,
    CAPS_LOCK   = 0x3A,
    LEFT_ARROW  = 0x4B,
    RIGHT_ARROW = 0x4D,
    UP_ARROW    = 0x48,
    DOWN_ARROW  = 0x50
};

/** @brief keyboard initialization */
void keyboard_init(void);

/**
 * @brief Keyboard key press handler.
 * 
 * @param [in] regs - given pointer to interrupt register state.
 */
void keyboard_handler(core::int_reg_t *regs);

/** @brief Keyboard wait for user to press a key. */
void keyboard_wait(void);

/**
 * @brief Keyboard get character on key press.
 * 
 * @return Character read from the keyboard.
 */
u8   keyboard_getchar(void);

} // namespace driver
} // namespace kernel

#endif /* _NOS_KERNEL_KEYBOARD_HPP_ */