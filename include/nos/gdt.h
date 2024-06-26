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
 * @file  gdt.h
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

#ifndef _NOS_KERNEL_GDT_H_
#define _NOS_KERNEL_GDT_H_

#include <nos/types.h>

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
} __attribute__((packed)); /* prevent the compiler from optimizing */

typedef struct gdt_entry_s gdt_entry_t;

/** @brief GDT pointer structure. */
struct gdt_ptr_s {
    u16 limit;
    u32 base;
} __attribute__((packed)); /* prevent the compiler from optimizing */

typedef struct gdt_ptr_s gdt_ptr_t;

/** @brief TSS (Task State Segment) entry. */
struct tss_entry_s {
    u32 prev_tss;   ///< previous TSS entry
    u32 esp0;       ///< stack pointer register 0
    u32 ss0;        ///< stack segment register 0
    u32 esp1;       ///< stack pointer register 1
    u32 ss1;        ///< stack segment register 1
    u32 esp2;       ///< stack pointer register 2
    u32 ss2;        ///< stack segment register 2
    u32 cr3;        ///< control register
    u32 eip;        ///< instruction pointer
    u32 eflags;     ///< flags register
    u32 eax;        ///< extended accumulator register
    u32 ecx;        ///< extended counter register
    u32 edx;        ///< extended data register
    u32 ebx;        ///< extended base register
    u32 esp;        ///< extended stack pointer
    u32 ebp;        ///< extended base pointer
    u32 esi;        ///< extended source index
    u32 edi;        ///< extended destination index
    u32 es;         ///< extra segment
    u32 cs;         ///< code segment
    u32 ss;         ///< stack segment
    u32 ds;         ///< data segment
    u32 fs;         ///< additional segment
    u32 gs;         ///< global segment
    u32 ldt;        ///< Local Descriptor Table register
    u32 trap;       ///< flag in the EFLAGS register
    u32 iomap_base; ///< input/output map base register
} __attribute__((packed)); ///< prevent the compiler from optimizing

typedef struct tss_entry_s tss_entry_t;

/** @brief initialize Global Descriptor Table */
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

#endif /* _NOS_KERNEL_GDT_H_ */