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

#include <arch/x86/io.hpp>
#include <nos/timer.hpp>
#include <nos/types.hpp>
#include <nos/irq.hpp>


namespace kernel {
namespace driver {
    
const u32 freq = 100;
u32 ticks;

void timer_delay(u32 seconds)
{
    (void)seconds;
    // TODO: implement
}

void on_irq0([[gnu::unused]] core::int_reg_t *regs)
{
    ticks++;
}

void timer_init(void)
{
    u32 divisor;

    ticks = 0;
    irq_install_handler(0, &on_irq0);

    divisor = 1193180 / freq; /* MHz */

    arch::x86::outb(0x43, 0x36);
    arch::x86::outb(0x40, (u8)(divisor & 0xFF));
    arch::x86::outb(0x40, (u8)((divisor >> 8) & 0xFF));
}

} // namespace driver
} // namespace kernel