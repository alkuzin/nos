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

#ifndef _KERNEL_TTY_HPP_
#define _KERNEL_TTY_HPP_ 

#include <kernel/kstd/stdarg.hpp>
#include <kernel/gfx/gfx.hpp>


namespace kernel {
namespace tty {

// Default kernel TTY foreground & background color.
constexpr gfx::rgb FG_COLOR  {gfx::RGB(255, 255, 255)};
constexpr gfx::rgb BG_COLOR  {gfx::RGB(0, 0, 204)};
constexpr s32      TAB_WIDTH {4};

// TTY management structure.
struct tty_t {
    s32 x_pos;                  // X position of the cursor.
    s32 y_pos;                  // Y position of the cursor.
    gfx::rgb fg;                // Foreground color.
    gfx::rgb bg;                // Background color.
    s32 height;                 // Screen height.
    s32 width;                  // Screen width.
    gfx::rgb primary_color;
    gfx::rgb secondary_color;
    gfx::rgb prev_fg;           // Previous foreground color.
    gfx::rgb prev_bg;           // Previous background color.
    gfx::rgb prev_prim_color;   // Previous primary color.
    gfx::rgb prev_sec_color;    // Previous secondary color.
};

/* Initialize kernel TTY structure.*/ 
void init(void);

/* Initialize kernel TTY cursor structure.*/ 
void cursor_init(void);

/**
 * @brief Get cursor x position.
 * 
 * @return x position.
 */
s32 get_x(void);

/**
 * @brief Get cursor y position.
 * 
 * @return y position.
 */
s32 get_y(void);

/**
 * @brief Set cursor x position.
 * 
 * @param [in] x - new given cursor x position.
 */
void set_x(s32 x);

/**
 * @brief Set cursor y position.
 * 
 * @param [in] y - new given cursor y position.
 */
void set_y(s32 y);

/**
 * @brief Get kernel TTY structure foreground color.
 * 
 * @return current foreground color.
 */
gfx::rgb get_fg(void);

/**
 * @brief Get kernel TTY structure background color.
 * 
 * @return current background color.
 */
gfx::rgb get_bg(void);

/**
 * @brief Get TTY primary color. 
 * 
 * @return primary color. 
 */
gfx::rgb get_primary_color(void);

/**
 * @brief Get TTY secondary color. 
 * 
 * @return secondary color. 
 */
gfx::rgb get_secondary_color(void);

/**
 * @brief Set TTY primary color.
 * 
 * @param [in] color - given new primary color.
 */
void set_primary_color(gfx::rgb color);

/**
 * @brief Set TTY secondary color. 
 * 
 * @param [in] color - given new secondary color.
 */
void set_secondary_color(gfx::rgb color);

/**
 * @brief Set foreground & background color.
 * 
 * @param [in] fg - given foreground color.
 * @param [in] bg - given background color.
 */
void set_color(gfx::rgb fg, gfx::rgb bg);

/**
 * @brief Get screen height.
 * 
 * @return current screen height.
 */
s32 get_height(void);

/**
 * @brief Get screen width.
 * 
 * @return current screen width.
 */
s32 get_width(void);

/** @brief Clear screen. */ 
void clear(void);

/** @brief Rewrite TTY buffer. */ 
void update(void);

/**
 * @brief Print char with custom color in a specific place.
 * 
 * @param [in] c - given character to print.
 * @param [in] x - given cursor x position to print.
 * @param [in] y - given cursor y position to print.
 * @param [in] fg - given foreground color. 
 * @param [in] bg - given background color. 
 */
void kputchar_at(char c, s32 x, s32 y, gfx::rgb fg, gfx::rgb bg);

/**
 * @brief Print colored string to the screen.
 * 
 * @param [in] str - given string to print.
 * @param [in] fg - given foreground color.
 * @param [in] bg - given background color.
 */
void printc(const char *str, gfx::rgb fg, gfx::rgb bg);

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
    
} // namespace tty
} // namespace kernel

#endif // _KERNEL_TTY_HPP_