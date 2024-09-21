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

/**
 * @file  cmath.hpp
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

#ifndef _KERNEL_KSTD_CMATH_HPP_
#define _KERNEL_KSTD_CMATH_HPP_

#include <kernel/kstd/types.hpp>


namespace kernel {
namespace kstd {
    
// Math Constants ---------------------------------------------------------

/** @brief The mathematical constant Pi. */
constexpr f64 M_PI {3.14159265358979323846};

/** @brief The mathematical constant Pi divided by 2.*/
constexpr f64 M_PI_2 {1.57079632679489661923};

/** @brief The mathematical constant Pi divided by 4.*/
constexpr f64 M_PI_4 {0.78539816339744830962};

/** @brief The mathematical constant e (Euler's number).*/
constexpr f64 M_E {2.7182818284590452354};

/** @brief Represents a NaN (Not-a-Number) value.*/
const auto NAN {(0.0f / 0.0f)};

// Absolute and Maximum/Minimum Functions ----------------------------------

/**
 * @brief Calculate the absolute value of a given value.
 *
 * @param [in] x - given value.
 * @return the absolute value of the given value.
 */
template <typename T>
constexpr inline T abs(T x) noexcept
{
    return ((x) < 0 ? -(x) : (x));
}

/**
 * @brief Calculate max value between a & b
 * 
 * @param [in] a - given value.
 * @param [in] b - given value.
 * @return max value of the given values.
*/
template <typename T>
constexpr inline T max(T a, T b) noexcept
{
    return ((a) > (b) ? (a) : (b));
}

/**
 * @brief Calculate max value between a & b
 * 
 * @param [in] a - given value.
 * @param [in] b - given value.
 * @return min value of the given values.
*/
template <typename T>
constexpr inline T min(T a, T b) noexcept
{
    return ((a) < (b) ? (a) : (b));
}

// Exponential and Logarithmic Functions -------------------------------

/**
 * @brief Calculate the exponent of given value.
 * 
 * @param [in] x - given value.
 * @return the exponent of x.
 */
constexpr f64 exp(f64 x) noexcept
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

/**
 * @brief Calculate natural logarithm.
 * 
 * @param [in] x - given value.
 * @return natural logarithm of x.
 */
constexpr f64 log(f64 x) noexcept
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

/**
 * @brief Calculate the base-2 logarithm of a given value.
 * 
 * @param [in] x - given value.
 * @return base-2 logarithm of @a x.
 */
constexpr inline f64 log2(f64 x) noexcept
{
    return log(x) / log(2.0);
}

/**
 * @brief Calculate the base-10 logarithm of a given value.
 * 
 * @param [in] x - given value.
 * @return base-10 logarithm of @a x.
 */
constexpr inline f64 log10(f64 x) noexcept
{
    return log(x) / 2.3025850929940456840179914546843642076011014886287729760333279009;
}

// Power and Root Functions -----------------------------------------------

/**
 * @brief Calculate the power of a given base raised to the exponent.
 * 
 * @param [in] x - base value.
 * @param [in] y - exponent value.
 * @return the power of x raised to the y.
 */
constexpr inline f64 pow(f64 x, f64 y) noexcept
{
    if(y == 0)
        return 1;

    if(y == 1 || y == -1)
        return x;

    return exp(log(x) * y);
}

/**
 * @brief Calculates the square root of given value.
 * 
 * @param [in] x - given value.
 * @return the square root of x.
 */
constexpr f64 sqrt(f64 x) noexcept
{
    return pow(x, 0.5);
}

// Trigonometric Functions -----------------------------------------------

/**
 * @brief Calculate the principal value of the arctangent of y/x.
 * 
 * @param [in] y - given y-coordinate of the point.
 * @param [in] x - given y-coordinate of the point.
 * @return principal value of the arctangent of y/x in the range [-pi, pi].
 */
constexpr f64 atan2(f64 y, f64 x) noexcept
{
    double t0, t1, t3, t4;

    t3 = abs(x);
    t1 = abs(y);
    t0 = max(t3, t1);
    t1 = min(t3, t1);
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

    t3 = (abs(y) > abs(x)) ? static_cast<f64>(1.570796327) - t3 : t3;
    t3 = (x < 0) ?  static_cast<f64>(3.141592654) - t3 : t3;
    t3 = (y < 0) ? -t3 : t3;
    
    return t3;
}

