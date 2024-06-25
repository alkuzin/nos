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

#include <nos/kernel.h>
#include <nos/nosstd.h>
#include <nos/types.h>
#include <nos/tty.h>
#include <nos/vga.h>


/* VGA scroll function */
static void __kscroll(void);

/* main kernel TTY structure */
static tty_t tty;

void tty_init(void)
{
    tty.v_mem  = (u16 *)VIDEO_MEMORY;
    tty.x_pos  = 0;
    tty.y_pos  = 0;
    tty.fg     = TTY_FG_COLOR;
    tty.bg     = TTY_BG_COLOR;
    tty.color  = vga_entry_color(tty.fg, tty.bg);
    tty.height = VGA_SCREEN_HEIGHT;
    tty.width  = VGA_SCREEN_WIDTH;
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

vga_color_t tty_get_fg(void)
{
    return tty.fg;
}

vga_color_t tty_get_bg(void)
{
    return tty.bg;
}

void tty_set_color(vga_color_t fg, vga_color_t bg)
{
    tty.fg    = TTY_FG_COLOR;
    tty.bg    = TTY_BG_COLOR;
    tty.color = (u8)(fg | bg << 4);
}

s32  tty_get_height(void)
{
    return tty.height;
}

s32  tty_get_width(void)
{
    return tty.width;
}

void tty_kputchar_at(char c, u8 color, s32 x, s32 y)
{
	tty.v_mem[y * tty.width + x] = vga_entry(c, color);
}

static void __kscroll(void)
{
	u16 buffer[(tty.width * tty.height * 2)];

	memset(buffer, tty.color, sizeof(buffer));
	memcpy(buffer, tty.v_mem, sizeof(buffer));

	tty_clear();

    for (u16 y = 0; y < tty.height; y++) {
        for (u16 x = 0; x < tty.width; x++)
            buffer[(y - 1) * tty.width + x] = buffer[y * tty.width + x];
    }

    for (u16 x = 0; x < tty.width; x++) {
        buffer[(tty.height - 1) * tty.width + x] = (' ' | tty.color);
    }
	
    memcpy(tty.v_mem, buffer, sizeof(buffer));
}

void tty_clear(void)
{
	s32 i;

	i = 0;
	
    while(i < tty.width * tty.height) {
		tty.v_mem[i] = vga_entry(' ', tty.color);
		i++;
	}
	
    tty_set_x(0);
    tty_set_y(0);
    update_cursor(0, 0);
}

void tty_rewrite(void)
{
	s32 i;

	i = 0;
	
    while(i < tty.width * tty.height) {
		tty.v_mem[i] = vga_entry(tty.v_mem[i], tty.color);
		i++;
	}
}

void kputchar(const s32 c)
{
	kputchar_c(c, tty.color);
}

void kputchar_c(const s32 c, u8 color)
{
	if(tty.x_pos >= tty.width) {
		tty.x_pos = 0;
		tty.y_pos++;
	}
	
	if(tty.y_pos >= tty.height) {
		__kscroll();
		tty.y_pos = tty.height - 1;
	}

	switch(c) {
		case '\n':
			tty.y_pos++;
			tty.x_pos = 0;
			break;
		
		case '\t':
			tty.x_pos += TTY_TAB_WIDTH;
			break;
		
		case '\v':
			tty.y_pos++;
			break;
		
		case '\r':
			tty.x_pos = 0;
			break;
		
		case '\b':
            tty.x_pos--;
            
            if(!tty.x_pos && tty.y_pos) {
			    tty.y_pos--;
                tty.x_pos = tty.width;
            }
			
            tty_kputchar_at(' ', color, tty.x_pos, tty.y_pos);
			break;
		
		default:
            if(isprint(c)) {
			    tty_kputchar_at(c, color, tty.x_pos, tty.y_pos);
			    tty.x_pos++;
            }
			break;
	};

	update_cursor(tty.x_pos, tty.y_pos);	
}

void tty_printc(const char *str, vga_color_t fg, vga_color_t bg)
{
	u8  color;
    u32 i;

	color = vga_entry_color(fg, bg);
    i = 0;

    while(str[i]) {
        kputchar_c(str[i], color);
        i++;
	}
}