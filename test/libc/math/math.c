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

#include "math.h"
#include "test.h"


f64 nos_atan2(f64 y, f64 x)
{
    double t0, t1, t3, t4;

    t3 = fabs(x);
    t1 = fabs(y);
    t0 = fmax(t3, t1);
    t1 = fmin(t3, t1);
    t3 = (f64)1 / t0;
    t3 = t1 * t3;

    t4 = t3 * t3;
    t0 =         - (f64)0.013480470;
    t0 = t0 * t4 + (f64)0.057477314;
    t0 = t0 * t4 - (f64)0.121239071;
    t0 = t0 * t4 + (f64)0.195635925;
    t0 = t0 * t4 - (f64)0.332994597;
    t0 = t0 * t4 + (f64)0.999995630;
    t3 = t0 * t3;

    t3 = (fabs(y) > fabs(x)) ? (f64)1.570796327 - t3 : t3;
    t3 = (x < 0) ?  (f64)3.141592654 - t3 : t3;
    t3 = (y < 0) ? -t3 : t3;
    
    return t3;
}

f64 nos_acos(f64 x)
{
    if (x < -1.0 || x > 1.0)
        return NAN;

    return nos_atan2(sqrt(1.0 - x * x), x);
}

f64 nos_asin(f64 x)
{
    if (x < -1.0 || x > 1.0)
        return NAN;

    return M_PI_2 - nos_acos(x);
}

// f64 nos_atan(f64 x)
// {

// }