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
 * @file  string.h
 * @brief Defines several strings and memory management functions.
 *
 * @details This header file provides functions for manipulating strings,
 * such as copying, concatenating and comparing.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   15.05.2024 
 */

#ifndef _LIBC_STRING_H_
#define _LIBC_STRING_H_

#include <stddef.h>

/**
 * @brief Get string length.
 * 
 * @param [in] str - given null terminated string.
 * @return str length.
 */
i32   strlen(const char *str);

/**
 * @brief Compares the two strings s1 and s2.
 * 
 * @param [in] s1 - first given null terminated string.
 * @param [in] s2 - second given null terminated string.
 * @param [in] n - given number of symbols for comparison.
 * @return 0, if s1 and s2 are equal;
 * @return a negative value if s1 is less than s2;
 * @return a positive value if s1 is greater than s2.
 */
i32   strncmp(const char *s1, const char *s2, usize n);

/**
 * @brief Copy a string with truncation.
 * 
 * @param [out] dest - given buffer for copied string.
 * @param [in] src - given source null terminated string.
 * @param [in] size - given size to copy.
 * @return number of copied string characters.
 */
usize strncpy(char *dest, const char *src, usize size);

/**
 * @brief Catenate a string with truncation.
 * 
 * @param [out] dest - given buffer for concatenated string.
 * @param [in] src - given source null terminated string.
 * @param [in] size - given size to concatenate.
 * @return length of new concatenated string.
 */
usize strncat(char *dest, const char *src, usize size);

/**
 * @brief Fills the first n bytes of the memory of the area pointed to by s 
 * with the constant byte c.
 * 
 * @param [out] s - given buffer pointer.
 * @param [in] c - given byte for filling buffer.
 * @param [in] n - given number of buffer bytes to fill.
 * @return filled buffer pointer.
 */
void  *memset(void *s, i32 c, usize n);

/**
 * @brief Erases the data in the n bytes 
 * of the memory of the area pointed to by s, 
 * by writing '\0' bytes to that area.
 * 
 * @param [out] s - given buffer pointer.
 * @param [in] n - given number of buffer bytes to erase.
 */
void  bzero(void *s, usize n);

/**
 * @brief Copies n bytes from memory area src to memory area dest.
 * 
 * @param [out] dest - given destination buffer.
 * @param [in] src - given source buffer.
 * @param [in] n - given number of bytes to copy.
 * @return destination buffer pointer.
 */
void  *memcpy(void *dest, const void *src, usize n);

/**
 * @brief Compares the first n bytes (each interpreted as unsigned char) 
 * of the memory areas s1 and s2.
 * 
 * @param [in] s1 - first given memory area pointer.
 * @param [in] s2 - second given memory area pointer.
 * @param [in] n - given number of bytes to compare.
 * @return 0, if s1 and s2 are equal;
 * @return a negative value if s1 is less than s2;
 * @return a positive value if s1 is greater than s2.
 */
i32   memcmp(const void *s1, const void *s2, usize n);

#endif /* _LIBC_STRING_H_ */