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

f64 nos_atan(f64 x)
{
    return nos_atan2(x, 1);
}

f64 nos_sin(f64 x)
{
    f64 cur, acc, fact, pow;
    s32 i;

    cur  = x;
    acc  = 1;
    fact = 1;
    pow  = x;
    i    = 1;

    while (fabs(acc) > 1e-8 && i < 100) {
        fact *= ((2*i)*(2*i+1));
        pow  *= -1 * x*x; 
        acc  =  pow / fact;
        cur  += acc;
        i++;
    }

    return cur;
}

f64 nos_cos(f64 x)
{
    return nos_sin(x + M_PI_2);
}

f64 nos_tan(f64 x)
{
    return nos_sin(x) / nos_cos(x);
}

f64 nos_cosh(f64 x)
{
    return 0.5 * (exp(x) + exp(-x));
}

f64 nos_sinh(f64 x)
{
    return 0.5 * (exp(x) - exp(-x));
}

f64 nos_tanh(f64 x)
{
  f64 exp2x;
  
  exp2x = exp(2 * x);
  return (exp2x - 1) / (exp2x + 1);
}

f64 nos_log10(f64 x)
{
    return log(x) / 2.3025850929940456840179914546843642076011014886287729760333279009;
}

f64 nos_log2(f64 x)
{
    return log(x) / log(2);
}

f64 nos_ceil(f64 x)
{
    s32 int_part;

    int_part = (s32)x;
    
    if (x == int_part)
        return x;
    else if (x > 0)
        return int_part + 1;
    else
        return int_part;
}

f64 nos_floor(f64 x)
{
    s32 int_part; 
    
    int_part = (int)x;
    
    if (x == int_part)
        return x;
    else if (x > 0)
        return int_part;
    else
        return int_part - 1;
}