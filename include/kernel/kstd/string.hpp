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
 * @file  string.hpp
 * @brief It includes declaration of string class.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   20.09.2024 
 */

#ifndef _KERNEL_KSTD_STRING_HPP_
#define _KERNEL_KSTD_STRING_HPP_

#include <kernel/kstd/cstring.hpp>
#include <kernel/klog.hpp>


namespace kernel {
namespace kstd {

class string
{
    const char *m_data;
    usize       m_size;

public:
    /** @brief Construct new string object.*/
    constexpr string(void) noexcept;

    /** @brief Construct new string object.*/
    constexpr string(const string& other) noexcept;

    virtual ~string(void) noexcept = default;
    
    /**
     * @brief Construct new string object.
     * 
     * @param [in] str - given C-like string.
     */
    constexpr string(const char *str) noexcept;
    
    /**
     * @brief Get elelment at specified position.
     * 
     * @param [in] pos - given element position.
     * @return element.
     */
    constexpr char at(usize pos) const noexcept;

    /**
     * @brief Get array data.
     * 
     * @return pointer to array data.
     */
    constexpr const char *data(void) const noexcept;
    
    /**
     * @brief Check if array is empty.
     * 
     * @return true - if array is empty.
     * @return false - otherwise.
     */
    constexpr bool empty(void) const noexcept;

    /**
     * @brief Get number of elements.
     * 
     * @return array size. 
     */
    constexpr usize size(void) const noexcept;
    
    /**
     * @brief Get elelment at specified position.
     * 
     * @param [in] pos - given element position.
     * @return element.
     */
    constexpr char operator[](usize pos) const noexcept;
    
    /**
     * @brief Get first element.
     * 
     * @return first element pointer.
     */
    constexpr const char* begin(void) const noexcept;
    
    /**
     * @brief Get last element.
     * 
     * @return last element pointer.
     */
    constexpr const char* end(void) noexcept;

    /**
     * @brief Compare current string with other.
     * 
     * @param [in] other - given other string object.
     * @param [in] n - given number of first symbols to compare.
     * @return 0, if strings are equal.
     * @return a negative value, if this string is less than other.
     * @return positive value - otherwise.
     */
    constexpr s32 compare(const string& other, usize n) const noexcept;
    
    /**
     * @brief Assignment operator overloading.
     * 
     * @param [in] str - given C-like string.
     * @return new string object.
     */
    constexpr string& operator=(const char *str) noexcept;
    
    /**
     * @brief Assignment operator overloading.
     * 
     * @param [in] other - given other string object.
     * @return new string object.
     */
    constexpr string& operator=(const string& other) noexcept;
};

// --------------------------------------------------------------------------------------

constexpr string::string(void) noexcept : m_data(nullptr), m_size(0) {}

constexpr string::string(const char *str) noexcept : m_data(str), m_size(str ? strlen(str) : 0) {}

constexpr string::string(const string& other) noexcept : m_data(other.m_data), m_size(other.m_size) {}

constexpr char string::at(usize pos) const noexcept
{
    if (pos >= m_size)
        log::error("%s\n", "given position out of range");
    
    return m_data[pos];
}

constexpr const char *string::data(void) const noexcept
{
    return m_data;
}

constexpr bool string::empty(void) const noexcept
{
    return m_data == nullptr;
}

constexpr usize string::size(void) const noexcept
{
    return m_size == 0;
}

constexpr char string::operator[](usize pos) const noexcept
{
    return m_data[pos];
}

constexpr const char* string::begin(void) const noexcept
{
    return m_data;
}
    
constexpr const char* string::end(void) noexcept
{
    return m_data + m_size;
}

constexpr s32 string::compare(const string& other, usize n) const noexcept
{
    return strncmp(m_data, other.m_data, n);
}

constexpr string& string::operator=(const string& other) noexcept
{
    if (this != &other) {
        m_data = other.m_data;
        m_size = other.m_size;
    }

    return *this;
}

constexpr string& string::operator=(const char *str) noexcept
{
    m_data = str;
    m_size = strlen(str);

    return *this;
}

} // namespace kstd
} // namespace kernel

#endif // _KERNEL_KSTD_STRING_HPP_