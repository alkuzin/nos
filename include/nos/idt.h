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

#ifndef _NOS_KERNEL_IDT_H_
#define _NOS_KERNEL_IDT_H_

#include <stdint.h>

/* IDT (Interrupt Descriptor Table) - telling the CPU where 
 * the Interrupt Service Routines (ISR) are located */

struct idt_entry_s {
    u16 base_low;    
    u16 sel;    
    u8  always0;    
    u8  flags;    
    u16 base_high;    
} __attribute__((packed)); /* prevent the compiler from optimizing */

typedef struct idt_entry_s idt_entry_t;

struct idt_ptr_s {
    u16 limit;
    u32 base;
} __attribute__((packed)); /* prevent the compiler from optimizing */

typedef struct idt_ptr_s idt_ptr_t;

/* initialize Interrupt Descriptor Table */
void idt_init(void);

/* set Interrupt Descriptor Table content */
void set_idt_gate(u8 num, u32 base, u16 sel, u8 flags);

#endif /* _NOS_KERNEL_IDT_H_ */
