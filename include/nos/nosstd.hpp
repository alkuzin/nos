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
 * @file  nosstd.hpp
 * @brief Contains diferent system functions.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   17.05.2024 
 */

#ifndef _NOS_NOSSTD_HPP_
#define _NOS_NOSSTD_HPP_

#include <nos/types.hpp>


namespace kernel {
namespace lib {

/**
 * @brief Kernel time delay in microseconds.
 * 
 * @param [in] microsec - given number of microseconds for kernel to sleep. 
 */
void __ksleep(u32 microsec);

/**
 * @brief Kernel time delay in seconds.
 * 
 * @param [in] sec - given number of seconds for kernel to sleep. 
 */
void ksleep(u32 sec);

///< Halt kernel.
void khalt(void); 

/**
 * @brief Allocates n bytes and returns a pointer
 * to the allocated memory.
 * 
 * @param [in] n - given number of bytes to allocate.
 * @return pointer to allocated memory in case of success.
 * @return null pointer otherwise.
 */
void *kmalloc(usize n);


/**
 * @brief Frees the memory space pointed to by ptr, 
 * which must have been returned by a previous call to kmalloc()
 * or related functions. Otherwise, or if ptr has already 
 * been freed, undefined behavior occurs. 
 * If ptr is null pointer, no operation is performed.
 * 
 * @param [in] ptr - given pointer to allocated memory.
 */
void kfree(void *ptr);

} // namespace lib
} // namespace kernel

#endif /* _NOS_NOSSTD_HPP_ */