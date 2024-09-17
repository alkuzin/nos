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
 * @file  gfx.hpp
 * @brief Contains declarations for graphics.
 * 
 * @details This header file includes functions and structs related to the
 * VBE mode graphics.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   24.06.2024
 */

#ifndef _NOS_KERNEL_GFX_HPP_
#define _NOS_KERNEL_GFX_HPP_

#include <nos/types.hpp>


namespace kernel {
namespace gfx {

/** @brief RGB color structure.*/
struct rgb {
    u8 red;
    u8 green;
    u8 blue;
};

/**
 * @brief Create RGB color.
 * 
 * @param [in] r - given red color.
 * @param [in] g - given green color.
 * @param [in] b - given blue color.
 * @return constexpr rgb 
 */
constexpr inline rgb RGB(u8 r, u8 g, u8 b) noexcept
{
    return ((rgb){r, g, b});
}

namespace color {

constexpr rgb red    = RGB(255, 0, 0);
constexpr rgb green  = RGB(0, 255, 0);
constexpr rgb blue   = RGB(0, 0, 255);
constexpr rgb black  = RGB(0, 0, 0);
constexpr rgb white  = RGB(255, 255, 255);
constexpr rgb brown  = RGB(176, 92, 53);
constexpr rgb purple = RGB(128, 0, 255);
constexpr rgb gray   = RGB(191, 191, 191);

} // namespace color

struct __screen_s {
    u16 pitch;              ///< Screen number of bytes per scanline.
    u16 width;              ///< Screen width.
    u16 height;             ///< Screen height.
    u32 *framebuffer;       ///< Screen framebuffer.
} __attribute__((packed)); /* prevent the compiler from optimizing */

typedef struct __screen_s screen_t;

/**
 * @brief Get framebuffer. 
 * 
 * @return pointer to framebuffer. 
 */
u32 *gfx_get_framebuffer(void);

/**
 * @brief Get number of bytes per scanline. 
 * 
 * @return framebuffer pitch. 
 */
u16 gfx_get_pitch(void);

/**
 * @brief Set number of bytes per scanline.
 * 
 * @param [in] pitch - given number of bytes per scanline to set.
 */
void gfx_set_pitch(u16 pitch);

/**
 * @brief Get screen width. 
 * 
 * @return screen width. 
 */
u16 gfx_get_width(void);

/**
 * @brief Get screen height. 
 * 
 * @return screen height. 
 */
u16 gfx_get_height(void);

/**
 * @brief Set screen width.
 * 
 * @param [in] width - given new screen width.
 */
void gfx_set_width(u16 width);

/**
 * @brief Set screen height.
 * 
 * @param [in] height - given new screen height.
 */
void gfx_set_height(u16 height);

/**
 * @brief Set screen framebuffer. 
 * 
 * @param [in] framebuffer - given new screen framebuffer.
 */
void gfx_set_framebuffer(u32 *framebuffer);

/**
 * @brief Compare two RGB colors.
 * 
 * @param [in] c1 - given first color to comapre. 
 * @param [in] c2 - given second color to comapre. 
 * @return true - if colors are equal.
 * @return false - otherwise.
 */
bool gfx_rgb_compare(rgb c1, rgb c2);

/**
 * @brief Draw pixel on the screen. 
 * 
 * @param [in] x - given x pixel position.
 * @param [in] y - given y pixel position.
 * @param [in] color - given RGB color of pixel.
 */
void gfx_draw_pixel(s32 x, s32 y, rgb color);

/**
 * @brief Get color of specific pixel.
 * 
 * @param [in] x - given x pixel position.
 * @param [in] y - given y pixel position.
 * @return pixel color.
 */
rgb gfx_get_pixel(s32 x, s32 y);

/**
 * @brief Fill screen with given color. 
 * 
 * @param [in] color - given RGB color.
 */
void gfx_fill_screen(rgb color);

/**
 * @brief Draw circle on the screen.
 * 
 * @param [in] cx - given x-position of circle center.
 * @param [in] cy - given y-position of circle center.
 * @param [in] r - given radius of the circle.
 * @param [in] color - given RGB color of circle.
 */
void gfx_draw_circle(s32 cx, s32 cy, s32 r, rgb color);

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
void gfx_draw_char(u8 c, s32 x, s32 y, rgb fg, rgb bg, bool is_bg_on);

/**
 * @brief Draw square on the screen.
 * 
 * @param [in] x - given x pixel position.
 * @param [in] y - given y pixel position.
 * @param [in] side - given square side length in pixels.
 * @param [in] color - given RGB color of square.
 */
void gfx_draw_square(s32 x, s32 y, s32 side, rgb color);

/**
 * @brief Draw line on the screen.
 * 
 * @param [in] x1 - given x position of first point.
 * @param [in] y1 - given y position of first point.
 * @param [in] x2 - given x position of second point.
 * @param [in] y2 - given y position of second point.
 * @param [in] color - given RGB color of line.
 */
void gfx_draw_line(s32 x1, s32 y1, s32 x2, s32 y2, rgb color);

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
void gfx_draw_triangle(s32 x1, s32 y1, s32 x2, s32 y2, s32 x3, s32 y3, rgb color);

/**
 * @brief Draw rectangle on the screen.
 * 
 * @param [in] x - given x pixel position.
 * @param [in] y - given y pixel position.
 * @param [in] width - given rectangle width. 
 * @param [in] height - given rectangle height. 
 * @param [in] color - given RGB color of rectangle.
 */
void gfx_draw_rectangle(s32 x, s32 y, s32 width, s32 height, rgb color);

/** @brief Test graphics.  */
void gfx_test(void);
    
} // namespace gfx
} // namespace kernel

#endif /* _NOS_KERNEL_GFX_HPP_ */