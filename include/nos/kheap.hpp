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
 * @file  kheap.hpp
 * @brief Contains declarations for dynamic heap allocation management.
 * 
 * @details This header file includes definitions and functions
 * related to the managing dynamic heap allocation.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   17.05.2024 
 */

#ifndef _NOS_KERNEL_KHEAP_HPP_
#define _NOS_KERNEL_KHEAP_HPP_

#include <nos/types.hpp>
#include <nos/pmm.hpp>
#include <nos/vmm.hpp>


namespace kernel {
namespace core {
namespace memory {

#define PAGE_SIZE 4096

/** @brief Structure representing a block of memory for kernel dynamic memory allocation */
typedef struct kmalloc_block_s {
    usize size;     ///< size of memory block
    bool is_free;   ///< flag indicating if the block of memory is free
    struct kmalloc_block_s *next; ///< pointer to the next block of memory
} kmalloc_block_t;

/**
 * @brief Get the start of the kmalloc blocks linked list.
 * 
 * @return Pointer to the head of the kmalloc blocks linked list.
 */
void *kmalloc_get_head(void);

/**
 * @brief Initialize kernel dynamic memory allocation.
 * 
 * @param [in] n - given size of memory to initialize.
 */
void kmalloc_init(const usize n);

/**
 * @brief Split a memory block into two by inserting a new block.
 * 
 * @param [in] node - given pointer to the memory block to split.
 * @param [in] size - given size of the new block to insert.
 */
void kmalloc_split(kmalloc_block_t *node, const u32 size);

/**
 * @brief Find and allocate the next block of memory.
 * 
 * @param [in] size - given dize of the memory block to allocate.
 * @return Pointer to the allocated memory block.
 */
void *kmalloc_next_block(const u32 size);

/** @brief Merge free blocks of memory to partially prevent memory fragmentation. */
void kmalloc_merge_free_blocks(void);

/**
 * @brief Free allocated memory.
 * 
 * @param [in] ptr - given pointer to the memory block to free.
 */
void kmalloc_free(void *ptr);

} // namespace memory
} // namespace core
} // namespace kernel

#endif /* _NOS_KERNEL_KHEAP_HPP_ */