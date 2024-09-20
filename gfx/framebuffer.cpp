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

#include <kernel/gfx/framebuffer.hpp>


namespace kernel {
namespace gfx {

Framebuffer::Framebuffer(const multiboot_info_t& mboot) noexcept
{
    m_addr   = reinterpret_cast<u32*>(mboot.framebuffer_addr);
    m_pitch  = mboot.framebuffer_pitch;
    m_width  = mboot.framebuffer_width;
    m_height = mboot.framebuffer_height;
    m_bpp    = mboot.framebuffer_bpp;
}

u32 *Framebuffer::addr(void) const noexcept
{
    return m_addr;
}

u32 Framebuffer::pitch(void) const noexcept
{
    return m_pitch;
}

u32 Framebuffer::width(void) const noexcept
{
    return m_width;
}

u32 Framebuffer::height(void) const noexcept
{
    return m_height;
}

u8 Framebuffer::bpp(void) const noexcept
{
    return m_bpp;
}

u32 Framebuffer::size(void) const noexcept
{
    return m_height * m_pitch;
}

} // namespace gfx
} // namespace kernel