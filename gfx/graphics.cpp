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

#include <kernel/gfx/graphics.hpp>
#include <kernel/kstd/cmath.hpp>


namespace kernel {
namespace gfx {

void Graphics::init(Framebuffer& fb) noexcept
{
    m_fb = fb;
}

void Graphics::set_pixel(s32 x, s32 y, const rgb& color) noexcept
{
    u32 red, green, blue, offset;
    s32 width  = static_cast<s32>(m_fb.width());
    s32 height = static_cast<s32>(m_fb.height());

    if (x >= 0 && x < width && y >= 0 && y < height) {
        red    = static_cast<u32>(color.m_red << 16);
        green  = static_cast<u32>(color.m_green << 8);
        blue   = static_cast<u32>(color.m_blue);
        offset = y * width + x;

        m_fb.addr()[offset] = red | green | blue;
    }
}

rgb Graphics::get_pixel(s32 x, s32 y) const noexcept
{
    u32 pixel = m_fb.addr()[y * m_fb.width() + x];
    u8 red    = ((pixel >> 16) & 0xFF);
    u8 green  = ((pixel >> 8) & 0xFF);
    u8 blue   = (pixel & 0xFF);

    return rgb(red, green, blue);
}

void Graphics::fill_screen(const rgb& color) noexcept
{
    for (u32 y = 0; y < m_fb.height(); y++) {
        for (u32 x = 0; x < m_fb.width(); x++)
            set_pixel(x, y, color);
    }
}

// --------------------------------------------------------------------

void Graphics::draw_circle(s32 cx, s32 cy, s32 r, const rgb& color) noexcept
{
    s32 x = 0;
    s32 y = r;
    s32 d = 3 - 2 * r;
    
    while (x <= y) {
        for (s32 i = cx - x; i <= cx + x; i++) {
            set_pixel(i, cy + y, color);
            set_pixel(i, cy - y, color);
        }
        for (s32 i = cx - y; i <= cx + y; i++) {
            set_pixel(i, cy + x, color);
            set_pixel(i, cy - x, color);
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

void Graphics::draw_square(s32 x, s32 y, s32 side, const rgb& color) noexcept
{
    for (s32 i = x; i < x + side; i++) {
        for (s32 j = y; j < y + side; j++)
            set_pixel(i, j, color);
    }
}

void Graphics::draw_line(s32 x1, s32 y1, s32 x2, s32 y2, const rgb& color) noexcept
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
        set_pixel(x1, y1, color);
        
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

void Graphics::draw_triangle(s32 x1, s32 y1, s32 x2, s32 y2, s32 x3, s32 y3, const rgb& color) noexcept
{
    draw_line(x1, y1, x2, y2, color);
    draw_line(x2, y2, x3, y3, color);
    draw_line(x3, y3, x1, y1, color);
}

void Graphics::draw_rectangle(s32 x, s32 y, s32 width, s32 height, const rgb& color) noexcept
{
    for (s32 i = x; i < x + width; i++) {
        for (s32 j = y; j < y + height; j++)
            set_pixel(i, j, color);
    }
}

Graphics graphics;

} // namespace gfx
} // namespace kernel