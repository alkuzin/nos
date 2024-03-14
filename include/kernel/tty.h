/*
MIT License

Copyright (c) 2024 Alexander (@alkuzin)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef _KERNEL_TTY_H_
#define _KERNEL_TTY_H_ 

#include <libk/stdarg.h>
#include <kernel/vga.h>

#define TTY_FG_COLOR  VGA_COLOR_WHITE
#define TTY_BG_COLOR  VGA_COLOR_BLUE
#define TTY_TAB_WIDTH 4

/* for NULL pointer in kprintf */
#define __NIL__ "(nil)"

/* The kvprintf() variadic function thats formats and prints data */
void kvprintf(const char *fmt, va_list args);

/* The kprintf() formats and prints data */
void kprintf(const char *fmt, ...);

/* print colored text to screen */
void kprintc(const char* str, enum vga_color fg, enum vga_color bg);

/* print text to screen */
void kprint(const char *str);

/* print character to screen */
void kputchar(const int c);

/* kernel panic (detecting an internal fatal error) */
void kpanic(const char *fmt, ...);

/* clear screen */
void __kclear(void);

/* get cursor x position */
int __vga_get_x(void);

/* get cursor y position */
int __vga_get_y(void);

#endif /* _KERNEL_TTY_H_ */
