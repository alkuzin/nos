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

#include "test.h"
#include "math.h"

static s32 successfull_tests = 0;
static s32 failed_tests      = 0;
static s32 test_number       = 0;

#define TEST_VALUES_1_SIZE 22

static const f64 test_values[TEST_VALUES_1_SIZE] = {
        0, -10, 0.00324, -0.00324, 0.00001, -0.00001, 10, 1, -1, 0,
        0.3456, -0.4567,  0.231589, -0.295024, -0.312828, -0.602383,
        0.512116, 0.903607, 0.506905, 0.311673, -0.535603, -0.316148
};

/**
 * @brief Compare expected and actual results of test.
 * 
 * @param [in] expected - given result. 
 * @param [in] actual - given result. 
 */
static void test_cmp(f64 expected, f64 actual);
    


void test_f(f64 (*test_func)(f64), f64 (*orig_func)(f64), const char *test_f, const char *orig_f, f64 x)
{
    f64 expected, actual;

    expected = test_func(x);
    actual   = orig_func(x);
    
    test_number++;
    printf(":::: TEST %d ::::\n\n", test_number);
    printf("x:\t\t%lf\n", x);
    printf("%s:\t%.*lf \n", test_f, TEST_MATH_PRECISION, expected);
    printf("%s:\t\t%.*lf \n", orig_f, TEST_MATH_PRECISION, actual);

    test_cmp(expected, actual);
}

void test_display_result(void)
{
    printf("test: total: %d \t successfull: %d failed: %d\n", 
    successfull_tests + failed_tests, successfull_tests, failed_tests);
}

static void test_cmp(f64 expected, f64 actual)
{
    if (isinf(actual) && isinf(expected)) {
        puts("test result: [ SUCCESS ]\n\n");
        successfull_tests++;
        return;
    }

    if (isnan(actual) && isnan(expected)) {
        puts("test result: [ SUCCESS ]\n\n");
        successfull_tests++;
        return;
    }

    if (fabs(expected - actual) < TEST_MATH_EPSILON) {
        puts("test result: [ SUCCESS ]\n\n");
        successfull_tests++;
    }
    else {
        puts("test result: < FAIL >\n\n");
        failed_tests++;
    }
}

void test_atan(void)
{
    puts("-----------------------------------------");   
    for (usize i = 0; i < TEST_VALUES_1_SIZE; i++)
        test_f(nos_atan, atan, "nos_atan", "atan", test_values[i]);
    puts("-----------------------------------------");
}

void test_acos(void)
{
    puts("-----------------------------------------");   
    for (usize i = 0; i < TEST_VALUES_1_SIZE; i++)
        test_f(nos_acos, acos, "nos_acos", "acos", test_values[i]);
    puts("-----------------------------------------");
}

void test_asin(void)
{
    puts("-----------------------------------------");   
    for (usize i = 0; i < TEST_VALUES_1_SIZE; i++)
        test_f(nos_asin, asin, "nos_asin", "asin", test_values[i]);
    puts("-----------------------------------------");
}

void test_sin(void)
{
    puts("-----------------------------------------");   
    for (usize i = 0; i < TEST_VALUES_1_SIZE; i++)
        test_f(nos_sin, sin, "nos_sin", "sin", test_values[i]);
    puts("-----------------------------------------");
}

void test_cos(void)
{
    puts("-----------------------------------------");   
    for (usize i = 0; i < TEST_VALUES_1_SIZE; i++)
        test_f(nos_cos, cos, "nos_cos", "cos", test_values[i]);
    puts("-----------------------------------------");
}

void test_cosh(void)
{
    puts("-----------------------------------------");   
    for (usize i = 0; i < TEST_VALUES_1_SIZE; i++)
        test_f(nos_cosh, cosh, "nos_cosh", "cosh", test_values[i]);
    puts("-----------------------------------------");
}

void test_sinh(void)
{
    puts("-----------------------------------------");   
    for (usize i = 0; i < TEST_VALUES_1_SIZE; i++)
        test_f(nos_sinh, sinh, "nos_sinh", "sinh", test_values[i]);
    puts("-----------------------------------------");
}

void test_tanh(void)
{
    puts("-----------------------------------------");   
    for (usize i = 0; i < TEST_VALUES_1_SIZE; i++)
        test_f(nos_tanh, tanh, "nos_tanh", "tanh", test_values[i]);
    puts("-----------------------------------------");
}

void test_log10(void)
{
    puts("-----------------------------------------");   
    for (usize i = 0; i < TEST_VALUES_1_SIZE; i++)
        test_f(nos_log10, log10, "nos_log10", "log10", test_values[i]);
    puts("-----------------------------------------");
}

void test_log2(void)
{
    puts("-----------------------------------------");   
    for (usize i = 0; i < TEST_VALUES_1_SIZE; i++)
        test_f(nos_log2, log2, "nos_log2", "log2", test_values[i]);
    puts("-----------------------------------------");
}

void test_atan2(void)
{
    puts("-----------------------------------------");
    test_atan2_s(-0.802298, -0.546836);
    test_atan2_s(0.498692, 0.770988);
    test_atan2_s(-0.657797, 0.659074);
    test_atan2_s(-0.085372, 0.440277);
    test_atan2_s(0.117072, -0.403319);
    test_atan2_s(-0.932701, 0.744791);
    test_atan2_s(0.738540, 0.892522);
    test_atan2_s(0.740202, -0.617846);
    test_atan2_s(0.978213, -0.803744);
    test_atan2_s(-0.382977, -0.895337);
    test_atan2_s(5.557308, 4.289497);
    test_atan2_s(9.193683, 9.160631);
    test_atan2_s(5.222103, -0.444610);
    test_atan2_s(0.299943, 1.685827);
    test_atan2_s(3.539471, 9.711910);
    test_atan2_s(2.148635, 10.887811);
    test_atan2_s(0.916825, 4.679829);
    test_atan2_s(1.449886, -0.649104);
    test_atan2_s(6.701190, 7.377651);
    test_atan2_s(3.406954, 0.943081);
    puts("-----------------------------------------");
}

void test_atan2_s(f64 y, f64 x)
{
    f64 expected, actual;

    expected = nos_atan2(y, x);
    actual   = atan2(y, x);
    
    test_number++;
    printf(":::: TEST %d ::::\n\n", test_number);
    printf("y:         %lf\n", y);
    printf("x:         %lf\n", x);
    printf("nos_atan2: %.*lf \n", TEST_MATH_PRECISION, expected);
    printf("atan2:     %.*lf \n", TEST_MATH_PRECISION, actual);
    
    test_cmp(expected, actual);
}