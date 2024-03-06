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
#include <kernel/tty.h>

static uint16_t *video_memory    = (uint16_t *)VIDEO_MEMORY;
static uint32_t cursor_pos = 0;

void __kclear(void)
{
	uint32_t i;

	i = 0;
	while(i < VGA_SCREEN_WIDTH * VGA_SCREEN_HEIGHT) {
		video_memory[i] = (video_memory[i] & 0xFF00) | ' ';
		i++;
	}
}

void kprint(const char *str)
{
	uint32_t i;

	i = 0;
	while(str[i]) {

		switch(str[i]) {
			case '\n':
    			cursor_pos = (cursor_pos / VGA_SCREEN_WIDTH + 1) * VGA_SCREEN_WIDTH;
				i++;
				continue;
		
			case '\v':
				cursor_pos += VGA_SCREEN_WIDTH;
				i++;
				continue;

			default:
				kputchar((video_memory[i] & 0xFF00) | str[i]);
				i++;
				break;
		};
	}
}

void kputchar(const int c)
{
	switch(c) {
		case '\n':
    		cursor_pos = (cursor_pos / VGA_SCREEN_WIDTH + 1) * VGA_SCREEN_WIDTH;
			return;
		
		case '\v':
			cursor_pos += VGA_SCREEN_WIDTH;
			return;
		
		default:
			video_memory[cursor_pos] = (video_memory[cursor_pos] & 0xFF00) | c;
			cursor_pos++;
			break;
	};
}