/**
 * @brief Calculate the principal value of the arctangent of @a x.
 *
 * @param [in] x - given value.
 * @return principal value of the arctangent of @a x in the range [-pi/2, pi/2].
 */
constexpr inline f64 atan(f64 x) noexcept
{
    return atan2(x, 1.0);
}

/**
 * @brief Calculates the arc cosine of given value.
 * 
 * @param [in] x - given value.
 * @return arc cosine of @a x. 
 */
constexpr inline f64 acos(f64 x) noexcept
{
    if (x < -1.0 || x > 1.0)
        return NAN;

    return atan2(sqrt(1.0 - x * x), x);
}

/**
 * @brief Calculates the arc sine of given value.
 * 
 * @param [in] x - given value.
 * @return arc sine of @a x. 
 */
constexpr inline f64 asin(f64 x) noexcept
{
    if (x < -1.0 || x > 1.0)
        return NAN;

    return M_PI_2 - acos(x);
}

/**
 * @brief Calculates the sine of given value.
 * 
 * @param [in] x - given value.
 * @return sine of @a x. 
 */
constexpr f64 sin(f64 x) noexcept
{
    f64 cur  = x;
    f64 acc  = 1;
    f64 fact = 1;
    f64 pow  = x;
    s32 i    = 1;

    while (abs(acc) > 1e-8 && i < 100) {
        fact *= ((2*i)*(2*i+1));
        pow  *= -1 * x*x; 
        acc  =  pow / fact;
        cur  += acc;
        i++;
    }
    
    return cur;
}

/**
 * @brief Calculates the cosine of given value.
 * 
 * @param [in] x - given value.
 * @return cosine of @a x. 
 */
constexpr inline f64 cos(f64 x) noexcept
{
    return sin(x + M_PI_2);
}

/**
 * @brief Calculate the tangent of an angle.
 * 
 * @param [in] x - given angle in radians.
 * @return tangent of @a x.
 */
constexpr inline f64 tan(f64 x) noexcept
{
    return sin(x) / cos(x);
}

// Hyperbolic Functions -----------------------------------------------

/**
 * @brief Calculate the hyperbolic cosine of given value.
 * 
 * @param [in] x - given value.
 * @return hyperbolic cosine of the @a x.
 */
constexpr inline f64 cosh(f64 x) noexcept
{
    return 0.5 * (exp(x) + exp(-x));
}

/**
 * @brief Calculate the hyperbolic sine of given value.
 * 
 * @param [in] x - given value.
 * @return hyperbolic sine of the @a x.
 */
constexpr inline f64 sinh(f64 x) noexcept
{
    return 0.5 * (exp(x) - exp(-x));
}

/**
 * @brief Calculate the hyperbolic tangent of given value.
 * 
 * @param [in] x - given value.
 * @return hyperbolic tangent of the @a x.
 */
constexpr inline f64 tanh(f64 x) noexcept
{
    f64 exp2x = exp(2.0 * x);
    return (exp2x - 1.0) / (exp2x + 1.0);
}

// Rounding Functions -----------------------------------------------

/**
 * @brief Calculates the smallest integer value >= the given value.
 * 
 * @param [in] x - given value to ceil.
 * @return ceil value of @a x.
 */
constexpr inline f64 ceil(f64 x) noexcept
{
    s32 int_part = static_cast<s32>(x);
    
    if (x == int_part)
        return x;
    else if (x > 0)
        return int_part + 1;
    else
        return int_part;
}

/**
 * @brief Calculates the largest integer value <= to the given double value.
 * 
 * @param [in] x - given value to floor.
 * @return floor value of @a x.
 */
constexpr f64 floor(f64 x) noexcept
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

/**
 * @brief Perform ceiling division of two numbers.
 *
 * This macro performs ceiling division of two numbers, rounding up to the nearest integer.
 *
 * @param [in] x - the dividend.
 * @param [in] y - the divisor.
 * @return the result of ceiling division of x by y.
 */
template <typename T>
constexpr inline T ceil_div(T x, T y) noexcept
{
    return (((x + y) - 1) / y);
}

} // namespace kstd
} // namespace kernel

#endif // _KERNEL_KSTD_CMATH_HPP_