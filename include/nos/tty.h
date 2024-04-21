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

#ifndef _NOS_KERNEL_TTY_H_
#define _NOS_KERNEL_TTY_H_ 

#include <stdarg.h>

#include <nos/vga.h>

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
void kprintc(const char* str, vga_color_t fg, vga_color_t bg);

/* print text to screen */
void kprint(const char *str);

/* print character to screen */
void kputchar(const i32 c);

/* clear screen */
void __kclear(void);

/* get cursor x position */
i32 __tty_get_x(void);

/* get cursor y position */
i32 __tty_get_y(void);

/* set cursor x position */
void __tty_set_x(i32 x);

/* set cursor y position */
void __tty_set_y(i32 y);

void __set_default_color(vga_color_t fg, vga_color_t bg);

#endif /* _NOS_KERNEL_TTY_H_ */
