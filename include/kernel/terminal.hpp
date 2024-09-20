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
 * @file  terminal.hpp
 * @brief TTY (teletype terminal). Contains definitions related
 * to screen input/output.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   20.09.2024
 */

#ifndef _KERNEL_TERMINAL_HPP_
#define _KERNEL_TERMINAL_HPP_

#include <kernel/gfx/graphics.hpp>


namespace kernel {
namespace tty {

class Terminal
{
    gfx::Framebuffer m_fb;
    gfx::rgb m_fg;                // Foreground color.
    gfx::rgb m_bg;                // Background color.
    gfx::rgb m_secondary_color;
    gfx::rgb m_primary_color;
    s32      m_x_pos;             // X position of the cursor.
    s32      m_y_pos;             // Y position of the cursor.
    s32      m_height;            // Screen height.
    s32      m_width;             // Screen width.

private:
    /** @brief Scroll screen.*/
    void scroll(void) noexcept;

public:
    Terminal(const Terminal&)        = delete; // prevent copying
    Terminal(Terminal&&)             = delete; // prevent moving
    Terminal& operator=(Terminal&&)  = delete; // prevent moving assignment
    Terminal(void) noexcept                       = default;
    virtual ~Terminal(void) noexcept              = default;
    Terminal& operator=(const Terminal&) noexcept = default;

    /**
     * @brief Initialize a Framebuffer object.
     * 
     * @param [in] mboot - given multiboot information structure.
     */
    void init(gfx::Framebuffer& fb) noexcept;

    /**
     * @brief Get kernel TTY structure foreground color.
     * 
     * @return current foreground color.
     */
    gfx::rgb fg(void) noexcept;

    /**
     * @brief Get kernel TTY structure background color.
     * 
     * @return current background color.
     */
    gfx::rgb bg(void) noexcept;

    /**
     * @brief Get TTY primary color. 
     * 
     * @return primary color. 
     */
    gfx::rgb primary_color(void) const noexcept;

    /**
     * @brief Get TTY secondary color. 
     * 
     * @return secondary color. 
     */
    gfx::rgb secondary_color(void) const noexcept;

    /**
     * @brief Set foreground & background color.
     * 
     * @param [in] fg - given foreground color.
     * @param [in] bg - given background color.
     * @param [in] pc - given primary color.
     * @param [in] sc - given secondary color.
     */
    void set_color(gfx::rgb fg, gfx::rgb bg, gfx::rgb pc, gfx::rgb sc) noexcept;

    /** @brief Clear screen. */ 
    void clear(void) noexcept;

    /**
     * @brief Print char with custom color in a specific place.
     * 
     * @param [in] c - given character to print.
     * @param [in] x - given cursor x position to print.
     * @param [in] y - given cursor y position to print.
     * @param [in] fg - given foreground color. 
     * @param [in] bg - given background color. 
     */
    void put_at(char c, s32 x, s32 y, gfx::rgb fg, gfx::rgb bg) noexcept;

    /**
     * @brief Print colored character on screen.
     * 
     * @param [in] c - given character to print.
     * @param [in] fg - given foreground color.
     * @param [in] bg - given background color.
     */
    void put_c(const s32 c, gfx::rgb fg, gfx::rgb bg) noexcept;

    /**
     * @brief Draw VBE font character on the screen.
     * 
     * @param [in] c - given character to print.
     * @param [in] x - given x pixel position.
     * @param [in] y - given y pixel position.
     * @param [in] fg - given foreground color.
     * @param [in] bg - given background color.
     * @param [in] is_bg_on - given param determine whether to display the @a bg.
     */
    void draw_char(u8 c, s32 x, s32 y, const gfx::rgb& fg, const gfx::rgb& bg, bool is_bg_on) noexcept;
};

extern Terminal terminal;

} // namespace tty
} // namespace kernel

#endif // _KERNEL_TERMINAL_HPP_