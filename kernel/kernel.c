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

#include <string.h>

#include <nos/shell/ksh.h>
#include <nos/multiboot.h>
#include <nos/keyboard.h>
#include <nos/nosstd.h>
#include <nos/kernel.h>
#include <nos/timer.h>
#include <nos/types.h>
#include <nos/sched.h>
#include <nos/tty.h>
#include <nos/gdt.h>
#include <nos/idt.h>
#include <nos/vfs.h>
#include <nos/mm.h>
#include <nos/pm.h>


void kboot(multiboot_t *boot_info)
{
    /* initializing kernel TTY */
    tty_init();
    tty_set_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
	tty_clear(); 
    printk(" %s\n", "kernel: initialized TTY");	

    /* initializing Global Descriptor Table */
    gdt_init();
    printk(" %s\n", "kernel: initialized Global Descriptor Table");
    
    /* initializing Interrupt Descriptor Table */
    idt_init();
    printk(" %s\n", "kernel: initialized Interrupt Descriptor Table");	
    
    /* initializing timer */
    timer_init();
    printk(" %s\n", "kernel: initialized timer");	

    /* initializing memory management */
    memory_init(boot_info);
    printk(" %s\n", "kernel: initialized memory management");

    __DISPLAY_OS_INFO();
    __DISPLAY_OS_BUILD_INFO();

    /* initializing Virtual File System */
    vfs_init();
    printk(" %s\n", "kernel: initialized Virtual File System");

    /* initializing process scheduler */
    sched_init();
    printk(" %s\n", "kernel: initialized scheduler");	

    /* Create initial system processes */
    pcb_t *init_proc, *ksh_proc;

    init_proc = pm_create_proc("init", HIGH_PRIORITY);
    ksh_proc  = pm_create_proc("ksh", MEDIUM_PRIORITY);

    sched_add(init_proc);
    sched_add(ksh_proc);

    /* initializing kernel shell */
    printk(" %s\n", "kernel: initializing kernel shell");
    ksh_init(boot_info);
}

/* kernel entry point */
extern void kmain(__attribute__((unused)) u32 magic, multiboot_t *boot_info)
{
    kboot(boot_info);

    for(;;); /* infinite loop for halting CPU */
}
