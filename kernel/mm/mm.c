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

#include <nos/multiboot.h>
#include <nos/tty.h>
#include <nos/pmm.h>
#include <nos/vmm.h>
#include <nos/mm.h>
#include <stdint.h>


void memory_init(multiboot_t *boot_info)
{
    uint32_t start_addr, size;
    bool vmm_status;

    if(!(boot_info->flags >> 6 & 0x1))
        kpanic("invalid memory map given by GRUB bootloader");

    /* initializing physical memory manager */

    /* set start address, size of available memory
       set total, used & free physical memory */
    pmm_get_memory(boot_info, &start_addr, &size);
    pmm_init(start_addr, size);
    
    /* free some available blocks of memory */
    pmm_region_init(start_addr, size / BITS_PER_BYTE);
    
    /* initializing virtual memory manager */
    vmm_status = vmm_init();

    if(!vmm_status)
        kpanic("%s\n", "virtual memory manager initialization error");
}
