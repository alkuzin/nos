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

#include <stdio.h>

#include <nos/shell/ksh.h>
#include <nos/kernel.h> 
#include <nos/nosstd.h>
#include <nos/sched.h>
#include <nos/types.h>
#include <nos/tty.h>
#include <nos/vga.h>
#include <nos/exe.h>
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
           " lsproc       - display list of current processes\n"
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

void ksh_lsproc(void)
{
    sched_t *scheduler;
    pcb_t   *proc;

    scheduler = get_sched();

    puts(" ------------------------------------------\n"
         " | pid | pr | ppid | name |   base | size |\n"
         " ------------------------------------------");

    for (s32 i = 0; i < scheduler->rear + 1; i++) {
        proc = scheduler->processes[i];
        printk("   %u |  %u  |  %u | %s | %#x | %u \n", proc->pid, proc->priority, 
        proc->parent_pid, proc->name, proc->base, proc->size);
    }

    puts(" ------------------------------------------ ");
    printk(" \n total processes: %d\n", scheduler->rear + 1);   
}

void ksh_readexe(void)
{
    // TODO: exstract exe header from file

    // if (!exe_is_valid(header))
    //     printk(" readexe: not NOS executable file. Incorrect signature: '%s'\n", 
    //     (char *)header->signature);

    // exe_display_info(header);
}