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

/**
 * @file  idt.h
 * @brief Contains IDT structures and management functions.
 *
 * @details 
 * IDT (Interrupt Descriptor Table) - telling the CPU where 
 * the Interrupt Service Routines (ISR) are located.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   15.05.2024 
 */

#ifndef _NOS_KERNEL_IDT_H_
#define _NOS_KERNEL_IDT_H_

#include <stdint.h>

/** @brief Interrupt Descriptor Table entry structure */
struct idt_entry_s {
    u16 base_low;    
    u16 sel;    
    u8  always0;    
    u8  flags;    
    u16 base_high;    
} __attribute__((packed)); /* prevent the compiler from optimizing */

typedef struct idt_entry_s idt_entry_t;

/** @brief Interrupt Descriptor Table pointer structure */
struct idt_ptr_s {
    u16 limit;
    u32 base;
} __attribute__((packed)); /* prevent the compiler from optimizing */

typedef struct idt_ptr_s idt_ptr_t;

/** @brief  initialize Interrupt Descriptor Table. */
void idt_init(void);

/**
 * @brief Set Interrupt Descriptor Table (IDT) gate.
 * 
 * @param [in] num - given IDT entry number.
 * @param [in] base - given base address of the interrupt handler.
 * @param [in] sel - given code segment selector.
 * @param [in] flags - given flags and type of the interrupt gate.
 */
void set_idt_gate(u8 num, u32 base, u16 sel, u8 flags);

#endif /* _NOS_KERNEL_IDT_H_ */