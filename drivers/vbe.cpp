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
#include <nos/vbe.hpp>
#include <nos/gfx.hpp>


namespace kernel {
namespace driver {

/**
 * @brief Set VBE params.
 * 
 * @param [in] index - given index to set. 
 * @param [in] data - given data to set. 
 */
static constexpr inline void vbe_write(u16 index, u16 data) noexcept
{
    arch::x86::outw(VBE_DISPI_IOPORT_INDEX, index);
    arch::x86::outw(VBE_DISPI_IOPORT_DATA, data);
}

/**
 * @brief Set VBE video mode.
 * 
 * @param [in] width - given screen width.
 * @param [in] height - given screen height.
 * @param [in] depth - given number of bits per pixel.
 * @param [in] pitch - given number of bytes per scanline.
 * @param [in] fb_addr - given framebuffer pointer.
 */
static constexpr void vbe_set_video_mode(u16 width, u16 height, u16 depth, u16 pitch, u32 *fb_addr) noexcept
{
    gfx::gfx_set_framebuffer(fb_addr);
    gfx::gfx_set_height(height);
    gfx::gfx_set_width(width);
    gfx::gfx_set_pitch(pitch);

    vbe_write(0x00, 0x4F02); // set VBE mode
    vbe_write(0x01, width);
    vbe_write(0x02, height);
    vbe_write(0x03, depth);
    vbe_write(0x04, VBE_DISPI_ENABLED | VBE_DISPI_LFB_ENABLED); // enable LFB mode
}

void vbe_init(const multiboot_info_t& mboot)
{
    vbe_set_video_mode(
        mboot.framebuffer_width,
        mboot.framebuffer_height,
        mboot.framebuffer_bpp,
        mboot.framebuffer_pitch,
        reinterpret_cast<u32*>(mboot.framebuffer_addr)
    );
}

} // namespace driver
} // namespace kernel