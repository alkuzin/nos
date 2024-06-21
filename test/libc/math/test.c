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

/**
 * @brief Compare expected and actual results of test.
 * 
 * @param [in] expected - given result. 
 * @param [in] actual - given result. 
 */
static void test_cmp(f64 expected, f64 actual);


void test_atan(void)
{
    puts("-----------------------------------------");
    test_atan_s(10);
    test_atan_s(-10);
    test_atan_s(0.00324);
    test_atan_s(-0.00324);
    test_atan_s(0.00001);
    test_atan_s(-0.00001);
    test_atan_s(-10);
    test_atan_s(1);
    test_atan_s(-1);
    test_atan_s(0);
    test_atan_s(0.3456);
    test_atan_s(-0.4567);
    test_atan_s(-0.231589);
    test_atan_s(-0.295024);
    test_atan_s(-0.312828);
    test_atan_s(-0.602383);
    test_atan_s(0.512116);
    test_atan_s(0.903607);
    test_atan_s(0.506905);
    test_atan_s(0.311673);
    test_atan_s(-0.535603);
    test_atan_s(-0.316148);
    puts("-----------------------------------------");
}

void test_acos(void)
{
    puts("-----------------------------------------");
    test_acos_s(10);
    test_acos_s(-10);
    test_acos_s(0.00324);
    test_acos_s(-0.00324);
    test_acos_s(0.00001);
    test_acos_s(-0.00001);
    test_acos_s(-10);
    test_acos_s(1);
    test_acos_s(-1);
    test_acos_s(0);
    test_acos_s(0.3456);
    test_acos_s(-0.4567);
    test_acos_s(-0.231589);
    test_acos_s(-0.295024);
    test_acos_s(-0.312828);
    test_acos_s(-0.602383);
    test_acos_s(0.512116);
    test_acos_s(0.903607);
    test_acos_s(0.506905);
    test_acos_s(0.311673);
    test_acos_s(-0.535603);
    test_acos_s(-0.316148);
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

void test_asin(void)
{
    puts("-----------------------------------------");
    test_asin_s(10);
    test_asin_s(-10);
    test_asin_s(0.00324);
    test_asin_s(-0.00324);
    test_asin_s(0.00001);
    test_asin_s(-0.00001);
    test_asin_s(-10);
    test_asin_s(1);
    test_asin_s(-1);
    test_asin_s(0);
    test_asin_s(0.3456);
    test_asin_s(-0.4567);
    test_asin_s(-0.231589);
    test_asin_s(-0.295024);
    test_asin_s(-0.312828);
    test_asin_s(-0.602383);
    test_asin_s(0.512116);
    test_asin_s(0.903607);
    test_asin_s(0.506905);
    test_asin_s(0.311673);
    test_asin_s(-0.535603);
    test_asin_s(-0.316148);
    puts("-----------------------------------------");
}


void test_acos_s(f64 x)
{
    f64 expected, actual;

    expected = nos_acos(x);
    actual   = acos(x);
    
    test_number++;
    printf(":::: TEST %d ::::\n\n", test_number);
    printf("x:        %lf\n", x);
    printf("nos_acos: %.*lf \n", TEST_MATH_PRECISION, expected);
    printf("acos:     %.*lf \n", TEST_MATH_PRECISION, actual);

    test_cmp(expected, actual);
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

void test_asin_s(f64 x)
{
    f64 expected, actual;

    expected = nos_asin(x);
    actual   = asin(x);
    
    test_number++;
    printf(":::: TEST %d ::::\n\n", test_number);
    printf("x:        %lf\n", x);
    printf("nos_asin: %.*lf \n", TEST_MATH_PRECISION, expected);
    printf("asin:     %.*lf \n", TEST_MATH_PRECISION, actual);

    test_cmp(expected, actual);
}

void test_display_result(void)
{
    printf("test: total: %d \t successfull: %d failed: %d\n", 
    successfull_tests + failed_tests, successfull_tests, failed_tests);
}

static void test_cmp(f64 expected, f64 actual)
{
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


void test_atan_s(f64 x)
{
    f64 expected, actual;

    expected = nos_atan(x);
    actual   = atan(x);
    
    test_number++;
    printf(":::: TEST %d ::::\n\n", test_number);
    printf("x:        %lf\n", x);
    printf("nos_atan: %.*lf \n", TEST_MATH_PRECISION, expected);
    printf("atan:     %.*lf \n", TEST_MATH_PRECISION, actual);

    test_cmp(expected, actual);
}