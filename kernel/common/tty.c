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

#include <string.h>
#include <ctype.h>

#include <nos/vbefont.h>
#include <nos/kernel.h>
#include <nos/nosstd.h>
#include <nos/types.h>
#include <nos/timer.h>
#include <nos/tty.h>
#include <nos/vga.h>
#include <nos/gfx.h>


/** @brief Screen scroll function */
static void __kscroll(void);

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

static void __kscroll(void)
{
	// TODO: implement secondary buffer for faster scrolling
}

void tty_clear(void)
{
	gfx_fill_screen(tty.bg);
	
    tty_set_x(0);
    tty_set_y(0);
    update_cursor(0, 0);
}

void tty_rewrite(void)
{
	// TODO: fix issue with rewrite
	
	// rgb_t pixel;

    // for (s32 y = 0; y < tty.height; y++) {
    //     for (s32 x = 0; x < tty.width; x++) {
	// 		pixel = gfx_get_pixel(x, y);

	// 		if (gfx_rgb_compare(pixel, tty.prev_fg))
    //         	gfx_draw_pixel(x, y, tty.fg);
	// 		else if (gfx_rgb_compare(pixel, tty.prev_bg))
    //         	gfx_draw_pixel(x, y, tty.bg);
	// 		else if (gfx_rgb_compare(pixel, tty.prev_prim_color))
    //         	gfx_draw_pixel(x, y, tty.primary_color);
	// 		else if (gfx_rgb_compare(pixel, tty.prev_sec_color))
    //         	gfx_draw_pixel(x, y, tty.secondary_color);
	// 		else
    //         	gfx_draw_pixel(x + 1, y, pixel);
	// 	}
    // }
}

void kputchar(const s32 c)
{
	kputchar_c(c, tty.fg, tty.bg);
}

void kputchar_c(const s32 c, rgb_t fg, rgb_t bg)
{
	if(tty.x_pos >= tty.width) {
		tty.x_pos = 0;
		tty.y_pos += VBE_CHAR_HEIGHT;
	}
	
	if(tty.y_pos >= tty.height) {
		__kscroll();
		tty.y_pos = tty.height - 1;
	}

	switch(c) {
		case '\n':
			tty.y_pos += VBE_CHAR_HEIGHT;
			tty.x_pos = 0;
			break;
		
		case '\t':
			tty.x_pos += TTY_TAB_WIDTH * VBE_CHAR_WIDTH;
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

	update_cursor(tty.x_pos, tty.y_pos);	
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