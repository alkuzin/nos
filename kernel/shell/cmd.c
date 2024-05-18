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
#include <stdio.h>

#include <nos/shell/ksh.h>
#include <nos/kernel.h> 
#include <nos/nosstd.h>
#include <nos/tty.h>
#include <nos/vga.h>
#include <nos/mm.h>


void ksh_warning(const char *cmd)
{
    printk(" ksh: incorrect command \"%s\"\n ksh: type \"help\""
           " to see list of available commands\n", cmd);
}

void ksh_clear(void)
{
    tty_clear();

    tty_set_x(0);
    tty_set_y(0);
    update_cursor(0, 0);
}

void ksh_lsmem(multiboot_t *boot_info)
{
    pmm_display_memory(boot_info);
}

void ksh_help(void)
{
    /* TODO: add command for displaying kernel info */
    putk("----------------------< help >------------------------\n"
           " help         - display this help menu\n"
           " clear        - clear screen\n"
           " lsmem        - display list of memory segments\n"
           " theme_0      - set CLI theme to default\n"
           " theme_1      - set CLI theme to classic\n"
           "------------------------------------------------------\n");
}

void ksh_theme(theme_t theme)
{
    vga_color_t fg, bg;

    switch (theme)
    {
        case THEME_DEFAULT:
            fg = VGA_COLOR_WHITE;
            bg = VGA_COLOR_BLACK;
            break;
        
        case THEME_CLASSIC:
            fg = VGA_COLOR_WHITE;
            bg = VGA_COLOR_BLUE;
            break;
    
        default:
            printk(" ksh: incorrect theme \"%d\"\n ksh: type \"help\""
                    " to see list of available commands\n", theme);
            return;
    }
    
    tty_set_color(fg, bg);
    tty_rewrite();    
}