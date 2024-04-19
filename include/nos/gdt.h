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

#ifndef _NOS_KERNEL_GDT_H_
#define _NOS_KERNEL_GDT_H_

#include <stdint.h>

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

/* TSS (Task State Segment) entry - structure that holds information about a task. */
struct tss_entry_s {
    uint32_t prev_tss;
    uint32_t esp0; /* stack pointer register 0 */
    uint32_t ss0; /* stack segment register 0 */
    uint32_t esp1; /* stack pointer register 1 */
    uint32_t ss1; /* stack segment register 1 */
    uint32_t esp2; /* stack pointer register 2 */
    uint32_t ss2; /* stack segment register 2 */
    uint32_t cr3; /* control register */
    uint32_t eip; /* instruction pointer */
    uint32_t eflags; /* flags register */
    uint32_t eax; /* extended accumulator register */
    uint32_t ecx; /* extended counter register */
    uint32_t edx; /* extended data register */
    uint32_t ebx; /* extended base register */
    uint32_t esp; /* extended stack pointer */
    uint32_t ebp; /* extended base pointer */
    uint32_t esi; /* extended source index */
    uint32_t edi; /* extended destination index */
    uint32_t es; /* extra segment */
    uint32_t cs; /* code segment */
    uint32_t ss; /* stack segment */
    uint32_t ds; /* data segment */
    uint32_t fs; /* additional segment */
    uint32_t gs; /* global segment */
    uint32_t ldt; /* Local Descriptor Table register */
    uint32_t trap; /* flag in the EFLAGS register */
    uint32_t iomap_base; /* input/output map base register */
} __attribute__((packed)); /* prevent the compiler from optimizing */

typedef struct tss_entry_s tss_entry_t;

/* initialize Global Descriptor Table */
void gdt_init(void);

/* set Global Descriptor Table content */
void set_gdt_gate(uint32_t num, uint32_t base, uint32_t limit, 
                  uint8_t access, uint8_t gran);

void tss_write(uint32_t num, uint16_t ss0, uint32_t esp0);

#endif /* _NOS_KERNEL_GDT_H_ */
