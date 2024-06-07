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
 * @file  multiboot.h
 * @brief Contains multiboot information structures decalarations.
 * 
 * @details This header file includes functions related to the
 * physical and virtual memory managing.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   17.05.2024 
 */

#ifndef _NOS_KERNEL_MULTIBOOT_H_
#define _NOS_KERNEL_MULTIBOOT_H_

#include <nos/types.h>

/** @brief Structure representing the symbol table for a.out format. */
struct multiboot_aout_symbol_table_s {
    u32 tabsize;    ///< Size of the symbol table
    u32 strsize;    ///< Size of the string table
    u32 addr;       ///< Address of the symbol table
    u32 reserved;   ///< Reserved field
};

/** @brief Structure representing the section header table for ELF format. */
struct multiboot_elf_section_header_table_s {
    u32 num;    ///< Number of section headers
    u32 size;   ///< Size of each section header
    u32 addr;   ///< Address of the section header table
    u32 shndx;  ///< Section header index
};

/** @brief Type representing multiboot information. */
typedef struct {
    u32 flags;       ///< Flags indicating available information
    u32 mem_lower;   ///< Lower memory size in KB
    u32 mem_upper;   ///< Upper memory size in KB
    u32 boot_device; ///< Boot device
    u32 cmdline;     ///< Command line
    u32 mods_count;  ///< Number of modules
    u32 mods_addr;   ///< Address of the module list
    union {
        struct multiboot_aout_symbol_table_s aout_sym;       ///< A.OUT symbol table
        struct multiboot_elf_section_header_table_s elf_sec; ///< ELF section header table
    } u; ///< Union for symbol table or section header table
    u32 mmap_length;        ///< Length of memory map
    u32 mmap_addr;          ///< Address of memory map
    u32 drives_length;      ///< Length of drive information
    u32 drives_addr;        ///< Address of drive information
    u32 config_table;       ///< Configuration table
    u32 boot_loader_name;   ///< Boot loader name
    u32 apm_table;          ///< APM table
    u32 vbe_control_info;   ///< VBE control information
    u32 vbe_mode_info;      ///< VBE mode information
    u16 vbe_mode;           ///< VBE mode
    u16 vbe_interface_seg;  ///< VBE interface segment
    u16 vbe_interface_off;  ///< VBE interface offset
    u16 vbe_interface_len;  ///< VBE interface length
} multiboot_t;

/** @brief Structure representing a memory map entry in multiboot format. */
struct multiboot_mmap_entry_s {
    u32 size;       ///< Size of the memory map entry
    u32 addr_low;   ///< Lower address of the memory region
    u32 addr_high;  ///< Higher address of the memory region
    u32 len_low;    ///< Lower length of the memory region
    u32 len_high;   ///< Higher length of the memory region
#define MULTIBOOT_MEMORY_AVAILABLE              1
#define MULTIBOOT_MEMORY_RESERVED               2
#define MULTIBOOT_MEMORY_ACPI_RECLAIMABLE       3
#define MULTIBOOT_MEMORY_NVS                    4
#define MULTIBOOT_MEMORY_BADRAM                 5
    u32 type;       ///< Type of memory region
} __attribute__((packed)); /*Prevent the compiler from optimizing*/

/** @brief Type representing a memory map entry in multiboot format. */
typedef struct multiboot_mmap_entry_s multiboot_mmap_entry_t;

#endif /* _NOS_KERNEL_MULTIBOOT_H_ */