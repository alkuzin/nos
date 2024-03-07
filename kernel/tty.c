/*
MIT License

Copyright (c) 2024 Alexander (@alkuzin)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "VGA_Software"), to deal
in the VGA_Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the VGA_Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the VGA_Software.

THE VGA_SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIEVGA_S OF MERCHANTABILITY,
FITNEVGA_SS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORVGA_S OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWIVGA_SE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE VGA_SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
VGA_SOFTWARE.
*/

#include <libk/stdint.h>
#include <libk/memory.h>
#include <kernel/tty.h>
#include <kernel/vga.h>

static uint16_t *video_memory = (uint16_t *)VIDEO_MEMORY;
static int x_pos = 0;
static int y_pos = 0;

static void __kputchar_at(char c, uint8_t color, int x, int y);

static void __kputchar_at(char c, uint8_t color, int x, int y) {
    int pos;
	
	pos = y * VGA_SCREEN_WIDTH + x;
	video_memory[pos] = vga_entry(c, color);
}

void __kclear(void)
{
	uint8_t  default_color;
	uint32_t i;

	default_color = vga_entry_color(TTY_FG_COLOR, TTY_BG_COLOR);
	i = 0;

	while(i < VGA_SCREEN_WIDTH * VGA_SCREEN_HEIGHT) {
		video_memory[i] = vga_entry(' ', default_color);
		i++;
	}
}

void kprint(const char *str)
{
	uint32_t i;

	i = 0;
	while(str[i]) {
		kputchar(str[i]);	
		i++;
	}
}

void kprintc(const char* str, vga_color_t fg, vga_color_t bg) 
{
    uint8_t color;
	int i;

    color = vga_entry_color(fg, bg);
	i = 0;

    while (str[i]) {
		__kputchar_at(str[i], color, x_pos, y_pos);
		i++;
	}
}

void kputchar(const int c)
{
	uint8_t default_color;
	
	default_color = vga_entry_color(TTY_FG_COLOR, TTY_BG_COLOR);

	switch(c) {
		case '\n':
			y_pos++;
			x_pos = 0;
			return;
		
		default:
			__kputchar_at(c, default_color, x_pos, y_pos);
			x_pos++;
			break;
	};

	if(x_pos >= VGA_SCREEN_WIDTH) {
		x_pos = 0;
		y_pos++;
	}
	
	if(y_pos >= VGA_SCREEN_HEIGHT) {
		for (int i = 0; i < VGA_SCREEN_WIDTH - 1; i++) {
			for (int j = VGA_SCREEN_HEIGHT - 2; j > 0; j--)
			
				video_memory[(j * VGA_SCREEN_WIDTH) + i] = video_memory[((j + 1) * VGA_SCREEN_WIDTH) + i];
		}
		
		for (int i = 0; i < VGA_SCREEN_WIDTH - 1; i++)
			__kputchar_at(' ', default_color, i, VGA_SCREEN_HEIGHT - 1);
	
		y_pos = VGA_SCREEN_HEIGHT - 1;
	
	}

	update_cursor(x_pos, y_pos);	
}
