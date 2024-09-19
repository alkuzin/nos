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
 * @file  byte.hpp
 * @brief It includes declaration of byte data type.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   18.09.2024 
 */

#ifndef _KERNEL_KSTD_BYTE_HPP_
#define _KERNEL_KSTD_BYTE_HPP_


namespace kernel {
namespace kstd {
    
enum class byte : unsigned char {};

// Operators overloading: (<<, <<=, >>, >>=):

/**
 * @brief Left shift operator overloading.
 * 
 * @param [in] b - given byte to shift.
 * @param [in] shift - given number of bits to shift.
 * @return shifted byte. 
 */
template <typename IntegerType>
constexpr inline byte operator<<(byte b, IntegerType shift) noexcept
{
    return byte(static_cast<unsigned int>(b) << shift);
}

/**
 * @brief Left shift assignment operator overloading.
 * 
 * @param [in] b - given byte to shift.
 * @param [in] shift - given number of bits to shift.
 * @return shifted byte.
 */
template <typename IntegerType>
constexpr inline byte& operator<<=(byte& b, IntegerType shift) noexcept
{
    return b = b << shift;
}

/**
 * @brief Right shift operator overloading.
 * 
 * @param [in] b - given byte to shift.
 * @param [in] shift - given number of bits to shift.
 * @return shifted byte. 
 */
template <typename IntegerType>
constexpr inline byte operator>>(byte b, IntegerType shift) noexcept
{
    return byte(static_cast<unsigned int>(b) >> shift);
}

/**
 * @brief Right shift assignment operator overloading.
 * 
 * @param [in] b - given byte to shift.
 * @param [in] shift - given number of bits to shift.
 * @return shifted byte. 
 */
template <typename IntegerType>
constexpr inline byte& operator>>=(byte& b, IntegerType shift) noexcept
{
    return b = b >> shift;
}

// Operators overloading: (|, |=, &, &=, ^, ^=):

/**
 * @brief OR operator overloading.
 * 
 * @param [in] l - given left byte.
 * @param [in] r - given right byte.
 * @return result of OR operation.
 */
constexpr inline byte operator|(byte l, byte r) noexcept
{
    return byte(static_cast<unsigned int>(l) | static_cast<unsigned int>(r));
}

/**
 * @brief OR assignment operator overloading.
 * 
 * @param [in] l - given left byte.
 * @param [in] r - given right byte.
 * @return result of OR operation.
 */
constexpr inline byte& operator|=(byte& l, byte r) noexcept
{
    return l = l | r;
}

/**
 * @brief AND operator overloading.
 * 
 * @param [in] l - given left byte.
 * @param [in] r - given right byte.
 * @return result of AND operation.
 */
constexpr inline byte operator&(byte l, byte r) noexcept
{
    return byte(static_cast<unsigned int>(l) & static_cast<unsigned int>(r));
}

/**
 * @brief AND assignment operator overloading.
 * 
 * @param [in] l - given left byte.
 * @param [in] r - given right byte.
 * @return result of AND operation.
 */
constexpr inline byte& operator&=(byte& l, byte r) noexcept
{
    return l = l & r;
}

/**
 * @brief XOR operator overloading.
 * 
 * @param [in] l - given left byte.
 * @param [in] r - given right byte.
 * @return result of XOR operation.
 */
constexpr inline byte operator^(byte l, byte r) noexcept
{
    return byte(static_cast<unsigned int>(l) ^ static_cast<unsigned int>(r));
}

/**
 * @brief XOR assignment operator overloading.
 * 
 * @param [in] l - given left byte.
 * @param [in] r - given right byte.
 * @return result of XOR operation.
 */
constexpr inline byte& operator^=(byte& l, byte r) noexcept
{
    return l = l ^ r;
}

// Operators overloading: (~, []):

/**
 * @brief NOT operator overloading.
 * 
 * @param [in] b - given byte to inverse. 
 * @return result of NOT operation.
 */
constexpr inline byte operator~(byte l) noexcept
{
    return byte(~static_cast<unsigned int>(l));
}

} // namespace kstd
} // namespace kernel

#endif // _KERNEL_KSTD_BYTE_HPP_