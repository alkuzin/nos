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

#ifndef _LIBC_MATH_TEST_H_
#define _LIBC_MATH_TEST_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TEST_MATH_PRECISION 5
#define TEST_MATH_EPSILON   1e-5


/** @brief Display total, successfull & failed number of tests. */
void test_display_result(void);

/** @brief Run all custom acos() tests. */
void test_acos(void);

/** @brief Run all custom atan2() tests. */
void test_atan2(void);

/** @brief Run all custom asin() tests. */
void test_asin(void);

/**
 * @brief Test custom acos() with glibc acos().
 * 
 * @param [in] x - given value.
 */
void test_acos_s(double x);

/**
 * @brief Test custom atan2() with glibc atan2().
 * 
 * @param [in] x - given value.
 * @param [in] y - given value.
 */
void test_atan2_s(double y, double x);

/**
 * @brief Test custom asin() with glibc asin().
 * 
 * @param [in] x - given value.
 */
void test_asin_s(double x);

#endif /* _LIBC_MATH_TEST_H_ */