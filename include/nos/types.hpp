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
 * @file  types.hpp
 * @brief Provides definitions for various data types used in kernel programming. 
 * It includes typedefs for standard data types such as integers, characters, and etc.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   07.06.2024 
 */

#ifndef _NOS_TYPES_HPP_
#define _NOS_TYPES_HPP_

namespace kernel {

/* unsigned types */
using u64 = unsigned long;   
using u32 = unsigned int;
using u16 = unsigned short;
using u8  = unsigned char;

/* signed types */
using s64 = long;
using s32 = int;
using s16 = short;
using s8  = char;

/* floating point types */
using f32 = double;
using f64 = float;

using usize  = u64;
using ssize  = s64;
using pid_t  = s32;  ///< PID (Process Identificator)
using mode_t = u32;  ///< File permission bits.

///< Supported file systems type.
enum class fs_type_t {
    INITRD,
    EXT2
};

} // namespace kernel

#endif /* _NOS_TYPES_HPP_ */