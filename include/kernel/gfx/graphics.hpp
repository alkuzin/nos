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
 * @file  graphics.hpp
 * @brief Contains declarations for graphics class.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   20.09.2024
 */

#ifndef _KERNEL_GFX_GRAPHICS_HPP_
#define _KERNEL_GFX_GRAPHICS_HPP_

#include <kernel/gfx/framebuffer.hpp>
#include <kernel/gfx/rgb.hpp>


namespace kernel {
namespace gfx {

class Graphics
{
    Framebuffer m_fb;

public:
    Graphics(const Graphics&)        = delete; // prevent copying
    Graphics(Graphics&&)             = delete; // prevent moving
    Graphics& operator=(Graphics&&)  = delete; // prevent moving assignment
    Graphics(void) noexcept                       = default;
    virtual ~Graphics(void) noexcept              = default;
    Graphics& operator=(const Graphics&) noexcept = default;

    /**
     * @brief Construct a new Framebuffer object.
     * 
     * @param [in] mboot - given multiboot information structure.
     */
    void init(Framebuffer& fb) noexcept;

    /**
     * @brief Draw pixel on the screen. 
     * 
     * @param [in] x - given x pixel position.
     * @param [in] y - given y pixel position.
     * @param [in] color - given RGB color of pixel.
     */
    void set_pixel(s32 x, s32 y, const rgb& color) noexcept;

    /**
     * @brief Get color of specific pixel.
     * 
     * @param [in] x - given x pixel position.
     * @param [in] y - given y pixel position.
     * @return pixel color.
     */
    rgb get_pixel(s32 x, s32 y) const noexcept;
    
    /**
     * @brief Fill screen with given color. 
     * 
     * @param [in] color - given RGB color.
     */
    void fill_screen(const rgb& color) noexcept;

    // -----------------------------------------------------------

    /**
     * @brief Draw circle on the screen.
     * 
     * @param [in] cx - given x-position of circle center.
     * @param [in] cy - given y-position of circle center.
     * @param [in] r - given radius of the circle.
     * @param [in] color - given RGB color of circle.
     */
    void draw_circle(s32 cx, s32 cy, s32 r, const rgb& color) noexcept;

    /**
     * @brief Draw square on the screen.
     * 
     * @param [in] x - given x pixel position.
     * @param [in] y - given y pixel position.
     * @param [in] side - given square side length in pixels.
     * @param [in] color - given RGB color of square.
     */
    void draw_square(s32 x, s32 y, s32 side, const rgb& color) noexcept;

    /**
     * @brief Draw line on the screen.
     * 
     * @param [in] x1 - given x position of first point.
     * @param [in] y1 - given y position of first point.
     * @param [in] x2 - given x position of second point.
     * @param [in] y2 - given y position of second point.
     * @param [in] color - given RGB color of line.
     */
    void draw_line(s32 x1, s32 y1, s32 x2, s32 y2, const rgb& color) noexcept;

    /**
     * @brief Draw triangle on the screen.
     * 
     * @param [in] x1 - given x position of first point.
     * @param [in] y1 - given y position of first point.
     * @param [in] x2 - given x position of second point.
     * @param [in] y2 - given y position of second point.
     * @param [in] x3 - given x position of third point.
     * @param [in] y3 - given y position of third point.
     * @param [in] color - given RGB color of triangle.
     */
    void draw_triangle(s32 x1, s32 y1, s32 x2, s32 y2, s32 x3, s32 y3, const rgb& color) noexcept;

    /**
     * @brief Draw rectangle on the screen.
     * 
     * @param [in] x - given x pixel position.
     * @param [in] y - given y pixel position.
     * @param [in] width - given rectangle width. 
     * @param [in] height - given rectangle height. 
     * @param [in] color - given RGB color of rectangle.
     */
    void draw_rectangle(s32 x, s32 y, s32 width, s32 height, const rgb& color) noexcept;
};

extern Graphics graphics;

} // namespace gfx
} // namespace kernel

#endif // _KERNEL_GFX_GRAPHICS_HPP_