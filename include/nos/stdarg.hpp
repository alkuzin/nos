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
 * @file  stdarg.hpp
 * @brief Defines several macros for stepping through a list of arguments.
 * 
 * @details 
 * This file contains declarations for several macros that are useful for 
 * managing functions with variable number of arguments.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   15.05.2024 
 */

#ifndef _NOS_KERNEL_STDARG_HPP_
#define _NOS_KERNEL_STDARG_HPP_

namespace kernel {
namespace lib {

/**
 * @brief This macro initializes ap for subsequent use by
 * va_arg() and va_end(), and must be called first.
 * 
 * The argument last is the name of the last argument before  the
 * variable argument list, that is, the last argument of which
 * the calling function knows the type.
 *
 * Because the address of this argument may be used in the
 * va_start() macro, it should not be declared as a register
 * variable, or as a function or an array type.
 * 
 * @param [in] v - arguments list.
 * @param [in] l - number of arguments.
 */
#define va_start(v,l) __builtin_va_start(v,l)

/**
 * @brief This macro expands to an expression that has the type
 * and value of the next argument in the call.
 * 
 * The argument ap is the va_list ap initialized by va_start(). 
 * Each call to va_arg() modifies ap  so that the next call 
 * returns the next argument. The argument type is a type name 
 * specified so that the type of a pointer to an object that has 
 * the specified type can be obtained simply by adding a * to type.
 *
 * The first use of the va_arg() macro after that of the
 * va_start() macro returns the argument after last. Successive
 * invocations return the values of the remaining arguments.
 *
 * If there is no next argument, or if type is not compatible
 * with the type of the actual next argument (as promoted accord‐
 * ing to the default argument promotions), random errors will
 * occur.
 *
 * If ap is passed to a function that uses va_arg(ap,type), then
 * the value of ap is undefined after the return of that function.
 * 
 * @param [in] v - arguments list.
 * @param [in] l - number of arguments.
 */
#define va_arg(v,l)   __builtin_va_arg(v,l)

/**
 * @brief This macro copies the (previously initialized) variable argument
 * list src to dest.  
 * 
 * The behavior is as if va_start() were applied to dest with the same
 * last argument, followed by the same number of va_arg() invocations 
 * that was used to reach the current state of src. 
 * 
 * @param [in] v - arguments list.
 * @param [in] l - number of arguments.
 */
#define va_copy(d,s)  __builtin_va_copy(d,s)

/**
 * @brief Each invocation of va_start() must be matched by a corresponding 
 * invocation of va_end() in the same function. 
 * 
 * After the call va_end(ap) the variable ap is undefined.
 * Multiple traversals of the list, each bracketed by va_start()
 * and va_end() are possible. va_end() may be a macro or a function.
 * 
 * @param [in] v - arguments list.
 * @param [in] l - number of arguments.
 */
#define va_end(v)     __builtin_va_end(v)

using va_list = __builtin_va_list;
    
} // namespace lib
} // namespace kernel

#endif /* _NOS_KERNEL_STDARG_HPP_ */