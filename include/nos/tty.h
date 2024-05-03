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

/* default kernel TTY foreground & background color */
#define TTY_FG_COLOR  VGA_COLOR_WHITE
#define TTY_BG_COLOR  VGA_COLOR_BLUE
#define TTY_TAB_WIDTH 4

/* for NULL pointer in kprintf */
#define __NIL__ "(nil)"

typedef struct tty_s {
    u16 *v_mem;     /* video memory address */    
    i32 x_pos;      /* x position of the cursor */
    i32 y_pos;      /* y position of the cursor */
    vga_color_t fg; /* foreground color */
    vga_color_t bg; /* background color */
    u8  color;      /* VGA entry color */
    i32 height;     /* screen height */
    i32 width;      /* screen width */
} tty_t;

/* initialize kernel TTY structure */
void tty_init(void);

/* get cursor x position */
i32  tty_get_x(void);

/* get cursor y position */
i32  tty_get_y(void);

/* set cursor x position */
void tty_set_x(i32 x);

/* set cursor y position */
void tty_set_y(i32 y);

/* get kernel TTY structure foreground color */
vga_color_t tty_get_fg(void);

/* get kernel TTY structure background color */
vga_color_t tty_get_bg(void);

/* set foreground & background color */
void tty_set_color(vga_color_t fg, vga_color_t bg);

/* get screen height */
i32  tty_get_height(void);

/* get screen width */
i32  tty_get_width(void);

/* clear screen */
void tty_clear(void);

/* print char with custom color in a specific place */
void tty_kputchar_at(char c, u8 color, i32 x, i32 y);

/* print character to screen */
void kputchar(const i32 c);

#endif /* _NOS_KERNEL_TTY_H_ */
