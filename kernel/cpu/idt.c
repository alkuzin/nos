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

#include <nos/string.h>
#include <nos/idt.h>
#include <nos/irq.h>

#include <asm/io.h>

idt_entry_t idt_entries[256];
idt_ptr_t   idt_ptr;

extern void idt_flush(u32);

void idt_init(void)
{
    idt_ptr.limit = sizeof(idt_entries) - 1;
    idt_ptr.base  = (u32) &idt_entries;

    bzero(&idt_entries, sizeof(idt_entries));

    /* chips initialization mode */
    outb(0x20, 0x11);
    outb(0xA0, 0x11);

    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    
    outb(0x21, 0x0);
    outb(0xA1, 0x0);

    set_idt_gate(0, (u32)isr0, 0x08, 0x8E);
    set_idt_gate(1, (u32)isr1, 0x08, 0x8E);
    set_idt_gate(2, (u32)isr2, 0x08, 0x8E);
    set_idt_gate(3, (u32)isr3, 0x08, 0x8E);
    set_idt_gate(4, (u32)isr4, 0x08, 0x8E);
    set_idt_gate(5, (u32)isr5, 0x08, 0x8E);
    set_idt_gate(6, (u32)isr6, 0x08, 0x8E);
    set_idt_gate(7, (u32)isr7, 0x08, 0x8E);
    set_idt_gate(8, (u32)isr8, 0x08, 0x8E);
    set_idt_gate(9, (u32)isr9, 0x08, 0x8E);
    set_idt_gate(10, (u32)isr10, 0x08, 0x8E);
    set_idt_gate(11, (u32)isr11, 0x08, 0x8E);
    set_idt_gate(12, (u32)isr12, 0x08, 0x8E);
    set_idt_gate(13, (u32)isr13, 0x08, 0x8E);
    set_idt_gate(14, (u32)isr14, 0x08, 0x8E);
    set_idt_gate(15, (u32)isr15, 0x08, 0x8E);
    set_idt_gate(16, (u32)isr16, 0x08, 0x8E);
    set_idt_gate(17, (u32)isr17, 0x08, 0x8E);
    set_idt_gate(18, (u32)isr18, 0x08, 0x8E);
    set_idt_gate(19, (u32)isr19, 0x08, 0x8E);
    set_idt_gate(20, (u32)isr20, 0x08, 0x8E);
    set_idt_gate(21, (u32)isr21, 0x08, 0x8E);
    set_idt_gate(22, (u32)isr22, 0x08, 0x8E);
    set_idt_gate(23, (u32)isr23, 0x08, 0x8E);
    set_idt_gate(24, (u32)isr24, 0x08, 0x8E);
    set_idt_gate(25, (u32)isr25, 0x08, 0x8E);
    set_idt_gate(26, (u32)isr26, 0x08, 0x8E);
    set_idt_gate(27, (u32)isr27, 0x08, 0x8E);
    set_idt_gate(28, (u32)isr28, 0x08, 0x8E);
    set_idt_gate(29, (u32)isr29, 0x08, 0x8E);
    set_idt_gate(30, (u32)isr30, 0x08, 0x8E);
    set_idt_gate(31, (u32)isr31, 0x08, 0x8E);

    set_idt_gate(32, (u32)irq0, 0x08, 0x8E);
    set_idt_gate(33, (u32)irq1, 0x08, 0x8E);
    set_idt_gate(34, (u32)irq2, 0x08, 0x8E);
    set_idt_gate(35, (u32)irq3, 0x08, 0x8E);
    set_idt_gate(36, (u32)irq4, 0x08, 0x8E);
    set_idt_gate(37, (u32)irq5, 0x08, 0x8E);
    set_idt_gate(38, (u32)irq6, 0x08, 0x8E);
    set_idt_gate(39, (u32)irq7, 0x08, 0x8E);
    set_idt_gate(40, (u32)irq8, 0x08, 0x8E);
    set_idt_gate(41, (u32)irq9, 0x08, 0x8E);
    set_idt_gate(42, (u32)irq10, 0x08, 0x8E);
    set_idt_gate(43, (u32)irq11, 0x08, 0x8E);
    set_idt_gate(44, (u32)irq12, 0x08, 0x8E);
    set_idt_gate(45, (u32)irq13, 0x08, 0x8E);
    set_idt_gate(46, (u32)irq14, 0x08, 0x8E);
    set_idt_gate(47, (u32)irq15, 0x08, 0x8E);

    set_idt_gate(128, (u32)isr128, 0x08, 0x8E);
    set_idt_gate(177, (u32)isr177, 0x08, 0x8E);      

    idt_flush((u32) &idt_ptr);
}

void set_idt_gate(u8 num, u32 base, u16 sel, u8 flags)
{
    idt_entries[num].base_low  = (base & 0xFFFF);
    idt_entries[num].base_high = ((base >> 0x10) & 0xFFFF);
    idt_entries[num].sel       = sel;
    idt_entries[num].always0   = 0;
    idt_entries[num].flags     = (flags | 0x60);
}
