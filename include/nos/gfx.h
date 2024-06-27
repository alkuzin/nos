/* MIT License
 *
 * Copyright (c) 2024 Alexander (@alkuzin)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. */

/**
 * @file  gfx.h
 * @brief Contains declarations for graphics.
 * 
 * @details This header file includes functions and structs related to the
 * VBE mode graphics.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   24.06.2024
 */

#ifndef _NOS_KERNEL_GFX_H_
#define _NOS_KERNEL_GFX_H_

#include <nos/types.h>


/** @brief Macro to create RGB color */
#define RGB(r, g, b) ((rgb_t){(r), (g), (b)})

#define GFX_COLOR_RED    RGB(255, 0, 0)
#define GFX_COLOR_GREEN  RGB(0, 255, 0)
#define GFX_COLOR_BLUE   RGB(0, 0, 255)
#define GFX_COLOR_BLACK  RGB(0, 0, 0)
#define GFX_COLOR_WHITE  RGB(255, 255, 255)
#define GFX_COLOR_BROWN  RGB(176, 92, 53)
#define GFX_COLOR_PURPLE RGB(128, 0, 255)

/** @brief RGB color structure */
typedef struct {
    u8 red;
    u8 green;
    u8 blue;
} rgb_t;

struct __screen_s {
    u16 width;          ///< Screen width.
    u16 height;         ///< Screen height.
    u32 *framebuffer;   ///< Screen framebuffer.
} __attribute__((packed)); /* prevent the compiler from optimizing */

typedef struct __screen_s screen_t;

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
 * @brief Draw pixel on the screen. 
 * 
 * @param [in] x - given x pixel position.
 * @param [in] y - given y pixel position.
 * @param [in] color - given RGB color of pixel.
 */
void gfx_draw_pixel(s32 x, s32 y, rgb_t color);

/**
 * @brief Get color of specific pixel.
 * 
 * @param [in] x - given x pixel position.
 * @param [in] y - given y pixel position.
 * @return pixel color.
 */
rgb_t gfx_get_pixel(s32 x, s32 y);

/**
 * @brief Fill screen with given color. 
 * 
 * @param [in] color - given RGB color.
 */
void gfx_fill_screen(rgb_t color);

/**
 * @brief Draw circle on the screen.
 * 
 * @param [in] cx - given x-position of circle center.
 * @param [in] cy - given y-position of circle center.
 * @param [in] r - given radius of the circle.
 * @param [in] color - given RGB color of circle.
 */
void gfx_draw_circle(s32 cx, s32 cy, s32 r, rgb_t color);

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
void gfx_draw_char(u8 c, s32 x, s32 y, rgb_t fg, rgb_t bg, bool is_bg_on);

/**
 * @brief Compare two RGB colors.
 * 
 * @param [in] c1 - given first color to comapre. 
 * @param [in] c2 - given second color to comapre. 
 * @return true - if colors are equal.
 * @return false - otherwise.
 */
bool gfx_rgb_compare(rgb_t c1, rgb_t c2);

/** @brief Test graphics.  */
void gfx_test(void);

#endif /* _NOS_KERNEL_GFX_H_ */