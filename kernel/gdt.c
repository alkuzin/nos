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

#include <libk/memory.h>
#include <kernel/gdt.h>


extern void gdt_flush(uint32_t);
extern void tss_flush(void);

gdt_entry_t gdt_entries[6];
gdt_ptr_t   gdt_ptr;
tss_entry_t tss_entry;


void set_gdt_gate(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    gdt_entries[num].base_low  = (base & 0xFFFF);
    gdt_entries[num].base_mid  = ((base >> 0xF) & 0xFF);
    gdt_entries[num].base_high = ((base >> 0x18) & 0xFF);
    gdt_entries[num].limit     = (limit & 0xFFFF);
    gdt_entries[num].flags     = ((limit >> 0xF) & 0x0F);
    gdt_entries[num].flags     |= (gran & 0xF0);
    gdt_entries[num].access    = access;
}

void gdt_init(void)
{
    gdt_ptr.limit = (sizeof(gdt_entry_t) * 6) - 1;
    gdt_ptr.base  = (uint32_t) &gdt_entries;

    /* null segment (required by convention) */
    set_gdt_gate(0, 0, 0, 0, 0); 
    
    /* kernel code segment
       
       Access byte 0x9A = 1001 1010, where:

       1 - present bit (must be set 1 for any valid segment)
       00 - descriptor privilege level field (highest privilege (kernel))
       1 - descriptor type bit (system segment)

       1 - executable bit (defines a code or data segment)
       0 - direction bit (segment grows up)
       1 - readable/writable bit (read access is allowed)
       0 - accessed bit (always 0 when not accessed by CPU)
    */
    set_gdt_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    /* kernel data segment */
    set_gdt_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    /* user code segment */
    set_gdt_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);

    /* user data segment */
    set_gdt_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    tss_write(5, 0x10, 0x0);

    gdt_flush((uint32_t) &gdt_ptr);
    tss_flush();
}

void tss_write(uint32_t num, uint16_t ss0, uint32_t esp0)
{
    uint32_t base, limit;

    base = (uint32_t) &tss_entry;
    limit = base + sizeof(tss_entry);

    set_gdt_gate(num, base, limit, 0xE9, 0x00);
    bzero(&tss_entry, sizeof(tss_entry));

    tss_entry.ss0 = ss0;
    tss_entry.esp0 = esp0;

    /* switch to kernel mode from user mode */
    tss_entry.cs = 0x08 | 0x3; 
    tss_entry.es = 0x10 | 0x3;
    tss_entry.ds = 0x10 | 0x3;
    tss_entry.ss = 0x10 | 0x3;
    tss_entry.fs = 0x10 | 0x3;
    tss_entry.gs = 0x10 | 0x3;
}
