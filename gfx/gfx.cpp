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

#include <kernel/kstd/cstring.hpp>
#include <kernel/gfx/vbefont.hpp>
#include <kernel/kstd/types.hpp>
#include <kernel/kstd/cmath.hpp>
#include <kernel/gfx/gfx.hpp>


namespace kernel {
namespace gfx {

static screen_t screen;


void set_width(u16 width)
{
    screen.width = width;
}

void set_height(u16 height)
{
    screen.height = height;
}

u16 get_width(void)
{
    return screen.width;
}

u16 get_height(void)
{
    return screen.height;
}

void set_framebuffer(u32 *framebuffer)
{
    screen.framebuffer = framebuffer;   
}

u32 *get_framebuffer(void)
{
    return screen.framebuffer;
}

void set_pitch(u16 pitch)
{
    screen.pitch = pitch;
}

u16 get_pitch(void)
{
    return screen.pitch;
}

bool rgb_compare(rgb c1, rgb c2)
{
    return (c1.red == c2.red && c1.green == c2.green && c1.blue == c2.blue);
}

void draw_pixel(s32 x, s32 y, rgb color)
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

rgb get_pixel(s32 x, s32 y)
{
    rgb color;
    u32   pixel;

    pixel       = screen.framebuffer[y * screen.width + x];
    color.red   = (pixel >> 16) & 0xFF;
    color.green = (pixel >> 8) & 0xFF;
    color.blue  = pixel & 0xFF;

    return color;
}

void fill_screen(rgb color)
{
    for (s32 y = 0; y < screen.height; y++) {
        for (s32 x = 0; x < screen.width; x++)
            draw_pixel(x, y, color);
    }
}

void draw_circle(s32 cx, s32 cy, s32 r, rgb color)
{
    s32 x, y, d;
    
    x = 0;
    y = r;
    d = 3 - 2 * r;
    
    while (x <= y) {
        for (s32 i = cx - x; i <= cx + x; i++) {
            draw_pixel(i, cy + y, color);
            draw_pixel(i, cy - y, color);
        }
        for (s32 i = cx - y; i <= cx + y; i++) {
            draw_pixel(i, cy + x, color);
            draw_pixel(i, cy - x, color);
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

void draw_char(u8 c, s32 x, s32 y, rgb fg, rgb bg, bool is_bg_on)
{
    static s32 mask[8] = { 128, 64, 32, 16, 8, 4, 2, 1 };
    s32 cx, cy;
    u8  *glyph;
    
    glyph = (u8 *)vbefont + (s32) c * 16;

    for (cy = 0; cy < 16; cy++) {
        for (cx = 0; cx < 8; cx++) {
            if (glyph[cy] & mask[cx])
                draw_pixel(x + cx, y + cy, fg); 
            else if (is_bg_on)
                draw_pixel(x + cx, y + cy, bg);
        }
    }
}

void draw_square(s32 x, s32 y, s32 side, rgb color)
{
    for (s32 i = x; i < x + side; i++) {
        for (s32 j = y; j < y + side; j++)
            draw_pixel(i, j, color);
    }
}

void draw_line(s32 x1, s32 y1, s32 x2, s32 y2, rgb color)
{
    s32 dx, dy, sx, sy, err, e2;
    
    dx  = kstd::abs(x2 - x1);
    dy  = kstd::abs(y2 - y1);
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
        draw_pixel(x1, y1, color);
        
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

void draw_triangle(s32 x1, s32 y1, s32 x2, s32 y2, s32 x3, s32 y3, rgb color)
{
    draw_line(x1, y1, x2, y2, color);
    draw_line(x2, y2, x3, y3, color);
    draw_line(x3, y3, x1, y1, color);
}

void draw_rectangle(s32 x, s32 y, s32 width, s32 height, rgb color)
{
    for (s32 i = x; i < x + width; i++) {
        for (s32 j = y; j < y + height; j++)
            draw_pixel(i, j, color);
    }
}

void test(void)
{
    draw_circle(400, 400, 100, color::red);
    draw_line(500, 500, 900, 600, color::green);
    draw_rectangle(100, 100, 50, 300, color::purple);
    draw_square(200, 100, 30, color::blue);
    draw_triangle(300, 50, 300, 300, 600, 300, color::white);


    draw_line(10, screen.height - 10, screen.width - 10, screen.height - 10, color::white);
    draw_line(10, screen.height - 11, screen.width - 10, screen.height - 11, color::white);
}

} // namespace gfx
} // namespace kernel