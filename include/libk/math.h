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

#ifndef _LIBK_MATH_H_
#define _LIBK_MATH_H_

/* math constants */
#define PI 3.141592653589793
#define E  2.718281828459045

#define _NAN (0.0f / 0.0f)

#define abs(x) ((x) < 0 ? -(x) : (x))

#include <libk/stdint.h>

/* the log() calculates natural logarithm */
double log(double x);

/* the pow() equal to 'x^y' in math */
double pow(double x, double y);

/* the exp() equal to 'e^x' in math */
double exp(double x);

/* the sqrt() calculates the square root */
double sqrt(double x);

/* the factorial() equal to 'n!' in math (up to 20! including) */
uint64_t factorial(uint32_t n);

#endif /* _LIBK_MATH_H_ */
