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
 * @file  rgb.hpp
 * @brief Contains declarations for RGB pixel.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   20.09.2024
 */

#ifndef _KERNEL_GFX_RGB_HPP_
#define _KERNEL_GFX_RGB_HPP_

#include <kernel/kstd/types.hpp>


namespace kernel {
namespace gfx {

/** @brief RGB color structure.*/
struct rgb {
    u8 m_red;
    u8 m_green;
    u8 m_blue;

    constexpr rgb(void) noexcept = default;

    /**
     * @brief Create RGB color.
     * 
     * @param [in] r - given red color.
     * @param [in] g - given green color.
     * @param [in] b - given blue color.
     * @return constexpr rgb 
     */
    constexpr rgb(u8 red, u8 green, u8 blue) noexcept;

    /**
     * @brief Three-way comparison operator overloading.
     * 
     * @param [in] other - given other RGB object to compare.
     */
    auto operator<=>(const rgb& other) const noexcept = default;
};

constexpr rgb::rgb(u8 red, u8 green, u8 blue) noexcept : m_red(red), m_green(green), m_blue(blue) {}

namespace color {
constexpr rgb red    = rgb(255, 0, 0);
constexpr rgb green  = rgb(0, 255, 0);
constexpr rgb blue   = rgb(0, 0, 255);
constexpr rgb black  = rgb(0, 0, 0);
constexpr rgb white  = rgb(255, 255, 255);
constexpr rgb brown  = rgb(176, 92, 53);
constexpr rgb purple = rgb(128, 0, 255);
constexpr rgb gray   = rgb(191, 191, 191);
} // namespace color

} // namespace gfx
} // namespace kernel

#endif // _KERNEL_GFX_RGB_HPP_