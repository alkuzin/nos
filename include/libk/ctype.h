/*
MIT License

Copyright (c) 2024 Alexander (@alkuzin)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef _LIBK_CTYPE_H_
#define _LIBK_CTYPE_H_

/* checks for an alphabetic character */
#define isalpha(c) (((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z')))

/* checks for a digit */
#define isdigit(c) ((c >= '0') && (c <= '9'))

/* checks for an alphanumeric character */
#define isalnum(c) (isalpha(c) || isdigit(c))

/* checks for an ASCII character */
#define isascii(c) ((c >= 0) && (c <= 255))

/* checks for a printable character (including space) */
#define isprint(c) ((c == ' ') || ((c > 32) && (c < 127)))

/* converts to uppercase character */
#define toupper(c) (islower(c) ? (c - ('a' - 'A')) : c)

/* converts to lowercase character */
#define tolower(c) (isupper(c) ? (c + ('a' - 'A')) : c)

/* checks for an uppercase character */
#define isupper(c) ((c >= 'A') && (c <= 'Z'))

/* checks for a lowercase character */
#define islower(c) ((c >= 'a') && (c <= 'z')) 

#endif /* _LIBK_CTYPE_H_ */
