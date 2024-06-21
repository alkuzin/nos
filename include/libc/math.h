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
 * @file  math.h
 * @brief Standard mathematical functions and constants.
 *
 * @details 
 * This file contains declarations for standard mathematical functions and constants.
 * It includes functions for common mathematical operations such as logarithmic functions,
 * exponential functions, and more. 
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   15.05.2024 
 */

#ifndef _LIBC_MATH_H_
#define _LIBC_MATH_H_

#include <stdint.h>

/** @brief The mathematical constant Pi. */
#define M_PI 3.14159265358979323846

/** @brief The mathematical constant Pi divided by 2.*/
#define M_PI_2 1.57079632679489661923

/** @brief The mathematical constant Pi divided by 4.*/
#define M_PI_4 0.78539816339744830962

/**
 * @brief The mathematical constant e (Euler's number).
 *
 * This constant defines the value of the mathematical constant e (approximately 2.718).
 */
#define M_E  2.7182818284590452354

/**
 * @brief Represents a NaN (Not-a-Number) value.
 *
 * This constant represents a NaN value, which is the result of dividing 0.0 by 0.0.
 */
#define NAN (0.0f / 0.0f)

/**
 * @brief Calculate the absolute value of a given value.
 *
 * This macro calculates the absolute value of the given value.
 *
 * @param [in] x - given value.
 * @return the absolute value of the given value.
 */
#define abs(x) ((x) < 0 ? -(x) : (x))

/**
 * @brief Calculate max value between a & b
 * 
 * @param [in] a - given value.
 * @param [in] b - given value.
 * @return max value of the given values.
*/
#define max(a, b) ((a) > (b) ? (a) : (b))

/**
 * @brief Perform ceiling division of two numbers.
 *
 * This macro performs ceiling division of two numbers, rounding up to the nearest integer.
 *
 * @param [in] x - the dividend.
 * @param [in] y - the divisor.
 * @return the result of ceiling division of x by y.
 */
#define ceil_div(x, y) (((x + y) - 1) / y)

/**
 * @brief Calculate natural logarithm.
 * 
 * @param [in] x - given value.
 * @return natural logarithm of x.
 */
f64 log(f64 x);

/**
 * @brief Calculate the power of a given base raised to the exponent.
 * 
 * @param [in] x - base value.
 * @param [in] y - exponent value.
 * @return the power of x raised to the y.
 */
f64 pow(f64 x, f64 y);

/**
 * @brief Calculate the exponent of given value.
 * 
 * @param [in] x - given value.
 * @return the exponent of x.
 */
f64 exp(f64 x);

/**
 * @brief Calculates the square root of given value.
 * 
 * @param [in] x - given value.
 * @return the square root of x.
 */
f64 sqrt(f64 x);

/**
 * @brief Calculate the absolute value of a floating point number.
 *
 * @param [in] x - given floating point number.
 * @return the absolute value of @a x.
 */
f64 fabs(f64 x);

/**
 * @brief Calculate the max value of given floating point numbers.
 * 
 * @param [in] x - first given floating point number to compare.
 * @param [in] y - second given floating point number to compare.
 * @return max value of the given values.
 */
f64 fmax(f64 x, f64 y);

/**
 * @brief Calculate the min value of given floating point numbers.
 * 
 * @param [in] x - first given floating point number to compare.
 * @param [in] y - second given floating point number to compare.
 * @return min value of the given values.
 */
f64 fmin(f64 x, f64 y);

/**
 * @brief Calculates the arc cosine of given value.
 * 
 * @param [in] x - given value.
 * @return arc cosine of @a x. 
 */
f64 acos(f64 x);
f64 asin(f64 x);
f64 atan(f64 x);

/**
 * @brief Compute the principal value of the arctangent of y/x.
 * 
 * @param [in] y - given y-coordinate of the point.
 * @param [in] x - given y-coordinate of the point.
 * @return principal value of the arctangent of y/x in the range [-pi, pi].
 */
f64 atan2(f64 y, f64 x);

#endif /* _LIBC_MATH_H_ */