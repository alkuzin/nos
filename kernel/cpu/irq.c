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

#include <nos/panic.h>
#include <nos/types.h>
#include <nos/idt.h>
#include <nos/irq.h>

#include <asm/system.h>
#include <asm/io.h>

char *exception_msgs[] = {
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

void isr_handler(int_reg_t *regs)
{
    if(regs->int_no < 32)
        panic(" %s\n", exception_msgs[regs->int_no]);
}

static irq_handler_t irq_routines[16] = {nullptr};

void irq_install_handler(s32 irq, irq_handler_t handler) 
{
    irq_routines[irq] = handler;
    sti();
}

void irq_uninstall_handler(s32 irq) {
    irq_routines[irq] = 0;
}

void irq_handler(int_reg_t *regs)
{
    void (*handler)(int_reg_t *regs);

    handler = irq_routines[regs->int_no - 32];

    if(handler)
        handler(regs);

    if(regs->int_no >= 40)
        outb(0xA0, 0x20);

    outb(0x20, 0x20);
}