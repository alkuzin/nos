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

#include <kernel/arch/x86/io.hpp>
#include <kernel/drivers/vbe.hpp>


namespace kernel {
namespace driver {
namespace vbe {

/**
 * @brief Set VBE params.
 * 
 * @param [in] index - given index to set. 
 * @param [in] data - given data to set. 
 */
static constexpr inline void write(u16 index, u16 data) noexcept
{
    arch::x86::outw(VBE_DISPI_IOPORT_INDEX, index);
    arch::x86::outw(VBE_DISPI_IOPORT_DATA, data);
}

void init(const multiboot_info_t& mboot) noexcept
{
    write(0x00, 0x4F02); // set VBE mode
    write(0x01, mboot.framebuffer_width);
    write(0x02, mboot.framebuffer_height);
    write(0x03, mboot.framebuffer_bpp);
    write(0x04, VBE_DISPI_ENABLED | VBE_DISPI_LFB_ENABLED); // enable LFB mode
}

} // namespace vbe
} // namespace driver
} // namespace kernel