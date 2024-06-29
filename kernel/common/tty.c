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
#include <nos/printk.h>
#include <nos/nosstd.h>
#include <nos/string.h>
#include <nos/ctype.h>
#include <nos/types.h>
#include <nos/timer.h>
#include <nos/tty.h>
#include <nos/gfx.h>


/** @brief Screen scroll function */
static void tty_scroll(void);

/* main kernel TTY structure */
static tty_t tty;


void tty_init(void)
{
    tty.x_pos  			= 0;
    tty.y_pos  			= 0;
    tty.fg     			= TTY_FG_COLOR;
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

rgb_t tty_get_fg(void)
{
    return tty.fg;
}

rgb_t tty_get_bg(void)
{
    return tty.bg;
}

rgb_t tty_get_primary_color(void)
{
	return tty.primary_color;
}

rgb_t tty_get_secondary_color(void)
{
	return tty.secondary_color;
}

void tty_set_primary_color(rgb_t color)
{
	tty.prev_prim_color = tty.primary_color;
	tty.primary_color   = color;
}

void tty_set_secondary_color(rgb_t color)
{
	tty.prev_sec_color  = tty.secondary_color;
	tty.secondary_color = color;
}

void tty_set_color(rgb_t fg, rgb_t bg)
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

void tty_kputchar_at(char c, s32 x, s32 y, rgb_t fg, rgb_t bg)
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
	rgb_t pixel;

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

void kputchar(const s32 c)
{
	kputchar_c(c, tty.fg, tty.bg);
}

void kputchar_c(const s32 c, rgb_t fg, rgb_t bg)
{
	s32 rows_to_scroll;

	if(tty.x_pos >= tty.width) {
		tty.x_pos = 0;
		tty.y_pos += VBE_CHAR_HEIGHT;
	}

	switch(c) {
		case '\n':
			for (s32 i = 0; i < tty.width / VBE_CHAR_WIDTH; i++) {
            	tty_kputchar_at(' ', tty.x_pos, tty.y_pos, fg, bg);
			    tty.x_pos += VBE_CHAR_WIDTH;
			}

			tty.y_pos += VBE_CHAR_HEIGHT;
			tty.x_pos = 0;
			
			break;
		
		case '\t':
			for (s32 i = 0; i < TTY_TAB_WIDTH; i++) {
            	tty_kputchar_at(' ', tty.x_pos, tty.y_pos, fg, bg);
				tty.x_pos += VBE_CHAR_WIDTH;
			}
			break;
		
		case '\v':
			tty.y_pos += VBE_CHAR_HEIGHT;
			break;
		
		case '\r':
			tty.x_pos = 0;
			break;
		
		case '\b':
            tty.x_pos -= VBE_CHAR_WIDTH;
            
            if(!tty.x_pos && tty.y_pos) {
			    tty.y_pos -= VBE_CHAR_HEIGHT;
                tty.x_pos = tty.width;
            }
			
            tty_kputchar_at(' ', tty.x_pos, tty.y_pos, fg, bg);
			break;
		
		default:
            if(isprint(c)) {
            	tty_kputchar_at(c, tty.x_pos, tty.y_pos, fg, bg);
			    tty.x_pos += VBE_CHAR_WIDTH;
            }
			break;
	};

	if (tty.y_pos >= tty.height) {
        rows_to_scroll = (tty.y_pos - tty.height) / VBE_CHAR_HEIGHT + 1;
        tty_scroll();
        tty.y_pos -= rows_to_scroll * VBE_CHAR_HEIGHT;
    }
}

void tty_printc(const char *str, rgb_t fg, rgb_t bg)
{
    u32 i;

    i = 0;

    while(str[i]) {
        kputchar_c(str[i], fg, bg);
        i++;
	}
}