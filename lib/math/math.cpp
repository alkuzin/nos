/**
 * The Null Operating System (NOS).
 * Copyright (C) 2024  Alexander (@alkuzin).
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <nos/math.hpp>

namespace kernel {
namespace math {

// Trigonometric Functions -----------------------------------------------

f64 acos(f64 x)
{
    if (x < -1.0 || x > 1.0)
        return NAN;

    return atan2(sqrt(1.0 - x * x), x);
}

f64 asin(f64 x)
{
    if (x < -1.0 || x > 1.0)
        return NAN;

    return M_PI_2 - acos(x);
}

f64 atan(f64 x)
{
    return atan2(x, 1.0);
}

f64 atan2(f64 y, f64 x)
{
    double t0, t1, t3, t4;

    t3 = fabs(x);
    t1 = fabs(y);
    t0 = fmax(t3, t1);
    t1 = fmin(t3, t1);
    t3 = static_cast<f64>(1.0) / t0;
    t3 = t1 * t3;

    t4 = t3 * t3;
    t0 =         - static_cast<f64>(0.013480470);
    t0 = t0 * t4 + static_cast<f64>(0.057477314);
    t0 = t0 * t4 - static_cast<f64>(0.121239071);
    t0 = t0 * t4 + static_cast<f64>(0.195635925);
    t0 = t0 * t4 - static_cast<f64>(0.332994597);
    t0 = t0 * t4 + static_cast<f64>(0.999995630);
    t3 = t0 * t3;

    t3 = (fabs(y) > fabs(x)) ? static_cast<f64>(1.570796327) - t3 : t3;
    t3 = (x < 0) ?  static_cast<f64>(3.141592654) - t3 : t3;
    t3 = (y < 0) ? -t3 : t3;
    
    return t3;
}

f64 cos(f64 x)
{
    return sin(x + M_PI_2);
}

f64 sin(f64 x)
{
    f64 cur  = x;
    f64 acc  = 1;
    f64 fact = 1;
    f64 pow  = x;
    s32 i    = 1;

    while (fabs(acc) > 1e-8 && i < 100) {
        fact *= ((2*i)*(2*i+1));
        pow  *= -1 * x*x; 
        acc  =  pow / fact;
        cur  += acc;
        i++;
    }
    
    return cur;
}

f64 tan(f64 x)
{
    return sin(x) / cos(x);
}

// Hyperbolic Functions -----------------------------------------------

f64 cosh(f64 x)
{
    return 0.5 * (exp(x) + exp(-x));
}

f64 sinh(f64 x)
{
    return 0.5 * (exp(x) - exp(-x));
}

f64 tanh(f64 x)
{
    f64 exp2x = exp(2.0 * x);
    return (exp2x - 1.0) / (exp2x + 1.0);
}

// Exponential and Logarithmic Functions -------------------------------

f64 exp(f64 x)
{
    if(x == 0.0)
        return 1.0;

    if(x == 1.0)
        return M_E;

    if(x <= -15.0)
        return 0.0;

    s32 accuracy = 1000;
    f64 exp_sum  = 1.0;
    s32 i        = accuracy - 1.0;
    
	while (i > 0.0) {
        exp_sum = 1.0 + x * exp_sum / i;
        i--;
    }

    return exp_sum;
}

f64 log(f64 x)
{
    if(x <= 0)
        return NAN;

    if(x == 1)
        return 0;

    if(x == M_E)
        return 1;

    s32 i      = 1;
    f64 result = 0;
    f64 term   = (x - 1) / (x + 1);
    f64 square = term * term;

    while(i <= 60000) {
        result += term / i;
        term   *= square;
        i++;
        i++;
    }

    return (2.0 * result);
}

f64 log2(f64 x)
{
    return log(x) / log(2.0);
}

f64 log10(f64 x)
{
    return log(x) / 2.3025850929940456840179914546843642076011014886287729760333279009;
}

// Power and Root Functions -----------------------------------------------

f64 pow(f64 x, f64 y)
{
    if(y == 0)
        return 1;

    if(y == 1 || y == -1)
        return x;

    return exp(log(x) * y);
}

f64 sqrt(f64 x)
{
    return pow(x, 0.5);
}

// Absolute and Maximum/Minimum Functions ----------------------------------

f64 fabs(f64 x)
{
    return (x < 0) ? -x : x;
}

f64 fmax(f64 x, f64 y)
{
    return (x > y) ? x : y;
}

f64 fmin(f64 x, f64 y)
{
    return (x < y) ? x : y;
}

// Rounding Functions -----------------------------------------------

f64 ceil(f64 x)
{
    s32 int_part;

    int_part = static_cast<s32>(x);
    
    if (x == int_part)
        return x;
    else if (x > 0)
        return int_part + 1;
    else
        return int_part;
}

f64 floor(f64 x)
{
    s32 int_part; 
    
    int_part = static_cast<int>(x);
    
    if (x == int_part)
        return x;
    else if (x > 0)
        return int_part;
    else
        return int_part - 1;
}

} // namespace math
} // namespace kernel