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

#ifndef _LIBC_STRING_H_
#define _LIBC_STRING_H_

#include <stddef.h>

/* Get string length */
i32   strlen(const char *str);

/* the strcmp() compares the two strings s1 and s2. */
i32   strncmp(const char *s1, const char *s2, usize n);

/* Copy a string with truncation. */
usize strncpy(char *dest, const char *src, usize size);

/* Catenate a string with truncation. */
usize strncat(char *dest, const char *src, usize size);

/* the memset() fills the first n bytes of the 
 * memory of the area pointed to by s 
 * with the constant byte c. */
void  *memset(void *s, i32 c, usize n);

/* the bzero() erases the data in the n bytes 
 * of the memory of the area pointed to by s, 
 * by writing '\0' bytes to that area. */
void  bzero(void *s, usize n);

/* the memcpy() copies n bytes from memory area src
 * to memory area dest. */
void  *memcpy(void *dest, const void *src, usize n);

/* the memcmp() function compares the 
 * first n bytes (each interpreted as 
 * unsigned char) of the memory areas s1 and s2. */
i32   memcmp(const void *s1, const void *s2, usize n);

#endif /* _LIBC_STRING_H_ */
