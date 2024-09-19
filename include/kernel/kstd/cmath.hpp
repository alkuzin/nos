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
    
/** @brief The mathematical constant Pi. */
constexpr f64 M_PI {3.14159265358979323846};

/** @brief The mathematical constant Pi divided by 2.*/
constexpr f64 M_PI_2 {1.57079632679489661923};

/** @brief The mathematical constant Pi divided by 4.*/
constexpr f64 M_PI_4 {0.78539816339744830962};

/** @brief The mathematical constant e (Euler's number).*/
constexpr f64 M_E {2.7182818284590452354};

/** @brief Represents a NaN (Not-a-Number) value.*/
constexpr auto NAN {(0.0f / 0.0f)};

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

/**
 * @brief Calculates the arc sine of given value.
 * 
 * @param [in] x - given value.
 * @return arc sine of @a x. 
 */
f64 asin(f64 x);

/**
 * @brief Calculate the principal value of the arctangent of @a x.
 *
 * @param [in] x - given value.
 * @return principal value of the arctangent of @a x in the range [-pi/2, pi/2].
 */
f64 atan(f64 x);

/**
 * @brief Calculate the principal value of the arctangent of y/x.
 * 
 * @param [in] y - given y-coordinate of the point.
 * @param [in] x - given y-coordinate of the point.
 * @return principal value of the arctangent of y/x in the range [-pi, pi].
 */
f64 atan2(f64 y, f64 x);

/**
 * @brief Calculates the cosine of given value.
 * 
 * @param [in] x - given value.
 * @return cosine of @a x. 
 */
f64 cos(f64 x);

/**
 * @brief Calculates the sine of given value.
 * 
 * @param [in] x - given value.
 * @return sine of @a x. 
 */
f64 sin(f64 x);

/**
 * @brief Calculate the tangent of an angle.
 * 
 * @param [in] x - given angle in radians.
 * @return tangent of @a x.
 */
f64 tan(f64 x);

/**
 * @brief Calculate the hyperbolic cosine of given value.
 * 
 * @param [in] x - given value.
 * @return hyperbolic cosine of the @a x.
 */
f64 cosh(f64 x);

/**
 * @brief Calculate the hyperbolic sine of given value.
 * 
 * @param [in] x - given value.
 * @return hyperbolic sine of the @a x.
 */
f64 sinh(f64 x);

/**
 * @brief Calculate the hyperbolic tangent of given value.
 * 
 * @param [in] x - given value.
 * @return hyperbolic tangent of the @a x.
 */
f64 tanh(f64 x);

/**
 * @brief Calculate the base-10 logarithm of a given value.
 * 
 * @param [in] x - given value.
 * @return base-10 logarithm of @a x.
 */
f64 log10(f64 x);

/**
 * @brief Calculate the base-2 logarithm of a given value.
 * 
 * @param [in] x - given value.
 * @return base-2 logarithm of @a x.
 */
f64 log2(f64 x);

/**
 * @brief Calculates the smallest integer value >= the given value.
 * 
 * @param [in] x - given value to ceil.
 * @return ceil value of @a x.
 */
f64 ceil(f64 x);

/**
 * @brief Calculates the largest integer value <= to the given double value.
 * 
 * @param [in] x - given value to floor.
 * @return floor value of @a x.
 */
f64 floor(f64 x);

} // namespace kstd
} // namespace kernel

#endif // _KERNEL_KSTD_CMATH_HPP_