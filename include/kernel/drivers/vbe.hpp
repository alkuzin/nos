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
 * @file  vbe.hpp
 * @brief Contains declarations for VBE (VESA BIOS Extensions).
 * 
 * @details This header file includes functions and structs related to the standard
 * interface for accessing advanced video modes and features on graphics hardware.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   24.06.2024
 */

#ifndef _KERNEL_DRIVER_VBE_HPP_
#define _KERNEL_DRIVER_VBE_HPP_

#include <kernel/kstd/types.hpp>
#include <kernel/multiboot.hpp>


namespace kernel {
namespace driver {
namespace vbe {

// VBE ports
constexpr u32 VBE_DISPI_IOPORT_INDEX {0x01CE};
constexpr u32 VBE_DISPI_IOPORT_DATA  {0x01CF};

// VBE control bits
constexpr u32 VBE_DISPI_ENABLED      {0x01};
constexpr u32 VBE_DISPI_LFB_ENABLED  {0x40};

/**
 * @brief Initialize VBE mode. 
 * 
 * @param [in] mboot - given multiboot information structure.
 */
void init(const multiboot_info_t& mboot) noexcept;

} // namespace vbe
} // namespace driver
} // namespace kernel

#endif // _KERNEL_DRIVER_VBE_HPP_