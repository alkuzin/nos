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
 * @file  icxxabi.hpp
 * @brief C++ ABI. https://wiki.osdev.org/C%2B%2B#Global_objects
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   20.09.2024
 */

#ifndef _KERNEL_ICXXABI_HPP_
#define _KERNEL_ICXXABI_HPP_

// Maximum number of functions that can be
// registered with atexit.
constexpr int ATEXIT_MAX_FUNCS {128};

// Type definition for unsigned architecture type.
using uarch_t = unsigned;

struct atexit_func_entry_t {
	// Each member is at least 4 bytes large. Such that each entry is 12bytes.
	// 128 * 12 = 1.5KB exact.
	void (*destructor_func)(void *); // Pointer to the destructor function.
	void *obj_ptr;      // Pointer to the object associated with the destructor.
	void *dso_handle;   // Handle to the dynamic shared object.
};

/**
 * @brief Registers a function to be called at program termination.
 * 
 * @param [in] f - given pointer to the destructor function to be registered.
 * @param [in] objptr - given pointer to the object that will be passed to the destructor.
 * @param [in] dso - given handle to the dynamic shared object associated with the function.
 * @return 0 - in case of success.
 * @return non-zero - otherwise.
 */
extern "C" int __cxa_atexit(void (*f)(void *), void *objptr, void *dso);

/**
 * @brief Finalizes the specified function.
 * 
 * @param [in] f - given pointer to the destructor function to be finalized.
 */
extern "C" void __cxa_finalize(void *f);

#endif // _KERNEL_ICXXABI_HPP_