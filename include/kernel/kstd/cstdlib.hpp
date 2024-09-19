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

#include <kernel/kstd/stdarg.hpp>
#include <kernel/kstd/types.hpp>
#include <kernel/gfx/gfx.hpp>


namespace kernel {
namespace kstd {

/** @brief The largest number rand will return.*/
constexpr u32 RAND_MAX {32767};

/** @brief Threshold of size of array to sort, below which insertion sort is used.*/
constexpr u32 QSORT_THRESHOLD {16};

/**
 * @brief Convert string to integer. 
 * 
 * @param [in] str - given string to convert. 
 * @return integer converted from string.
 */
s32 atoi(const char *str);

/**
 * @brief Convert string to double. 
 * 
 * @param [in] str - given string to convert. 
 * @return double converted from string.
 */
f64 atof(const char *str);

/**
 * @brief Calculates the sequence of pseudo random numbers
 * from 0 to RAND_MAX.
 * 
 * @return pseudo random number. 
 */
s32 rand(void);

/**
 * @brief Set seed for the sequence of pseudo random numbers.
 * 
 * @param [in] seed - given new beginning of the sequence of pseudo random numbers.
 */
void srand(u32 seed);

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

//** @brief Halt kernel.*/ 
void khalt(void); 

/**
 * @brief Allocates n bytes and returns a pointer
 * to the allocated memory.
 * 
 * @param [in] n - given number of bytes to allocate.
 * @return pointer to allocated memory in case of success.
 * @return null pointer otherwise.
 */
void *kmalloc(usize n);

/**
 * @brief Frees the memory space pointed to by ptr, 
 * which must have been returned by a previous call to kmalloc()
 * or related functions. Otherwise, or if ptr has already 
 * been freed, undefined behavior occurs. 
 * If ptr is null pointer, no operation is performed.
 * 
 * @param [in] ptr - given pointer to allocated memory.
 */
void kfree(void *ptr);

} // namespace kstd
} // namespace kernel

#endif // _KERNEL_KSTD_CSTDLIB_HPP_