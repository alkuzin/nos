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

#include "../../../include/nos/types.h"

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

/** @brief Run all custom atan() tests. */
void test_atan(void);

/** @brief Run all custom sin() tests. */
void test_sin(void);

/** @brief Run all custom cos() tests. */
void test_cos(void);

/** @brief Run all custom cosh() tests. */
void test_cosh(void);

/** @brief Run all custom sinh() tests. */
void test_sinh(void);

/** @brief Run all custom tanh() tests. */
void test_tanh(void);


/**
 * @brief Test custom atan2() with glibc atan2().
 * 
 * @param [in] x - given value.
 * @param [in] y - given value.
 */
void test_atan2_s(f64 y, f64 x);

/**
 * @brief Function for testing math functions with 1 argument.
 * 
 * @param [in] test_func - given test function pointer.
 * @param [in] orig_func - given original function pointer.
 * @param [in] test_f - given test function name.
 * @param [in] orig_f - given original function name.
 * @param [in] x  - given value.
 */
void test_f(f64 (*test_func)(f64), f64 (*orig_func)(f64), const char *test_f, const char *orig_f, f64 x);

#endif /* _LIBC_MATH_TEST_H_ */