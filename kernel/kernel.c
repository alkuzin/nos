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

#include <kernel/multiboot.h>
#include <kernel/keyboard.h>
#include <kernel/kernel.h>
#include <kernel/timer.h>
#include <libk/memory.h>
#include <kernel/sstd.h>
#include <kernel/tty.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/mm.h>
#include <shell/ksh.h>


/* kernel entry point */
extern void kmain(uint32_t magic, multiboot_t *boot_info)
{
    __set_default_color(VGA_COLOR_WHITE, VGA_COLOR_BLUE);

	__kclear(); /* clear screen */
    kprintf("\n kernel: set magic number: %#X\n", magic);
    
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

	/* display OS banner */
    kprintf(
    "    _____            __        ____  ____      \n"
    "   / __(_)_ _  ___  / /__ ____/ __ \\/ __/     \n"
    "  _\\ \\/ /  ' \\/ _ \\/ / -_)___/ /_/ /\\ \\  \n"
    " /___/_/_/_/_/ .__/_/\\__/    \\____/___/      \n"
    "            /_/                              \n\n"
    " %s (%s %s) (c) @alkuzin - 2024\n"
    " ---------------------------------------------\n\n\n", 
    __OS_NAME__, __OS_VERSION__, __OS_ARCH__);

    /* initializing kernel shell */
    ksh_init(boot_info);
    kprint(" kernel: initialized kernel shell\n");	


	for(;;); /* infinite loop for halting CPU */
}
