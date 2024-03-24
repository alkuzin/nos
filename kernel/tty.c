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

#include <kernel/kernel.h>
#include <libk/stdint.h>
#include <libk/memory.h>
#include <kernel/tty.h>
#include <kernel/vga.h>
#include <libk/ctype.h>

/* video memory address */
static uint16_t *video_memory = (uint16_t *)VIDEO_MEMORY;

/* x & y positions of the cursor */
static int x_pos = 0;
static int y_pos = 0;

/* foreground & background default color */
static uint8_t default_color = (uint8_t)(TTY_FG_COLOR | TTY_BG_COLOR << 4);

/* print char with custom color in a specific place */
static void __kputchar_at(char c, uint8_t color, int x, int y);

/* VGA scroll function */
static void __kscroll(void);


void __set_default_color(vga_color_t fg, vga_color_t bg) {
    default_color = (uint8_t)(fg | bg << 4);
}

static void __kputchar_at(char c, uint8_t color, int x, int y) {
	video_memory[y * VGA_SCREEN_WIDTH + x] = vga_entry(c, color);
}

static void __kscroll(void)
{
	uint16_t buffer[(VGA_SCREEN_WIDTH * VGA_SCREEN_HEIGHT * 2)];

	memset(buffer, default_color, sizeof(buffer));
	memcpy(buffer, video_memory,  sizeof(buffer));

	__kclear();

    for (uint16_t y = 0; y < VGA_SCREEN_HEIGHT; y++) {
        for (uint16_t x = 0; x < VGA_SCREEN_WIDTH; x++)
            buffer[(y-1) * VGA_SCREEN_WIDTH + x] = buffer[y*VGA_SCREEN_WIDTH+x];
    }

    for (uint16_t x = 0; x < VGA_SCREEN_WIDTH; x++) {
        buffer[(VGA_SCREEN_HEIGHT-1) * VGA_SCREEN_WIDTH + x] = ' ' | default_color;
    }
	
    memcpy(video_memory, buffer, sizeof(buffer));
}

void __kclear(void)
{
	uint32_t i;

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

void kpanic(const char *fmt, ...)
{
	va_list args;
	
	va_start(args, fmt);
    kprintf("kernel: panic: ");
	kvprintf(fmt, args);
    va_end(args);

	khalt();
}

int __tty_get_x(void) {
    return x_pos;
}

int __tty_get_y(void) {
    return y_pos;
}

void __tty_set_x(int x) {
    x_pos = x;
}

void __tty_set_y(int y) {
    y_pos = y;
}
