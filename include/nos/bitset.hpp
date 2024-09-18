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
 * @file  bitset.hpp
 * @brief It includes declaration of bitset class.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   18.09.2024 
 */

#ifndef _NOS_KERNEL_BITSET_HPP_
#define _NOS_KERNEL_BITSET_HPP_

#include <nos/string.hpp>


namespace kernel {
namespace lib {

static constexpr inline usize bitset_words(usize n) noexcept
{
    return static_cast<usize>((n + 7) / 8);
}

static constexpr inline usize get_set_bits(u64 n) noexcept
{
    usize count = 0;

    while (n) {
        n &= (n - 1);
        count++;
    }

    return count;
}

template <usize N>
class bitset
{
    u64 m_data[bitset_words(N)];

private:
    /**
     * @brief Get the specific bit.
     * 
     * @param [in] pos - given bit position.
     * @return true - if bit is 1.
     * @return false - if bit is 0.
     */
    constexpr bool get_bit(usize pos) const noexcept;
    
    /**
     * @brief Set the specific bit.
     * 
     * @param [in] pos - given bit position.
     */
    constexpr void set_bit(usize pos, bool value = true) noexcept;
    
    /**
     * @brief Flip the specific bit.
     * 
     * @param [in] pos - given bit position.
     */
    constexpr void flip_bit(usize pos) noexcept;

public:
    /** @brief Default bitset constructor.*/
    explicit bitset(void) noexcept;
    
    /** @brief virtual bitset destructor.*/
    virtual ~bitset(void) = default;

    /**
     * @brief Get the number of bits that the bitset holds.
     * 
     * @return number of bits.
     */
    constexpr usize size(void) const noexcept;

    /**
     * @brief Get the number of bits set to 1.
     * 
     * @return number of bits set to 1.
     */
    constexpr usize count(void) const noexcept;

    /**
     * @brief Get value of the specific bit.
     * 
     * @param [in] pos - given bit position.
     * @return true - if bit is 1.
     * @return false - if bit is 0.
     */
    constexpr bool test(usize pos) const noexcept;

    /**
     * @brief Get the specific bit.
     * 
     * @param [in] pos - given bit position.
     * @return true - if bit is 1.
     * @return false - if bit is 0.
     */
    constexpr bool operator[](usize pos) const noexcept;

    /**
     * @brief Set all bits to 1.
     * 
     * @return pointer to current object.
     */
    constexpr bitset& set(void) noexcept;

    /**
     * @brief Set specific bit to 1.
     * 
     * @return pointer to current object.
     */
    constexpr bitset& set(usize pos, bool value = true) noexcept;
    
    /**
     * @brief Set all bits to 0.
     * 
     * @return pointer to current object.
     */
    constexpr bitset& reset(void) noexcept;
    
    /**
     * @brief Set specific bit to 0.
     * 
     * @return pointer to current object.
     */
    constexpr bitset& reset(usize pos) noexcept;

    /**
     * @brief Flip all bits to 0.
     * 
     * @return pointer to current object.
     */
    constexpr bitset& flip(void) noexcept;
    
    /**
     * @brief Flip specific bit to 0.
     * 
     * @return pointer to current object.
     */
    constexpr bitset& flip(usize pos) noexcept;
};

template <usize N>
bitset<N>::bitset(void) noexcept
{
    lib::bzero(m_data, sizeof(m_data));
}

template <usize N>
constexpr bool bitset<N>::get_bit(usize pos) const noexcept
{
    return m_data[pos/32] & (1 << (pos % 32));
}

template <usize N>
constexpr void bitset<N>::set_bit(usize pos, bool value) noexcept
{
    m_data[pos/32] |= (value << (pos % 32));
}

template <usize N>
constexpr void bitset<N>::flip_bit(usize pos) noexcept
{
    m_data[pos/32] &= ~(1 << (pos % 32));
}

template <usize N>
constexpr usize bitset<N>::size(void) const noexcept
{
    return N;
}

template <usize N>
constexpr usize bitset<N>::count(void) const noexcept
{
    usize count = 0;

    for (const auto& word : m_data)
        count += get_set_bits(word);

    return count;
}

template <usize N>
constexpr bool bitset<N>::test(usize pos) const noexcept
{
    // TODO: create error function that print colored text
    if (pos >= N)
        lib::panic("\n[ ERR ] %s\n", "given position out of range");
    
    return get_bit(pos);
}

template <usize N>
constexpr bitset<N>& bitset<N>::set(void) noexcept
{
    for (usize i = 0; i < N; i++)
        set_bit(i);

    return *this;
}

template <usize N>
constexpr bitset<N>& bitset<N>::set(usize pos, bool value) noexcept
{
    set_bit(pos, value);
    return *this;
}

template <usize N>
constexpr bitset<N>& bitset<N>::reset(void) noexcept
{
    for (usize i = 0; i < N; i++)
        set_bit(i);

    return *this;
}

template <usize N>
constexpr bitset<N>& bitset<N>::reset(usize pos) noexcept
{
    set_bit(pos, false);
    return *this;
}

template <usize N>
constexpr bitset<N>& bitset<N>::flip(void) noexcept
{
    for (usize i = 0; i < N; i++)
        flip_bit(i);

    return *this;
}

template <usize N>
constexpr bitset<N>& bitset<N>::flip(usize pos) noexcept
{
    flip_bit(pos);
    return *this;
}

// Operators overloading -------------------------------------------

template <usize N>
constexpr bool bitset<N>::operator[](usize pos) const noexcept
{
    return get_bit(pos);
}

} // namespace lib
} // namespace kernel

#endif // _NOS_KERNEL_BITSET_HPP_