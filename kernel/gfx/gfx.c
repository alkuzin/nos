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
#include <nos/string.h>
#include <nos/types.h>
#include <nos/math.h>
#include <nos/gfx.h>


static u32 back_framebuffer[sizeof(u16) * 1024 * 768];  ///< Additional framebuffer.
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

u32 *gfx_get_framebuffer(void)
{
    return screen.framebuffer;
}

u32 *gfx_get_back_framebuffer(void)
{
    return back_framebuffer;
}

void gfx_set_pitch(u16 pitch)
{
    screen.pitch = pitch;
}

u16 gfx_get_pitch(void)
{
    return screen.pitch;
}

void gfx_back_frambuffer_init(void)
{
    bzero(back_framebuffer, sizeof(back_framebuffer));
}

bool gfx_rgb_compare(rgb_t c1, rgb_t c2)
{
    return (c1.red == c2.red && c1.green == c2.green && c1.blue == c2.blue);
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
        back_framebuffer[offset]   = red | green | blue;
    }
}

rgb_t gfx_get_pixel(s32 x, s32 y)
{
    rgb_t color;
    u32   pixel;

    pixel       = screen.framebuffer[y * screen.width + x];
    color.red   = (pixel >> 16) & 0xFF;
    color.green = (pixel >> 8) & 0xFF;
    color.blue  = pixel & 0xFF;

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
        for (s32 i = cx - x; i <= cx + x; i++) {
            gfx_draw_pixel(i, cy + y, color);
            gfx_draw_pixel(i, cy - y, color);
        }
        for (s32 i = cx - y; i <= cx + y; i++) {
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

void gfx_draw_square(s32 x, s32 y, s32 side, rgb_t color)
{
    for (s32 i = x; i < x + side; i++) {
        for (s32 j = y; j < y + side; j++)
            gfx_draw_pixel(i, j, color);
    }
}

void gfx_draw_line(s32 x1, s32 y1, s32 x2, s32 y2, rgb_t color)
{
    s32 dx, dy, sx, sy, err, e2;
    
    dx  = abs(x2 - x1);
    dy  = abs(y2 - y1);
    err = dx - dy;

    if (x1 < x2) 
        sx = 1;
    else 
        sx = -1;
    
    if (y1 < y2)
        sy = 1;
    else
        sy = -1;
    
    for (;;) {
        gfx_draw_pixel(x1, y1, color);
        
        if (x1 == x2 && y1 == y2)
            break;
        
        e2 = 2 * err;
        
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }

        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

void gfx_draw_triangle(s32 x1, s32 y1, s32 x2, s32 y2, s32 x3, s32 y3, rgb_t color)
{
    gfx_draw_line(x1, y1, x2, y2, color);
    gfx_draw_line(x2, y2, x3, y3, color);
    gfx_draw_line(x3, y3, x1, y1, color);
}

void gfx_draw_rectangle(s32 x, s32 y, s32 width, s32 height, rgb_t color)
{
    for (s32 i = x; i < x + width; i++) {
        for (s32 j = y; j < y + height; j++)
            gfx_draw_pixel(i, j, color);
    }
}

void gfx_test(void)
{
    gfx_draw_circle(400, 400, 100, GFX_COLOR_RED);
    gfx_draw_line(500, 500, 900, 600, GFX_COLOR_GREEN);
    gfx_draw_rectangle(100, 100, 50, 300, GFX_COLOR_PURPLE);
    gfx_draw_square(200, 100, 30, GFX_COLOR_BLUE);
    gfx_draw_triangle(300, 50, 300, 300, 600, 300, GFX_COLOR_WHITE);


    gfx_draw_line(10, screen.height - 10, screen.width - 10, screen.height - 10, GFX_COLOR_WHITE);
    gfx_draw_line(10, screen.height - 11, screen.width - 10, screen.height - 11, GFX_COLOR_WHITE);
}