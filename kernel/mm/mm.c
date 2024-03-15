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

/*
Global Descriptor Table (GDT) is a structure specific to the IA-32 
and x86-64 architectures. It contains entries telling the CPU about memory segments.
*/

#include <kernel/multiboot.h>
#include <libk/stdint.h>
#include <kernel/tty.h>
#include <kernel/mm.h>

void memory_init(multiboot_t *boot_info)
{
    multiboot_mmap_entry_t *mmmt;

    for(uint32_t i = 0; i < boot_info->mmap_length; i += sizeof(multiboot_mmap_entry_t)) {
       mmmt = (multiboot_mmap_entry_t *)(boot_info->mmap_addr + i);

       kprintf("\n low addr:   <%#x> | high addr:   <%#x>\n", mmmt->addr_low, mmmt->addr_high);
       kprintf(" low length: <%#x> | high lenght: <%#x>\n", mmmt->len_low, mmmt->len_high);
       kprintf(" size:        %#x  | type:           %u\n\n", mmmt->size, mmmt->type);
    }
}
