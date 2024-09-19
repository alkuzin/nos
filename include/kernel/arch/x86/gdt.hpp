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
 * @file  gdt.hpp
 * @brief Contains GDT and TSS structures and management functions.
 * 
 * @details 
 * Global Descriptor Table (GDT) is a structure specific to the IA-32
 * and x86-64 architectures. It contains entries telling the CPU about memory segments.
 * 
 * The TSS is used for hardware task switching and contains 
 * information about the state of a task.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   15.05.2024 
 */

#ifndef _KERNEL_ARCH_X86_GDT_HPP_
#define _KERNEL_ARCH_X86_GDT_HPP_

#include <kernel/kstd/types.hpp>


namespace kernel {
namespace arch {
namespace x86 {

/**
 * @brief GDT entry (segment descriptor) - tells the CPU the attributes of a given segment.
 * 
 * @warning Order of segment descriptor content is important!
 */
struct gdt_entry_s {
    u16 limit;
    u16 base_low;
    u8  base_mid;
    u8  access;
    u8  flags;
    u8  base_high;
} __attribute__((packed)); // prevent the compiler from optimizing

using gdt_entry_t = gdt_entry_s;

/** @brief GDT pointer structure.*/
struct gdt_ptr_s {
    u16 limit;
    u32 base;
} __attribute__((packed)); // prevent the compiler from optimizing

using gdt_ptr_t = gdt_ptr_s;

/** @brief TSS (Task State Segment) entry.*/
struct tss_entry_s {
    u32 prev_tss;   // previous TSS entry
    u32 esp0;       // stack pointer register 0
    u32 ss0;        // stack segment register 0
    u32 esp1;       // stack pointer register 1
    u32 ss1;        // stack segment register 1
    u32 esp2;       // stack pointer register 2
    u32 ss2;        // stack segment register 2
    u32 cr3;        // control register
    u32 eip;        // instruction pointer
    u32 eflags;     // flags register
    u32 eax;        // extended accumulator register
    u32 ecx;        // extended counter register
    u32 edx;        // extended data register
    u32 ebx;        // extended base register
    u32 esp;        // extended stack pointer
    u32 ebp;        // extended base pointer
    u32 esi;        // extended source index
    u32 edi;        // extended destination index
    u32 es;         // extra segment
    u32 cs;         // code segment
    u32 ss;         // stack segment
    u32 ds;         // data segment
    u32 fs;         // additional segment
    u32 gs;         // global segment
    u32 ldt;        // Local Descriptor Table register
    u32 trap;       // flag in the EFLAGS register
    u32 iomap_base; // input/output map base register
} __attribute__((packed)); // prevent the compiler from optimizing

using tss_entry_t = tss_entry_s;

/** @brief initialize Global Descriptor Table.*/
void gdt_init(void);

/**
 * @brief Set the Global Descriptor Table content.
 * 
 * @param [in] num - given GDT entry number.
 * @param [in] base - given base address of the segment.
 * @param [in] limit - given limit of the segment.
 * @param [in] access - given access byte for the segment.
 * @param [in] gran - given granularity and size information.
 */
void set_gdt_gate(u32 num, u32 base, u32 limit, u8 access, u8 gran);

/**
 * @brief Write Task State Segment (TSS) entry.
 * 
 * @param [in] num - given TSS entry number.
 * @param [in] ss0 - given stack segment for privilege level 0.
 * @param [in] esp0 - given stack pointer for privilege level 0.
 */
void tss_write(u32 num, u16 ss0, u32 esp0);
    
} // namespace x86
} // namespace arch
} // namespace kernel

#endif //_KERNEL_ARCH_X86_GDT_HPP_