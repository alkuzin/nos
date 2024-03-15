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
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/mm.h>

void __ksleep(uint32_t microsec)
{
	uint32_t i;

	for (i = 0; i < microsec * 10000; i++) {
		for (i = 0; i < microsec * 10000; i++)
			__asm__ volatile ("nop"); /* do nothing */
	}
}

void ksleep(uint32_t sec) {
	__ksleep(sec * 10000);
}

void khalt(void) 
{
	__asm__ volatile("cli"); /* disable interrupts */

	for(;;);
}

/* kernel entry point */
extern void kmain(uint32_t magic, multiboot_t *boot_info)
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

    /* initializing keyboard */
    keyboard_init();
    kprint(" kernel: initialized keyboard \n");	
    
    /* initializing memory management */

    uint32_t mod1, physical_alloc_start;

    mod1 = *(uint32_t *)(boot_info->mods_addr + 4);
    physical_alloc_start = ((mod1 + 0xFFF) & ~0xFFF);

    kprintf("\n kernel: set magic number:     %#X\n", magic);
    kprintf(" kernel: set mod1:             %#X\n", mod1);
    kprintf(" kernel: physical_alloc_start: %#X\n\n", physical_alloc_start);
    
    memory_init(boot_info->mem_upper * 1024, physical_alloc_start);
    kprint(" kernel: initialized memory management \n");	

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
	

	for(;;); /* infinite loop for halting CPU */
}
