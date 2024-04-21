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
#include <string.h>

#include <nos/shell/ksh.h>
#include <nos/multiboot.h>
#include <nos/keyboard.h>
#include <nos/unistd.h>
#include <nos/kernel.h>
#include <nos/timer.h>
#include <nos/tty.h>
#include <nos/gdt.h>
#include <nos/idt.h>
#include <nos/mm.h>


void kboot(multiboot_t *boot_info)
{
	__kclear(); /* clear screen */
    
    /* initializing Global Descriptor Table */
    gdt_init();
    kprint(" kernel: initialized Global Descriptor Table \n");	
    
    /* initializing Interrupt Descriptor Table */
    idt_init();
    kprint(" kernel: initialized Interrupt Descriptor Table \n");	
    
    /* initializing timer */
    timer_init();
    kprint(" kernel: initialized timer \n");	

    /* initializing memory management */
    memory_init(boot_info);
    kprint(" kernel: initialized memory management\n");	

    __DISPLAY_OS_INFO();
    __DISPLAY_OS_BUILD_INFO();

    /* initializing kernel shell */
    kprint(" kernel: initializing kernel shell\n");	
    ksh_init(boot_info);
}

/* kernel entry point */
extern void kmain(__attribute__((unused)) u32 magic, multiboot_t *boot_info)
{
    __set_default_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    kboot(boot_info);

	for(;;); /* infinite loop for halting CPU */
}
