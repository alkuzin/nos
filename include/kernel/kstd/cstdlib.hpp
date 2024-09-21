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
 * @file  cstdlib.hpp
 * @brief Defines general functions.
 * 
 * @details This file declares functions designed to convert numbers, 
 * query memory and other tasks.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   22.06.2024
 */

#ifndef _KERNEL_KSTD_CSTDLIB_HPP_
#define _KERNEL_KSTD_CSTDLIB_HPP_

#include <kernel/arch/x86/system.hpp>
#include <kernel/kstd/stdarg.hpp>
#include <kernel/kstd/types.hpp>


namespace kernel {
namespace kstd {

/** @brief The largest number rand will return.*/
constexpr u32 RAND_MAX {32767};

/** @brief Threshold of size of array to sort, below which insertion sort is used.*/
constexpr u32 QSORT_THRESHOLD {16};

// Convertion Functions ---------------------------------------------

/**
 * @brief Convert string to integer. 
 * 
 * @param [in] str - given string to convert. 
 * @return integer converted from string.
 */
constexpr s32 atoi(const char *str) noexcept
{
    s32 i           = 0;
    s32 res         = 0;
    s32 is_negative = 0;
    
    if(str[i] == '-') {
        is_negative = 1;
        i++;
    }
    
    while(str[i] && (str[i] >= '0' && str[i] <= '9')) {
        res *= 10;
        res += (static_cast<int>(str[i]) - '0');
        i++;
    }

    if(is_negative)
        return -res;
    
    return res;
}

/**
 * @brief Convert string to double. 
 * 
 * @param [in] str - given string to convert. 
 * @return double converted from string.
 */
constexpr f64 atof(const char *str) noexcept
{
    f64 res      = 0;
    f64 fraction = 1;
    s32 sign     = 1;
    s32 decimal  = 0;

    while (*str == ' ')
        str++;

    if (*str == '-') {
        sign = -1;
        str++;
    } 
    else if (*str == '+')
        str++;

    while (*str != '\0') {

        if (*str >= '0' && *str <= '9') {
            res = res * 10 + (*str - '0');

            if (decimal)
                fraction *= 10;
        } 
        else if (*str == '.')
            decimal = 1;
        else
            break;

        str++;
    }
    
    return (sign * res) / fraction;
}

// Pseudo-random Functions ---------------------------------------------

static u64 next = 1;

/**
 * @brief Calculates the sequence of pseudo random numbers
 * from 0 to RAND_MAX.
 * 
 * @return pseudo random number. 
 */
constexpr inline s32 rand(void) noexcept
{
    next = next * 1103515245 + 12345;
    return static_cast<u32>(next / 65536) % RAND_MAX;
}

/**
 * @brief Set seed for the sequence of pseudo random numbers.
 * 
 * @param [in] seed - given new beginning of the sequence of pseudo random numbers.
 */
constexpr inline void srand(u32 seed) noexcept
{
    next = seed;
}

//** @brief Halt kernel.*/ 
inline void khalt(void) noexcept
{
	arch::x86::cli();
	for(;;);
}

/**
 * @brief Time delay.
 * 
 * @param [in] microsec - given time to delay.
 */
static inline void __ksleep(u32 microsec) noexcept
{
	u32 i;

	for (i = 0; i < microsec * 10000; i++) {
		for (i = 0; i < microsec * 10000; i++)
			arch::x86::nop();
	}
}

/**
 * @brief Time delay.
 * 
 * @param [in] microsec - given time to delay in seconds.
 */
inline void ksleep(u32 sec) noexcept
{
	__ksleep(sec * 10000);
}

/**
 * @brief Sorts an array with @a nmemb elements of size @a size.
 * 
 * There is Radix sort inside, what makes this algorithm even faster,
 * than GNU libc qsort() (only for integers).
 * 
 * @param [in] base - given pointer to the first element of the sequence to sort.
 * @param [in] nmemb - given number of elements in the sequence.
 * @param [in] size - given size of each element in sequence in bytes.
 * @param [in] cmp - given comparison function pointer.
 */
void qsort(void *base, usize nmemb, usize size, s32 (*cmp)(const void *, const void *));

} // namespace kstd
} // namespace kernel

#endif // _KERNEL_KSTD_CSTDLIB_HPP_