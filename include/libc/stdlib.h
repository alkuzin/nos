/* MIT License
 *
 * Copyright (c) 2024 Alexander (@alkuzin)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. */

/**
 * @file  stdlib.h
 * @brief Defines general functions.
 * 
 * @details This file declares functions designed to convert numbers, 
 * query memory and other tasks.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   22.06.2024
 */

#ifndef _LIBC_STDLIB_H_
#define _LIBC_STDLIB_H_

#include <stddef.h>


/** @brief The largest number rand will return.  */
#define	RAND_MAX 32767

/** @brief Threshold of size of array to sort, below which insertion sort is used. */
#define QSORT_THRESHOLD 16

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

#endif /* _LIBC_STDLIB_H_ */