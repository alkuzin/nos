/**
 * The Null Operating System (NOS).
 * Copyright (C) 2024  Alexander (@alkuzin).
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

/**
 * @file  idt.hpp
 * @brief Contains IDT structures and management functions.
 *
 * @details 
 * IDT (Interrupt Descriptor Table) - telling the CPU where 
 * the Interrupt Service Routines (ISR) are located.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   15.05.2024 
 */

#ifndef _NOS_KERNEL_IDT_HPP_
#define _NOS_KERNEL_IDT_HPP_

#include <nos/types.hpp>

namespace kernel {
namespace core {

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

} // namespace core
} // namespace kernel


#endif /* _NOS_KERNEL_IDT_HPP_ */