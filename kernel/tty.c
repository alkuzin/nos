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

#include <stdint.h>
#include <string.h>
#include <ctype.h>

#include <nos/kernel.h>
#include <nos/unistd.h>
#include <nos/tty.h>
#include <nos/vga.h>

/* video memory address */
static u16 *video_memory = (u16 *)VIDEO_MEMORY;

/* x & y positions of the cursor */
static i32 x_pos = 0;
static i32 y_pos = 0;

/* foreground & background default color */
static u8 default_color = (u8)(TTY_FG_COLOR | TTY_BG_COLOR << 4);

/* print char with custom color in a specific place */
static void __kputchar_at(char c, u8 color, i32 x, i32 y);

/* VGA scroll function */
static void __kscroll(void);


void __set_default_color(vga_color_t fg, vga_color_t bg) {
    default_color = (u8)(fg | bg << 4);
}

static void __kputchar_at(char c, u8 color, i32 x, i32 y) {
	video_memory[y * VGA_SCREEN_WIDTH + x] = vga_entry(c, color);
}

static void __kscroll(void)
{
	u16 buffer[(VGA_SCREEN_WIDTH * VGA_SCREEN_HEIGHT * 2)];

	memset(buffer, default_color, sizeof(buffer));
	memcpy(buffer, video_memory,  sizeof(buffer));

	__kclear();

    for (u16 y = 0; y < VGA_SCREEN_HEIGHT; y++) {
        for (u16 x = 0; x < VGA_SCREEN_WIDTH; x++)
            buffer[(y-1) * VGA_SCREEN_WIDTH + x] = buffer[y*VGA_SCREEN_WIDTH+x];
    }

    for (u16 x = 0; x < VGA_SCREEN_WIDTH; x++) {
        buffer[(VGA_SCREEN_HEIGHT-1) * VGA_SCREEN_WIDTH + x] = ' ' | default_color;
    }
	
    memcpy(video_memory, buffer, sizeof(buffer));
}

void __kclear(void)
{
	u32 i;

	i = 0;
	while(i < VGA_SCREEN_WIDTH * VGA_SCREEN_HEIGHT) {
		video_memory[i] = vga_entry(' ', default_color);
		i++;
	}
}

void kprint(const char *str)
{
    u32 i;

    i = 0;
    while(str[i]) {
        kputchar(str[i]);       
        i++;
	}
}

void kprintc(const char* str, vga_color_t fg, vga_color_t bg) 
{
    u8 color;
	i32 i;

    color = vga_entry_color(fg, bg);
	i = 0;
    while (str[i]) {
		__kputchar_at(str[i], color, x_pos, y_pos);
		i++;
	}
}

void kputchar(const i32 c)
{
	if(x_pos >= VGA_SCREEN_WIDTH) {
		x_pos = 0;
		y_pos++;
	}
	
	if(y_pos >= VGA_SCREEN_HEIGHT) {
		__kscroll();
		y_pos = VGA_SCREEN_HEIGHT - 1;
	}

	switch(c) {
		case '\n':
			y_pos++;
			x_pos = 0;
			break;
		
		case '\t':
			x_pos += TTY_TAB_WIDTH;
			break;
		
		case '\v':
			y_pos++;
			break;
		
		case '\r':
			x_pos = 0;
			break;
		
		case '\b':
            x_pos--;
            if(!x_pos && y_pos) {
			    y_pos--;
                x_pos = VGA_SCREEN_WIDTH;
            }
			__kputchar_at(' ', default_color, x_pos, y_pos);
			break;
		
		default:
            if(isprint(c)) {
			    __kputchar_at(c, default_color, x_pos, y_pos);
			    x_pos++;
            }
			break;
	};

	update_cursor(x_pos, y_pos);	
}

i32 __tty_get_x(void) {
    return x_pos;
}

i32 __tty_get_y(void) {
    return y_pos;
}

void __tty_set_x(i32 x) {
    x_pos = x;
}

void __tty_set_y(i32 y) {
    y_pos = y;
}
