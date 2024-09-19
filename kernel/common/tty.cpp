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

#include <kernel/drivers/timer.hpp>
#include <kernel/kstd/cstdlib.hpp>
#include <kernel/kstd/cstring.hpp>
#include <kernel/gfx/vbefont.hpp>
#include <kernel/kstd/cstdio.hpp>
#include <kernel/kstd/ctype.hpp>
#include <kernel/kstd/types.hpp>
#include <kernel/gfx/gfx.hpp>
#include <kernel/tty.hpp>


namespace kernel {
namespace tty {

/** @brief Screen scroll function */
void scroll(void);

/* main kernel terminal.structure */
static tty_t terminal;


void init(void)
{
    terminal.x_pos			 = 0;
    terminal.y_pos			 = 0;
    terminal.fg				 = FG_COLOR;
    terminal.bg				 = BG_COLOR;
    terminal.height			 = gfx::get_height();
    terminal.width			 = gfx::get_width();
	terminal.primary_color   = FG_COLOR;
	terminal.secondary_color = BG_COLOR;
	terminal.prev_fg		 = FG_COLOR;
	terminal.prev_bg		 = BG_COLOR;
	terminal.primary_color   = FG_COLOR;
	terminal.secondary_color = BG_COLOR;
}

s32 get_x(void)
{
    return terminal.x_pos;
}

s32 get_y(void)
{
    return terminal.y_pos;
}

void set_x(s32 x)
{
    terminal.x_pos = x;
}

void set_y(s32 y)
{
    terminal.y_pos = y;
}

gfx::rgb get_fg(void)
{
    return terminal.fg;
}

gfx::rgb get_bg(void)
{
    return terminal.bg;
}

gfx::rgb get_primary_color(void)
{
	return terminal.primary_color;
}

gfx::rgb get_secondary_color(void)
{
	return terminal.secondary_color;
}

void set_primary_color(gfx::rgb color)
{
	terminal.prev_prim_color = terminal.primary_color;
	terminal.primary_color   = color;
}

void set_secondary_color(gfx::rgb color)
{
	terminal.prev_sec_color  = terminal.secondary_color;
	terminal.secondary_color = color;
}

void set_color(gfx::rgb fg, gfx::rgb bg)
{
	terminal.prev_fg = terminal.fg;
	terminal.prev_bg = terminal.bg;
    terminal.fg 		= fg;
    terminal.bg 		= bg;
}

s32  get_height(void)
{
    return terminal.height;
}

s32  get_width(void)
{
    return terminal.width;
}

void kputchar_at(char c, s32 x, s32 y, gfx::rgb fg, gfx::rgb bg)
{
	gfx::draw_char((u8)c, x, y, fg, bg, true);
}

void scroll(void)
{
	u32 *framebuffer = gfx::get_framebuffer();
	u16 pitch		 = gfx::get_pitch();
	u32 size		 = static_cast<u32>(terminal.height) * pitch;
	u32 offset;

    for (u32 i = 0; i < size; i++) {
		offset         = i + static_cast<u32>(terminal.width) * gfx::VBE_CHAR_HEIGHT;
        framebuffer[i] = framebuffer[offset];
    }

	auto pos = size - terminal.width * gfx::VBE_CHAR_HEIGHT;
	kstd::bzero(&framebuffer[pos], size - pos);
}

void clear(void)
{
	gfx::fill_screen(terminal.bg);
	
    set_x(0);
    set_y(0);
}

void update(void)
{
	gfx::rgb pixel;

    for (s32 y = 0; y < terminal.height; y++) {
        for (s32 x = 0; x < terminal.width; x++) {
			pixel = gfx::get_pixel(x, y);

			if (gfx::rgb_compare(pixel, terminal.prev_fg))
            	gfx::draw_pixel(x, y, terminal.fg);
			else if (gfx::rgb_compare(pixel, terminal.prev_bg))
            	gfx::draw_pixel(x, y, terminal.bg);
			else if (gfx::rgb_compare(pixel, terminal.prev_prim_color))
            	gfx::draw_pixel(x, y, terminal.primary_color);
			else if (gfx::rgb_compare(pixel, terminal.prev_sec_color))
            	gfx::draw_pixel(x, y, terminal.secondary_color);
			else
            	gfx::draw_pixel(x, y, terminal.fg);
		}
    }
}

void printc(const char *str, gfx::rgb fg, gfx::rgb bg)
{
    u32 i = 0;

    while(str[i]) {
        kputchar_c(str[i], fg, bg);
        i++;
	}
}

void kputchar(const s32 c)
{
	kputchar_c(c, terminal.fg, terminal.bg);
}

void kputchar_c(const s32 c, gfx::rgb fg, gfx::rgb bg)
{
	s32 rows_to_scroll;

	if(terminal.x_pos >= terminal.width) {
		terminal.x_pos = 0;
		terminal.y_pos += gfx::VBE_CHAR_HEIGHT;
	}

	switch(c) {
		case '\n':
			for (s32 i = 0; i < terminal.width / gfx::VBE_CHAR_WIDTH; i++) {
            	kputchar_at(' ', terminal.x_pos, terminal.y_pos, fg, bg);
			    terminal.x_pos += gfx::VBE_CHAR_WIDTH;
			}

			terminal.y_pos += gfx::VBE_CHAR_HEIGHT;
			terminal.x_pos = 0;
			
			break;
		
		case '\t':
			for (s32 i = 0; i < TAB_WIDTH; i++) {
            	kputchar_at(' ', terminal.x_pos, terminal.y_pos, fg, bg);
				terminal.x_pos += gfx::VBE_CHAR_WIDTH;
			}
			break;
		
		case '\v':
			terminal.y_pos += gfx::VBE_CHAR_HEIGHT;
			break;
		
		case '\r':
			terminal.x_pos = 0;
			break;
		
		case '\b':
            terminal.x_pos -= gfx::VBE_CHAR_WIDTH;
            
            if(!terminal.x_pos && terminal.y_pos) {
			    terminal.y_pos -= gfx::VBE_CHAR_HEIGHT;
                terminal.x_pos = terminal.width;
            }
			
            kputchar_at(' ', terminal.x_pos, terminal.y_pos, fg, bg);
			break;
		
		default:
            if(kstd::isprint(c)) {
            	kputchar_at(c, terminal.x_pos, terminal.y_pos, fg, bg);
			    terminal.x_pos += gfx::VBE_CHAR_WIDTH;
            }
			break;
	};

	if (terminal.y_pos >= terminal.height) {
        rows_to_scroll = (terminal.y_pos - terminal.height) / gfx::VBE_CHAR_HEIGHT + 1;
        scroll();
        terminal.y_pos -= rows_to_scroll * gfx::VBE_CHAR_HEIGHT;
    }
}

} // namespace tty
} // namespace kernel