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

#include <kernel/arch/x86/system.hpp>
#include <kernel/arch/x86/irq.hpp>
#include <kernel/arch/x86/io.hpp>
#include <kernel/drivers/pit.hpp>


namespace kernel {
namespace driver {

static usize _ticks = 0;

/**
 * @brief Inerrupt handler.
 * 
 * @param [in] regs - given pointer to interrupt register state.
 */
static void handler(arch::x86::int_reg_t *regs)
{
    (void)regs;
    _ticks++;
}

PIT::PIT(void) noexcept : m_frequency(100), m_divisor(11931180 / m_frequency /* MHz */)
{
    m_name = "Programmable Interval Timer";
}

void PIT::initialize(void) noexcept {}

void PIT::handle_interrupt(void) const noexcept
{
    arch::x86::irq_install_handler(0, &handler);

    arch::x86::outb(0x43, 0x36);
    arch::x86::outb(0x40, static_cast<u8>(m_divisor & 0xFF));
    arch::x86::outb(0x40, static_cast<u8>((m_divisor >> 8) & 0xFF));
}

void PIT::delay(usize msec) const noexcept
{
    (void)msec;
    // TODO: implement
}

usize PIT::ticks(void) const noexcept
{
    return _ticks;
}

PIT timer;

} // namespace driver
} // namespace kernel