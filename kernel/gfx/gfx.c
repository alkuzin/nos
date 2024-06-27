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

#include <nos/vbefont.h>
#include <nos/types.h>
#include <nos/gfx.h>


static screen_t screen;


void gfx_set_width(u16 width)
{
    screen.width = width;
}

void gfx_set_height(u16 height)
{
    screen.height = height;
}

u16 gfx_get_width(void)
{
    return screen.width;
}

u16 gfx_get_height(void)
{
    return screen.height;
}

void gfx_set_framebuffer(u32 *framebuffer)
{
    screen.framebuffer = framebuffer;   
}

void gfx_draw_pixel(s32 x, s32 y, rgb_t color)
{
    u32 red, green, blue, offset;

    if (x >= 0 && x < screen.width && y >= 0 && y < screen.height) {
        red    = (u32)color.red << 16;
        green  = (u32)color.green << 8;
        blue   = (u32)color.blue;
        offset = y * screen.width + x;
        screen.framebuffer[offset] = red | green | blue;
    }
}

rgb_t gfx_get_pixel(s32 x, s32 y)
{
    u32   offset;
    rgb_t color;

    offset      = y * screen.width + x;
    color.red   = screen.framebuffer[offset + 2];
    color.green = screen.framebuffer[offset + 1];
    color.blue  = screen.framebuffer[offset];

    return color;
}

void gfx_fill_screen(rgb_t color)
{
    for (s32 y = 0; y < screen.height; y++) {
        for (s32 x = 0; x < screen.width; x++)
            gfx_draw_pixel(x, y, color);
    }
}

void gfx_draw_circle(s32 cx, s32 cy, s32 r, rgb_t color)
{
    s32 x, y, d;
    
    x = 0;
    y = r;
    d = 3 - 2 * r;
    
    while (x <= y) {
        for (int i = cx - x; i <= cx + x; i++) {
            gfx_draw_pixel(i, cy + y, color);
            gfx_draw_pixel(i, cy - y, color);
        }
        for (int i = cx - y; i <= cx + y; i++) {
            gfx_draw_pixel(i, cy + x, color);
            gfx_draw_pixel(i, cy - x, color);
        }

        if (d < 0)
            d = d + 4 * x + 6; 
        else {
            d = d + 4 * (x - y) + 10;
            y--;
        }

        x++;
    }
}

void gfx_draw_char(u8 c, s32 x, s32 y, rgb_t fg, rgb_t bg, bool is_bg_on)
{
    s32 mask[8] = { 128, 64, 32, 16, 8, 4, 2, 1 };
    s32 cx, cy;
    u8  *glyph;
    
    glyph = (u8 *)vbefont + (s32) c * 16;

    for (cy = 0; cy < 16; cy++) {
        for (cx = 0; cx < 8; cx++) {
            if (glyph[cy] & mask[cx])
                gfx_draw_pixel(x + cx, y + cy, fg); 
            else if (is_bg_on)
                gfx_draw_pixel(x + cx, y + cy, bg);
        }
    }
}

bool gfx_rgb_compare(rgb_t c1, rgb_t c2)
{
    return (c1.red == c2.red && c1.green == c2.green && c1.blue == c2.blue);
}

void gfx_test(void)
{
    gfx_draw_circle(400, 400, 100, RGB(255, 0, 0));
    gfx_draw_circle(600, 600, 50, RGB(255, 0, 255));
}