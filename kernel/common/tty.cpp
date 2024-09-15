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

#include <nos/vbefont.hpp>
#include <nos/printk.hpp>
#include <nos/nosstd.hpp>
#include <nos/string.hpp>
#include <nos/ctype.hpp>
#include <nos/types.hpp>
#include <nos/timer.hpp>
#include <nos/tty.hpp>
#include <nos/gfx.hpp>


namespace kernel {
namespace gfx {

/** @brief Screen scroll function */
static void tty_scroll(void);

/* main kernel TTY structure */
static tty_t tty;


void tty_init(void)
{
    tty.x_pos  			= 0;
    tty.y_pos  			= 0;
    tty.fg     			= gfx::TTY_FG_COLOR;
    tty.bg     			= TTY_BG_COLOR;
    tty.height 			= gfx_get_height();
    tty.width  			= gfx_get_width();
	tty.primary_color   = TTY_FG_COLOR;
	tty.secondary_color = TTY_BG_COLOR;
	tty.prev_fg 		= TTY_FG_COLOR;
	tty.prev_bg 		= TTY_BG_COLOR;
	tty.primary_color   = TTY_FG_COLOR;
	tty.secondary_color = TTY_BG_COLOR;
}

s32 tty_get_x(void)
{
    return tty.x_pos;
}

s32 tty_get_y(void)
{
    return tty.y_pos;
}

void tty_set_x(s32 x)
{
    tty.x_pos = x;
}

void tty_set_y(s32 y)
{
    tty.y_pos = y;
}

rgb tty_get_fg(void)
{
    return tty.fg;
}

rgb tty_get_bg(void)
{
    return tty.bg;
}

rgb tty_get_primary_color(void)
{
	return tty.primary_color;
}

rgb tty_get_secondary_color(void)
{
	return tty.secondary_color;
}

void tty_set_primary_color(rgb color)
{
	tty.prev_prim_color = tty.primary_color;
	tty.primary_color   = color;
}

void tty_set_secondary_color(rgb color)
{
	tty.prev_sec_color  = tty.secondary_color;
	tty.secondary_color = color;
}

void tty_set_color(rgb fg, rgb bg)
{
	tty.prev_fg = tty.fg;
	tty.prev_bg = tty.bg;
    tty.fg 		= fg;
    tty.bg 		= bg;
}

s32  tty_get_height(void)
{
    return tty.height;
}

s32  tty_get_width(void)
{
    return tty.width;
}

void tty_kputchar_at(char c, s32 x, s32 y, rgb fg, rgb bg)
{
	gfx_draw_char((u8)c, x, y, fg, bg, true);
}

static void tty_scroll(void)
{
	u32 *back_framebuffer, *framebuffer, framebuffer_size, offset;
	u16 pitch;

	back_framebuffer = gfx_get_back_framebuffer();
	framebuffer      = gfx_get_framebuffer();
	pitch 			 = gfx_get_pitch();
	framebuffer_size = tty.height * pitch;

    for (u32 i = 0; i < framebuffer_size - tty.width * VBE_CHAR_HEIGHT; i++) {
		offset              = i + tty.width * VBE_CHAR_HEIGHT;
        framebuffer[i]      = framebuffer[offset];
        back_framebuffer[i] = back_framebuffer[offset];
    }

    for (u32 i = framebuffer_size - tty.width * VBE_CHAR_HEIGHT; i < framebuffer_size; i++) {
        framebuffer[i]      = 0x00;
        back_framebuffer[i] = 0x00;
    }
}

void tty_clear(void)
{
	gfx_fill_screen(tty.bg);
	
    tty_set_x(0);
    tty_set_y(0);
}

void tty_update(void)
{
	rgb pixel;

    for (s32 y = 0; y < tty.height; y++) {
        for (s32 x = 0; x < tty.width; x++) {
			pixel = gfx_get_pixel(x, y);

			if (gfx_rgb_compare(pixel, tty.prev_fg))
            	gfx_draw_pixel(x, y, tty.fg);
			else if (gfx_rgb_compare(pixel, tty.prev_bg))
            	gfx_draw_pixel(x, y, tty.bg);
			else if (gfx_rgb_compare(pixel, tty.prev_prim_color))
            	gfx_draw_pixel(x, y, tty.primary_color);
			else if (gfx_rgb_compare(pixel, tty.prev_sec_color))
            	gfx_draw_pixel(x, y, tty.secondary_color);
			else
            	gfx_draw_pixel(x, y, tty.fg);
		}
    }
}

void tty_printc(const char *str, rgb fg, rgb bg)
{
    u32 i;

    i = 0;

    while(str[i]) {
        lib::kputchar_c(str[i], fg, bg);
        i++;
	}
}

} // namespace gfx

namespace lib {

void kputchar(const s32 c)
{
	kputchar_c(c, gfx::tty.fg, gfx::tty.bg);
}

void kputchar_c(const s32 c, gfx::rgb fg, gfx::rgb bg)
{
	s32 rows_to_scroll;

	if(gfx::tty.x_pos >= gfx::tty.width) {
		gfx::tty.x_pos = 0;
		gfx::tty.y_pos += VBE_CHAR_HEIGHT;
	}

	switch(c) {
		case '\n':
			for (s32 i = 0; i < gfx::tty.width / VBE_CHAR_WIDTH; i++) {
            	gfx::tty_kputchar_at(' ', gfx::tty.x_pos, gfx::tty.y_pos, fg, bg);
			    gfx::tty.x_pos += VBE_CHAR_WIDTH;
			}

			gfx::tty.y_pos += VBE_CHAR_HEIGHT;
			gfx::tty.x_pos = 0;
			
			break;
		
		case '\t':
			for (s32 i = 0; i < TTY_TAB_WIDTH; i++) {
            	gfx::tty_kputchar_at(' ', gfx::tty.x_pos, gfx::tty.y_pos, fg, bg);
				gfx::tty.x_pos += VBE_CHAR_WIDTH;
			}
			break;
		
		case '\v':
			gfx::tty.y_pos += VBE_CHAR_HEIGHT;
			break;
		
		case '\r':
			gfx::tty.x_pos = 0;
			break;
		
		case '\b':
            gfx::tty.x_pos -= VBE_CHAR_WIDTH;
            
            if(!gfx::tty.x_pos && gfx::tty.y_pos) {
			    gfx::tty.y_pos -= VBE_CHAR_HEIGHT;
                gfx::tty.x_pos = gfx::tty.width;
            }
			
            gfx::tty_kputchar_at(' ', gfx::tty.x_pos, gfx::tty.y_pos, fg, bg);
			break;
		
		default:
            if(lib::isprint(c)) {
            	tty_kputchar_at(c, gfx::tty.x_pos, gfx::tty.y_pos, fg, bg);
			    gfx::tty.x_pos += VBE_CHAR_WIDTH;
            }
			break;
	};

	if (gfx::tty.y_pos >= gfx::tty.height) {
        rows_to_scroll = (gfx::tty.y_pos - gfx::tty.height) / VBE_CHAR_HEIGHT + 1;
        gfx::tty_scroll();
        gfx::tty.y_pos -= rows_to_scroll * VBE_CHAR_HEIGHT;
    }
}

} // namespace lib
} // namespace kernel