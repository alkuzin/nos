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

#ifndef _KERNEL_GDT_H_
#define _KERNEL_GDT_H_

#include <libk/stdint.h>

/*
GDT entry (segment descriptor) - tells the CPU the attributes of a given segment
warning: order of segment descriptor content is important
*/

struct gdt_entry_s {
    uint16_t limit;
    uint16_t base_low;
    uint8_t  base_mid;
    uint8_t  access;
    uint8_t  flags;
    uint8_t  base_high;
} __attribute__((packed)); /* prevent the compiler from optimizing */

typedef struct gdt_entry_s gdt_entry_t;

struct gdt_ptr_s {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)); /* prevent the compiler from optimizing */

typedef struct gdt_ptr_s gdt_ptr_t;

/* initialize Global Descriptor Table */
void gdt_init(void);

/* set Global Descriptor Table content */
void set_gdt_gate(uint32_t num, uint32_t base, uint32_t limit, 
                  uint8_t access, uint8_t gran);

#endif /* _KERNEL_GDT_H_ */
