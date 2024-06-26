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

#include <nos/stdarg.h>
#include <nos/printk.h> 
#include <nos/types.h>
#include <nos/gfx.h>
#include <nos/tty.h>

#define BUF_SIZE 1024

static char buf[BUF_SIZE];


void vprintk(const char *fmt, va_list args)
{
    va_list args_copy;

    va_copy(args_copy, args);
    vsnprintk(buf, BUF_SIZE, fmt, args);
    va_end(args_copy);

	putk(buf);
}

void printk(const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    vsnprintk(buf, BUF_SIZE, fmt, args);
    va_end(args);

    putk(buf);
}

void kmesg(bool state, const char *fmt, ...)
{
    va_list args;
    
    kputchar('[');

    if (state)
        cputk(" OK ", GFX_COLOR_GREEN, tty_get_bg());
    else
        cputk(" ERR ", GFX_COLOR_RED, tty_get_bg());
    
    kputchar(']');
    kputchar(' ');

    va_start(args, fmt);    
    vprintk(fmt, args);
    va_end(args);
}

void putk(const char *str)
{
    u32 i;

    i = 0;
    while(str[i]) {
        kputchar(str[i]);       
        i++;
	}
}

void cputk(const char *str, rgb_t fg, rgb_t bg)
{
	s32 i;

	i = 0;

    while (str[i]) {
        kputchar_c(str[i], fg, bg);
		i++;
	}
}