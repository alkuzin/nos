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

#include <nos/types.h>
#include <nos/ports.h>
#include <nos/vga.h>

u8 vga_entry_color(vga_color_t fg, vga_color_t bg)
{
    return (fg | bg << 4);
}

u16 vga_entry(u8 c, u8 color)
{
    return ((u16)c | (u16)color << 8);
}

void update_cursor(s32 x, s32 y)
{
	u16 pos;

	pos = y * VGA_SCREEN_WIDTH + x;

	outb(REG_SCREEN_CTRL, 15);
	outb(REG_SCREEN_DATA, (u8)(pos & 0xFF));
	outb(REG_SCREEN_CTRL, 14);
	outb(REG_SCREEN_DATA, (u8)(pos >> 8) & 0xFF);
}
