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
 * @file  tty.hpp
 * @brief TTY (teletype terminal). Contains definitions related
 * to screen input/output.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   17.05.2024 
 */

#ifndef _NOS_KERNEL_TTY_HPP_
#define _NOS_KERNEL_TTY_HPP_ 

#include <nos/stdarg.hpp>
#include <nos/types.hpp>
#include <nos/gfx.hpp>


namespace kernel {
namespace gfx {

///< Default kernel TTY foreground & background color.
#define TTY_FG_COLOR  RGB(255, 255, 255)
#define TTY_BG_COLOR  RGB(0, 0, 204)
#define TTY_TAB_WIDTH 4

///< TTY management structure.
typedef struct tty_s {
    s32   x_pos;            ///< X position of the cursor.
    s32   y_pos;            ///< Y position of the cursor.
    rgb fg;               ///< Foreground color.
    rgb bg;               ///< Background color.
    s32   height;           ///< Screen height.
    s32   width;            ///< Screen width.
    rgb primary_color;
    rgb secondary_color;
    rgb prev_fg;          ///< Previous foreground color.
    rgb prev_bg;          ///< Previous background color.
    rgb prev_prim_color;  ///< Previous primary color.
    rgb prev_sec_color;   ///< Previous secondary color.
} tty_t;

/* Initialize kernel TTY structure. */ 
void tty_init(void);

/* Initialize kernel TTY cursor structure. */ 
void tty_cursor_init(void);

/**
 * @brief Get cursor x position.
 * 
 * @return x position.
 */
s32  tty_get_x(void);

/**
 * @brief Get cursor y position.
 * 
 * @return y position.
 */
s32  tty_get_y(void);

/**
 * @brief Set cursor x position.
 * 
 * @param [in] x - new given cursor x position.
 */
void tty_set_x(s32 x);

/**
 * @brief Set cursor y position.
 * 
 * @param [in] y - new given cursor y position.
 */
void tty_set_y(s32 y);

/**
 * @brief Get kernel TTY structure foreground color.
 * 
 * @return current foreground color.
 */
rgb tty_get_fg(void);

/**
 * @brief Get kernel TTY structure background color.
 * 
 * @return current background color.
 */
rgb tty_get_bg(void);

/**
 * @brief Get TTY primary color. 
 * 
 * @return primary color. 
 */
rgb tty_get_primary_color(void);

/**
 * @brief Get TTY secondary color. 
 * 
 * @return secondary color. 
 */
rgb tty_get_secondary_color(void);

/**
 * @brief Set TTY primary color.
 * 
 * @param [in] color - given new primary color.
 */
void tty_set_primary_color(rgb color);

/**
 * @brief Set TTY secondary color. 
 * 
 * @param [in] color - given new secondary color.
 */
void tty_set_secondary_color(rgb color);

/**
 * @brief Set foreground & background color.
 * 
 * @param [in] fg - given foreground color.
 * @param [in] bg - given background color.
 */
void tty_set_color(rgb fg, rgb bg);

/**
 * @brief Get screen height.
 * 
 * @return current screen height.
 */
s32  tty_get_height(void);

/**
 * @brief Get screen width.
 * 
 * @return current screen width.
 */
s32  tty_get_width(void);

/** @brief Clear screen. */ 
void tty_clear(void);

/** @brief Rewrite TTY buffer. */ 
void tty_update(void);

/**
 * @brief Print char with custom color in a specific place.
 * 
 * @param [in] c - given character to print.
 * @param [in] x - given cursor x position to print.
 * @param [in] y - given cursor y position to print.
 * @param [in] fg - given foreground color. 
 * @param [in] bg - given background color. 
 */
void tty_kputchar_at(char c, s32 x, s32 y, rgb fg, rgb bg);

/**
 * @brief Print colored string to the screen.
 * 
 * @param [in] str - given string to print.
 * @param [in] fg - given foreground color.
 * @param [in] bg - given background color.
 */
void tty_printc(const char *str, rgb fg, rgb bg);

} // namespace gfx

namespace lib {

/**
 * @brief Print character to screen.
 * 
 * @param [in] c - given character to print.
 */
void kputchar(const s32 c);

/**
 * @brief Print colored character on screen.
 * 
 * @param [in] c - given character to print.
 * @param [in] fg - given foreground color.
 * @param [in] bg - given background color.
 */
void kputchar_c(const s32 c, gfx::rgb fg, gfx::rgb bg);
    
} // namespace lib
} // namespace kernel

#endif /* _NOS_KERNEL_TTY_HPP_ */