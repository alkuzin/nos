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

#ifndef _KERNEL_IDT_H_
#define _KERNEL_IDT_H_

#include <libk/stdint.h>

/* 
IDT (Interrupt Descriptor Table) - telling the CPU where 
the Interrupt Service Routines (ISR) are located
*/

struct idt_entry_s {
    uint16_t base_low;    
    uint16_t sel;    
    uint8_t  always0;    
    uint8_t  flags;    
    uint16_t base_high;    
} __attribute__((packed)); /* prevent the compiler from optimizing */

typedef struct idt_entry_s idt_entry_t;

struct idt_ptr_s {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)); /* prevent the compiler from optimizing */

typedef struct idt_ptr_s idt_ptr_t;

/* initialize Interrupt Descriptor Table */
void idt_init(void);

/* set Interrupt Descriptor Table content */
void set_idt_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);

#endif /* _KERNEL_IDT_H_ */
