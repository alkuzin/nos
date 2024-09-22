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
 * @file  array.hpp
 * @brief It includes declaration of array class.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   20.09.2024 
 */

#ifndef _KERNEL_KSTD_ARRAY_HPP_
#define _KERNEL_KSTD_ARRAY_HPP_

#include <kernel/kstd/types.hpp>
#include <kernel/klog.hpp>


namespace kernel {
namespace kstd {

template <typename T, usize N>
class array
{
    T m_data[N];

public:
    array(void)          = default;
    virtual ~array(void) = default;

    /**
     * @brief Construct a new array object.
     * 
     * @param [in] arr - given C-style array.
     */
    constexpr array(const T (&arr)[N]) noexcept;

    /**
     * @brief Get elelment at specified position.
     * 
     * @param [in] pos - given element position.
     * @return element.
     */
    constexpr T at(usize pos) const noexcept;

    /**
     * @brief Get array data.
     * 
     * @return pointer to array data.
     */
    constexpr T *data(void) const noexcept;

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
     * @brief Fill array with specific value.
     * 
     * @param [in] value - given value to fill with.
     */
    constexpr void fill(const T& value) noexcept;

    /**
     * @brief Get elelment at specified position.
     * 
     * @param [in] pos - given element position.
     * @return element.
     */
    constexpr const T& operator[](usize pos) const noexcept;
    
    /**
     * @brief Get elelment at specified position.
     * 
     * @param [in] pos - given element position.
     * @return element.
     */
    constexpr T& operator[](usize pos) noexcept;

    /**
     * @brief Get first element.
     * 
     * @return first element pointer.
     */
    constexpr T* begin(void) noexcept;
    
    /**
     * @brief Get first element.
     * 
     * @return first element pointer.
     */
    constexpr const T* begin(void) const noexcept;
    
    /**
     * @brief Get last element.
     * 
     * @return last element pointer.
     */
    constexpr T* end(void) noexcept;
    
    /**
     * @brief Get last element.
     * 
     * @return last element pointer.
     */
    constexpr const T* end(void) const noexcept;
};

template <typename T, usize N>
constexpr array<T, N>::array(const T (&arr)[N]) noexcept
{
    for (usize i = 0; i < N; i++)
        m_data[i] = arr[i];
}

template <typename T, usize N>
constexpr T array<T, N>::at(usize pos) const noexcept
{
    if (pos >= N)
        log::error("%s\n", "given position out of range");
    
    return m_data[pos];
}

template <typename T, usize N>
constexpr T *array<T, N>::data(void) const noexcept
{
    return m_data;
}

template <typename T, usize N>
constexpr bool array<T, N>::empty(void) const noexcept
{
    return N == 0;
}

template <typename T, usize N>
constexpr usize array<T, N>::size(void) const noexcept
{
    return N;
}

template <typename T, usize N>
constexpr const T& array<T, N>::operator[](usize pos) const noexcept
{
    return m_data[pos];
}

template <typename T, usize N>
constexpr T& array<T, N>::operator[](usize pos) noexcept
{
    return m_data[pos];
}

template <typename T, usize N>
constexpr void array<T, N>::fill(const T& value) noexcept
{
    for (auto& x : m_data)
        x = value;
}

template <typename T, usize N>
constexpr T* array<T, N>::begin(void) noexcept
{
    return &m_data[0];
}

template <typename T, usize N>
constexpr const T* array<T, N>::begin(void) const noexcept
{
    return &m_data[0];
}

template <typename T, usize N>
constexpr T* array<T, N>::end(void) noexcept
{
    return &m_data[N];
}

template <typename T, usize N>
constexpr const T* array<T, N>::end(void) const noexcept
{
    return &m_data[N];
}

} // namespace kstd
} // namespace kernel

#endif // _KERNEL_KSTD_ARRAY_HPP_