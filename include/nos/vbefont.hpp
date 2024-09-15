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
 * @file  vbefont.hpp
 * @brief Contains declarations for VBE font.
 * 
 * @details This header file includes macro related to the VBE mode font.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   26.06.2024
 */

#ifndef _NOS_KERNEL_VBEFONT_HPP_
#define _NOS_KERNEL_VBEFONT_HPP_

#include <nos/types.hpp>


namespace kernel {

#define VBE_FONT_SIZE   4096
#define VBE_CHAR_HEIGHT 16
#define VBE_CHAR_WIDTH  8

extern u8 vbefont[VBE_FONT_SIZE];

} // namespace kernel

#endif /* _NOS_KERNEL_VBEFONT_HPP_ */