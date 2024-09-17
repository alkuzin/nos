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

#include <arch/x86/system.hpp>
#include <arch/x86/idt.hpp>
#include <arch/x86/irq.hpp>
#include <arch/x86/io.hpp>
#include <nos/panic.hpp>


namespace kernel {
namespace arch {
namespace x86 {
    
const char *exception_msgs[] = {
    "division by zero",
    "debug",
    "non maskable interrupt",
    "breakpoint",
    "into detected overflow",
    "out of bounds",
    "invalid opcode",
    "no coprocessor",
    "double fault",
    "coprocessor segment overrun",
    "bad TSS",
    "segment not present",
    "stack fault",
    "general protection fault",
    "page fault",
    "unknown interrupt",
    "coprocessor fault",
    "alignment fault",
    "machine check",
    "reserved",
    "reserved",
    "reserved",
    "reserved",
    "reserved",
    "reserved",
    "reserved",
    "reserved",
    "reserved",
    "reserved",
    "reserved",
    "reserved",
    "reserved"
};

static irq_handler_t irq_routines[16] = {nullptr};

void irq_install_handler(s32 irq, irq_handler_t handler) 
{
    irq_routines[irq] = handler;
    arch::x86::sti();
}

void irq_uninstall_handler(s32 irq)
{
    irq_routines[irq] = 0;
}

} // namespace x86
} // namespace arch
} // namespace kernel

extern "C" void irq_handler(kernel::arch::x86::int_reg_t *regs)
{
    void (*handler)(kernel::arch::x86::int_reg_t *regs);

    handler = kernel::arch::x86::irq_routines[regs->int_no - 32];

    if(handler)
        handler(regs);

    if(regs->int_no >= 40)
        kernel::arch::x86::outb(0xA0, 0x20);

    kernel::arch::x86::outb(0x20, 0x20);
}

extern "C" void isr_handler(kernel::arch::x86::int_reg_t *regs)
{
    if(regs->int_no < 32)
        kernel::lib::panic(" %s\n", kernel::arch::x86::exception_msgs[regs->int_no]);
}