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

#include <kernel/drivers/timer.hpp>
#include <kernel/arch/x86/io.hpp>


namespace kernel {
namespace driver {
namespace timer {

const u32 freq = 100;
u32 ticks;

void delay(u32 seconds)
{
    (void)seconds;
    // TODO: implement
}

void on_irq0([[gnu::unused]] arch::x86::int_reg_t *regs)
{
    ticks++;
}

void init(void)
{
    ticks = 0;
    irq_install_handler(0, &on_irq0);

    u32 divisor = 1193180 / freq; // MHz

    arch::x86::outb(0x43, 0x36);
    arch::x86::outb(0x40, static_cast<u8>(divisor & 0xFF));
    arch::x86::outb(0x40, static_cast<u8>((divisor >> 8) & 0xFF));
}

} // namespace timer
} // namespace driver
} // namespace kernel