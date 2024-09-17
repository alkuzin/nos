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

#include <arch/x86/gdt.hpp>
#include <nos/string.hpp>


extern "C" void gdt_flush(kernel::u32);
extern "C" void tss_flush(void);


namespace kernel {
namespace arch {
namespace x86 {

gdt_entry_t gdt_entries[6];
gdt_ptr_t   gdt_ptr;
tss_entry_t tss_entry;

void set_gdt_gate(u32 num, u32 base, u32 limit, u8 access, u8 gran)
{
    gdt_entries[num].base_low  = (base & 0xFFFF);
    gdt_entries[num].base_mid  = ((base >> 0x10) & 0xFF);
    gdt_entries[num].base_high = ((base >> 0x18) & 0xFF);
    gdt_entries[num].limit     = (limit & 0xFFFF);
    gdt_entries[num].flags     = ((limit >> 0x10) & 0x0F);
    gdt_entries[num].flags     |= (gran & 0xF0);
    gdt_entries[num].access    = access;
}

void gdt_init(void)
{
    gdt_ptr.limit = (sizeof(gdt_entry_t) * 6) - 1;
    gdt_ptr.base  = (u32) &gdt_entries;

    /* null segment (required by convention) */
    set_gdt_gate(0, 0, 0, 0, 0); 
    
    /* kernel code segment
     *
     * Access byte 0x9A = 1001 1010, where:
     * 
     * 1 - present bit (must be set 1 for any valid segment)
     * 00 - descriptor privilege level field (highest privilege (kernel))
     * 1 - descriptor type bit (system segment)
     *
     * 1 - executable bit (defines a code or data segment)
     * 0 - direction bit (segment grows up)
     * 1 - readable/writable bit (read access is allowed)
     * 0 - accessed bit (always 0 when not accessed by CPU) */
    set_gdt_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    /* kernel data segment */
    set_gdt_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    /* user code segment */
    set_gdt_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);

    /* user data segment */
    set_gdt_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    tss_write(5, 0x10, 0x0);

    gdt_flush((u32) &gdt_ptr);
    tss_flush();
}

void tss_write(u32 num, u16 ss0, u32 esp0)
{
    u32 base, limit;

    base  = (u32) &tss_entry;
    limit = base + sizeof(tss_entry);

    set_gdt_gate(num, base, limit, 0xE9, 0x00);
    lib::bzero(&tss_entry, sizeof(tss_entry));

    tss_entry.ss0  = ss0;
    tss_entry.esp0 = esp0;

    /* switch to kernel mode from user mode */
    tss_entry.cs = 0x08 | 0x3; 
    tss_entry.es = 0x10 | 0x3;
    tss_entry.ds = 0x10 | 0x3;
    tss_entry.ss = 0x10 | 0x3;
    tss_entry.fs = 0x10 | 0x3;
    tss_entry.gs = 0x10 | 0x3;
}

} // namespace x86
} // namespace arch
} // namespace kernel