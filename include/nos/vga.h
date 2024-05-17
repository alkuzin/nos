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
 * @file  vga.h
 * @brief Contains definitions related to screen characters input/output.
 * 
 * VGA (Video Graphics Array). It is a standard for displaying graphics 
 * and video on computer monitors.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   17.05.2024 
 */

#ifndef _NOS_KERNEL_VGA_H_
#define _NOS_KERNEL_VGA_H_ 

#include <stdint.h>

///< VGA screen information macros.
#define VIDEO_MEMORY       0xB8000
#define VGA_SCREEN_WIDTH   80
#define VGA_SCREEN_HEIGHT  25

#define REG_SCREEN_CTRL    0x3D4
#define REG_SCREEN_DATA    0x3D5

///< VGA colors enumeration.
typedef enum vga_color {
	VGA_COLOR_BLACK,
	VGA_COLOR_BLUE,
	VGA_COLOR_GREEN,
	VGA_COLOR_CYAN,
	VGA_COLOR_RED,
	VGA_COLOR_MAGENTA,
	VGA_COLOR_BROWN,
	VGA_COLOR_LIGHT_GREY,
	VGA_COLOR_DARK_GREY,
	VGA_COLOR_LIGHT_BLUE,
	VGA_COLOR_LIGHT_GREEN,
	VGA_COLOR_LIGHT_CYAN,
	VGA_COLOR_LIGHT_RED,
	VGA_COLOR_LIGHT_MAGENTA,
	VGA_COLOR_YELLOW,
	VGA_COLOR_WHITE
} vga_color_t;

/**
 * @brief Creates a VGA color entry based on
 * the foreground and background colors.
 * 
 * @param [in] fg - given foreground color.
 * @param [in] bg - given background color. 
 * @return the VGA color entry.
 */
u8   vga_entry_color(vga_color_t fg, vga_color_t bg);

/**
 * @brief Creates a VGA entry combining a character
 * and color information.
 * 
 * @param [in] c - given character.
 * @param [in] color - given color information for the character.
 * @return the VGA entry combining character and color.
 */
u16  vga_entry(u8 c, u8 color);

/**
 * @brief Updates the cursor position on the screen.
 *
 * @param [in] x - given x position of the cursor.
 * @param [in] y - given y position of the cursor.
 */
void update_cursor(i32 x, i32 y);

#endif /* _NOS_KERNEL_VGA_H_ */