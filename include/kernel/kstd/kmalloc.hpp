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
 * @file  kmalloc.hpp
 * @brief Contains declarations for dynamic heap allocation management.
 * 
 * @details This header file includes definitions and functions
 * related to the managing dynamic heap allocation.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   21.09.2024 
 */

#ifndef _KERNEL_KSTD_KMALLOC_HPP_
#define _KERNEL_KSTD_KMALLOC_HPP_

#include <kernel/kheap.hpp>


namespace kernel {
namespace kstd {

/**
 * @brief Allocates n bytes and returns a pointer
 * to the allocated memory.
 * 
 * @param [in] n - given number of bytes to allocate.
 * @return pointer to allocated memory in case of success.
 * @return null pointer otherwise.
 */
inline void *kmalloc(usize n) noexcept
{
    static void *ptr;

    if(!core::memory::kmalloc::get_head())
        core::memory::kmalloc::init(n);

    ptr = core::memory::kmalloc::next_block(n);
    core::memory::kmalloc::merge_free_blocks();

    return ptr;
}

/**
 * @brief Frees the memory space pointed to by ptr, 
 * which must have been returned by a previous call to kmalloc()
 * or related functions. Otherwise, or if ptr has already 
 * been freed, undefined behavior occurs. 
 * If ptr is null pointer, no operation is performed.
 * 
 * @param [in] ptr - given pointer to allocated memory.
 */
inline void kfree(void *ptr) noexcept
{
    if(!ptr)
        return;

    core::memory::kmalloc::free(ptr);
}
    
} // namespace kstd
} // namespace kernel

#endif // _KERNEL_KSTD_KMALLOC_HPP_