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

#ifndef _LIBK_STRING_H_
#define _LIBK_STRING_H_

#include <libk/stddef.h>

/* Get string length */
int strlen(const char *str);

/* the strcmp() compares the two strings s1 and s2. */
int strncmp(const char *s1, const char *s2, size_t n);

/* Copy a string with truncation. */
size_t strlcpy(char *dest, const char *src, size_t size);

/* Catenate a string with truncation. */
size_t strlcat(char *dest, const char *src, size_t size);

/* the strchr() returns a pointer to the 
 * first occurrence of the character c in the string s. */
char *strchr(const char *s, int c);

/* the strrchr() returns a pointer to the 
 * last occurrence of the character c in the string s. */
char *strrchr(const char *s, int c);

/* the strnstr() function locates the first	occurrence 
 * of the  null-termi-nated string little in the 
 * string big, where not more than len characters are searched. */
char *strnstr(const char *big, const char *little, size_t len);

#endif /* _LIBK_STRING_H_ */
