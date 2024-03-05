/*
MIT License

Copyright (c) 2024 Alexander (@alkuzin)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

the above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef _LIBK_MEMORY_H_
#define _LIBK_MEMORY_H_ 

#include <libk/stddef.h>

/* the memset() fills the first n bytes of the 
 * memory of the area pointed to by s 
 * with the constant byte c. */
void *memset(void *s, int c, size_t n);

/* the bzero() erases the data in the n bytes 
 * of the memory of the area pointed to by s, 
 * by writing '\0' bytes to that area. */
void bzero(void *s, size_t n);

/* the memcpy() copies n bytes from memory area src
 * to memory area dest. */
void *memcpy(void *dest, const void *src, size_t n);

/* the memccpy() copies no more than n bytes 
 * from memory area src to memory area dest, 
 * stopping when the character c is found. */
void *memccpy(void *dest, const void *src, int c, size_t n);

/* the memmove() copies n bytes 
 * from memory area src to memory area dest. */
void *memmove(void *dest, const void *src, size_t n);

/* the memchr() scans the initial n bytes
 * of the memory area pointed to by s
 * for the first instance of c. */
void *memchr(const void *s, int c, size_t n);

/* the memcmp() function compares the 
 * first n bytes (each interpreted as 
 * unsigned char) of the memory areas s1 and s2. */
int memcmp(const void *s1, const void *s2, size_t n);

#endif /* _LIBK_MEMORY_H_ */
