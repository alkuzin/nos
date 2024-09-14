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
 * @brief Defines several strings and memory management functions.
 *
 * @details This header file provides functions for manipulating strings,
 * such as copying, concatenating and comparing.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   15.05.2024 
 */

#ifndef _NOS_KERNEL_STRING_HPP_
#define _NOS_KERNEL_STRING_HPP_

#include <nos/types.hpp>


namespace kernel {
namespace str {
    
/**
 * @brief Get string length.
 * 
 * @param [in] str - given null terminated string.
 * @return str length.
 */
s32   strlen(const char *str);

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
s32   strncmp(const char *s1, const char *s2, usize n);

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
 * @brief Breaks a string into a sequence of zero or more nonempty tokens.
 * 
 * On the first call to strtok(), the string to be parsed should be specified in str.
 * In each subsequent call that should parse the same string, str must be nullptr.
 * 
 * @param [in] str - given string to parse. 
 * @param [in] delim - given set of bytes that delimit the tokens in the parsed string.
 * @return pointer to the next token.
 * @return nullptr if there are no more tokens.
 */
char *strtok(char *str, const char *delim);

/**
 * @brief Search a string for any of a set of bytes.
 * 
 * @param [in] str - given string.
 * @param [in] accept - given string to find.
 * @return pointer to the byte in s that matches one of the bytes in accept.
 * @return nullptr if no such byte is found.
 */
char *strpbrk(const char *str, const char *accept);

/**
 * @brief Returns a pointer to the first occurrence of the character @a c in the string @a s.
 * 
 * @param [in] s - given source string.
 * @param [in] c - given character to find.
 * @return pointer to the first occurrence of @a c in @a s - in case of success.
 * @return nullptr - otherwise.
 */
char *strchr(const char *s, s32 c);

/**
 * @brief Returns a pointer to the last occurrence of the character @a c in the string @a s.
 * 
 * @param [in] s - given source string.
 * @param [in] c - given character to find.
 * @return pointer to the last occurrence of @a c in @a s - in case of success.
 * @return nullptr - otherwise.
 */
char *strrchr(const char *s, s32 c);

/**
 * @brief Locates the first occurrence of the null-terminated string @a little
 * in the string @a big, where not more than @a len characters are searched.
 * 
 * @param [in] big - given string to find.
 * @param [in] little - given source string.
 * @param [in] len - given number of characters of @a little to search.
 * @return pointer to the first occurrence of the string @a little in string @a big.
 */
char *strnstr(const char *big, const char *little, usize len);

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
 * @brief Copies @a n bytes from memory area @a src to memory area @a dest.
 * 
 * @param [out] dest - given destination buffer.
 * @param [in] src - given source buffer.
 * @param [in] n - given number of bytes to copy.
 * @return destination buffer pointer.
 */
void *memmove(void *dest, const void *src, usize n);

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
s32   memcmp(const void *s1, const void *s2, usize n);

/**
 * @brief Fills the first n bytes of the memory of the area pointed to by s 
 * with the constant byte c.
 * 
 * @param [out] s - given buffer pointer.
 * @param [in] c - given byte for filling buffer.
 * @param [in] n - given number of buffer bytes to fill.
 * @return filled buffer pointer.
 */
void  *memset(void *s, s32 c, usize n);

/**
 * @brief Scans the initial @a n bytes of the memory area 
 * pointed to by @a s for the first instance of @a c.
 * 
 * @param [in] s - given pointer to the memory block to be searched.
 * @param [in] c - given character to be located.
 * @param [in] n - given number of bytes to be searched.
 * @return pointer to the located character in case of success.
 * @return nullptr - otherwise.
 */
void *memchr(const void *s, s32 c, usize n);

/**
 * @brief Retrieve a string describing the error code.
 * 
 * @param [in] errnum - given error code. 
 * @return pointer to a string describing the error code.
 */
const char *strerror(s32 errnum);

} // namespace str
} // namespace kernel

#endif /* _NOS_KERNEL_STRING_HPP_ */