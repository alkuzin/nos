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
 * @file  ctype.h
 * @brief Declares basic character handling functions.
 * 
 * @details 
 * This file contains declarations for several macros that are useful for 
 * testing and mapping characters.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   15.05.2024 
 */

#ifndef _LIBC_CTYPE_H_
#define _LIBC_CTYPE_H_

/**
 * @brief Checks for an alphabetic character.
 * 
 * @param [in] c - given character.
 * @return whether c is an alphabetic character or not.
 */
#define isalpha(c) (((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z')))

/**
 * @brief Checks for a digit.
 * 
 * @param [in] c - given character.
 * @return whether c is a digit or not.
 */
#define isdigit(c) ((c >= '0') && (c <= '9'))

/**
 * @brief Checks for an alphanumeric character.
 * 
 * @param [in] c - given character.
 * @return whether c is an alphanumeric character or not.
 */
#define isalnum(c) (isalpha(c) || isdigit(c))

/**
 * @brief Checks for an ASCII character.
 * 
 * @param [in] c - given character.
 * @return whether c is an ASCII character or not.
 */
#define isascii(c) ((c >= 0) && (c <= 255))

/**
 * @brief Checks for a printable character (including space).
 * 
 * @param [in] c - given character.
 * @return whether c is a printable character (including space) or not.
 */
#define isprint(c) ((c == ' ') || ((c > 32) && (c < 127)))

/**
 * @brief Converts to an uppercase character.
 * 
 * @param [in] c - given character.
 * @return uppercase c character.
 */
#define toupper(c) (islower(c) ? (c - ('a' - 'A')) : c)

/**
 * @brief Converts to a lowercase character.
 * 
 * @param [in] c - given character.
 * @return lowercase c character.
 */
#define tolower(c) (isupper(c) ? (c + ('a' - 'A')) : c)

/**
 * @brief Checks for an uppercase character.
 * 
 * @param [in] c - given character.
 * @return whether c is an uppercase character or not.
 */
#define isupper(c) ((c >= 'A') && (c <= 'Z'))

/**
 * @brief Checks for a lowercase character.
 * 
 * @param [in] c - given character.
 * @return whether c is a lowercase character or not.
 */
#define islower(c) ((c >= 'a') && (c <= 'z')) 


#endif /* _LIBC_CTYPE_H_ */