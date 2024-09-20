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

/**
 * @file  framebuffer.hpp
 * @brief Contains declarations for multiboot framebuffer.
 * 
 * @details This header file includes macro related to the VBE mode font.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   20.09.2024
 */

#ifndef _KERNEL_GFX_FRAMEBUFFER_HPP_
#define _KERNEL_GFX_FRAMEBUFFER_HPP_

#include <kernel/kstd/types.hpp>
#include <kernel/multiboot.hpp>


namespace kernel {
namespace gfx {

class Framebuffer
{
    u32 *m_addr;    // framebuffer address
    u32  m_pitch;   // number of bytes in a single row of the framebuffer
    u32  m_width;   // y-resolution
    u32  m_height;  // x-resolution
    u8   m_bpp;     // bytes per pixel

public:
    Framebuffer(Framebuffer&&)            = delete; // prevent moving
    Framebuffer& operator=(Framebuffer&&) = delete; // prevent moving assignment
    virtual ~Framebuffer(void)            = default;

    /** @brief Framebuffer default constructor.*/
    Framebuffer(void) noexcept = default;
    Framebuffer(const Framebuffer&) = default;

    /**
     * @brief Construct a new Framebuffer object.
     * 
     * @param [in] mboot - given multiboot information structure.
     */
    Framebuffer(const multiboot_info_t& mboot) noexcept;

    /**
     * @brief Copy assignment operation overloading.
     * 
     * @return new Framebuffer object. 
     */
    Framebuffer& operator=(const Framebuffer&) noexcept = default;
    
    /**
     * @brief Get framebuffer address.
     * 
     * @return framebuffer address.
     */
    u32 *addr(void) const noexcept;

    /**
     * @brief Get number of bytes in a single row of the framebuffer.
     * 
     * @return framebuffer pitch.
     */
    u32 pitch(void) const noexcept;

    /**
     * @brief Get framebuffer width in pixels.
     * 
     * @return framebuffer width.
     */
    u32 width(void) const noexcept;

    /**
     * @brief Get framebuffer height in pixels.
     * 
     * @return framebuffer height.
     */
    u32 height(void) const noexcept;

    /**
     * @brief Get framebuffer bytes per pixel.
     * 
     * @return framebuffer bytes per pixel.
     */
    u8 bpp(void) const noexcept;

    /**
     * @brief Get framebuffer number of bytes allocated for the framebuffer.
     * 
     * @return framebuffer size in bytes.
     */
    u32 size(void) const noexcept;
};

} // namespace gfx
} // namespace kernel

#endif // _KERNEL_GFX_FRAMEBUFFER_HPP_