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

/**
 * @file  kheap.h
 * @brief Contains declarations for dynamic heap allocation management.
 * 
 * @details This header file includes definitions and functions
 * related to the managing dynamic heap allocation.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   17.05.2024 
 */

#ifndef _NOS_KERNEL_KHEAP_H_
#define _NOS_KERNEL_KHEAP_H_

#include <nos/types.h>
#include <nos/pmm.h>
#include <nos/vmm.h>

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

#endif /* _NOS_KERNEL_KHEAP_H_ */