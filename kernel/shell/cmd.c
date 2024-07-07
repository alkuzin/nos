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

#include <nos/shell/ksh.h>
#include <nos/printk.h>
#include <nos/initrd.h> 
#include <nos/nosstd.h>
#include <nos/sched.h>
#include <nos/types.h>
#include <nos/tty.h>
#include <nos/exe.h>
#include <nos/mm.h>

#include <asm/io.h>


void ksh_warning(const char *cmd)
{
    printk("ksh: %s: command not found \n", cmd);
}

void ksh_help(void)
{
    putk("help, ?      - display information about builtin commands.\n"
         "clear        - clear screen\n"
         "uname        - print system information\n"
         "ls           - display list of files\n"
         "cat          - display file content\n"
         "free         - display list of free memory\n"
         "theme <id>   - set CLI theme\n"
         "ps           - display list of current processes\n"
         "reboot       - reboot OS\n"
         "shutdown     - shutdown OS\n"
         "gfx          - test graphics\n\n"
    );
}

void ksh_clear(void)
{
    tty_clear();
}

void ksh_free(void)
{
    u32 max_blocks, used_blocks, phys_mem_total, phys_mem_free; 
    u32 free_blocks, total_bytes, used_bytes, free_bytes;
    
    max_blocks     = pmm_get_max_blocks();
    used_blocks    = pmm_get_used_blocks();
    phys_mem_total = pmm_get_phys_mem_total();
    phys_mem_free  = pmm_get_phys_mem_free();
    free_blocks    = max_blocks - used_blocks;
    total_bytes    = max_blocks  * BLOCK_SIZE;
    used_bytes     = used_blocks * BLOCK_SIZE;
    free_bytes     = free_blocks * BLOCK_SIZE;

    printk("\nMem: \n\t total: %u KB   free: %u KB   used: %u KB\n\n", phys_mem_total >> 10, 
    phys_mem_free >> 10, (phys_mem_total - phys_mem_free) >> 10);
    putk("Blocks:\n\n");
    printk("\ttotal: %u (%u KB) (%u MB)\n", max_blocks, total_bytes >> 10, total_bytes >> 20);
    printk("\tused : %u (%u KB) (%u MB)\n", used_blocks, used_bytes >> 10, used_bytes >> 20);
    printk("\tfree : %u (%u KB) (%u MB)\n \n", free_blocks, free_bytes >> 10, free_bytes >> 20);
}

void ksh_theme(theme_t theme)
{
    rgb_t fg, bg, primary_color, secondary_color;

    switch (theme) {

        case THEME_DEFAULT:
            fg              = GFX_COLOR_WHITE;
            bg              = GFX_COLOR_BLACK;
            primary_color   = GFX_COLOR_GRAY;
            secondary_color = GFX_COLOR_BLACK;
            break;
        
        case THEME_CLASSIC:
            fg              = GFX_COLOR_WHITE;
            bg              = GFX_COLOR_BLUE;
            primary_color   = GFX_COLOR_WHITE;
            secondary_color = GFX_COLOR_BLUE;
            break;
        
        case THEME_GREEN_BLACK:
            fg              = GFX_COLOR_GREEN;
            bg              = GFX_COLOR_BLACK;
            primary_color   = GFX_COLOR_GREEN;
            secondary_color = GFX_COLOR_BLACK;
            break;
        
        case THEME_BROWN_BLACK:
            fg              = GFX_COLOR_BROWN;
            bg              = GFX_COLOR_BLACK;
            primary_color   = GFX_COLOR_BROWN;
            secondary_color = GFX_COLOR_BLACK;
            break;
        
        case THEME_PURPLE_BLACK:
            fg              = GFX_COLOR_PURPLE;
            bg              = GFX_COLOR_BLACK;
            primary_color   = GFX_COLOR_PURPLE;
            secondary_color = GFX_COLOR_BLACK;
            break;
    
        default:
            printk("theme: incorrect theme \"%d\" \nksh: type \"help\""
                   " to see list of available commands\n", theme);
            return;
    }
    
    tty_set_color(fg, bg);
    tty_set_primary_color(primary_color);
    tty_set_secondary_color(secondary_color);

    tty_update();
}

void ksh_ps(void)
{
    putk("comming soon ...\n");
    // sched_t *scheduler;
    // pcb_t   *proc;

    // scheduler = get_sched();

    // puts(" ------------------------------------------\n"
    //      " | pid | pr | ppid | name |   base | size |\n"
    //      " ------------------------------------------");

    // for (s32 i = 0; i < scheduler->rear + 1; i++) {
    //     proc = scheduler->processes[i];
    //     printk("   %u |  %u  |  %u | %s | %#x | %u \n", proc->pid, proc->priority, 
    //     proc->parent_pid, proc->name, proc->base, proc->size);
    // }

    // puts(" ------------------------------------------ ");
    // printk(" \n total processes: %d\n", scheduler->rear + 1);   
}

void ksh_readexe(void)
{
    // TODO: exstract exe header from file

    // if (!exe_is_valid(header))
    //     printk(" readexe: not NOS executable file. Incorrect signature: '%s'\n", 
    //     (char *)header->signature);

    // exe_display_info(header);
}

void ksh_cat(const char *pathname)
{
    char buffer[INITRD_FILE_SIZE];
    s32 fd, ret;

    fd = vfs_open(pathname, O_RDONLY);

    if (fd == -1) {
        printk("cat: error to open file \"%s\"\n", pathname);
        return;
    }

    ret = vfs_read(fd, buffer, INITRD_FILE_SIZE);

    if (ret == -1)
        printk("cat: error to read file \"%s\"\n", pathname);
    
    printk("%s", buffer);

    ret = vfs_close(fd);

    if (ret == -1)
        printk("cat: error to close file \"%s\"\n", pathname);
}

void ksh_reboot(void)
{
    outb(0x64, 0xFE);
}

void ksh_shutdown(void)
{
    outw(0xB004, 0x2000);
    outw(0x0604, 0x2000);
    outw(0x4004, 0x3400);
}