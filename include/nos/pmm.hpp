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
 * @file  pmm.hpp
 * @brief Contains declarations for physical memory management.
 * 
 * @details This header file includes functions related to the
 * physical memory management.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   17.05.2024 
 */

#ifndef _NOS_KERNEL_PMM_HPP_
#define _NOS_KERNEL_PMM_HPP_

#include <nos/memlayout.hpp>
#include <nos/multiboot.hpp>


namespace kernel {
namespace core {
namespace memory {

#define BLOCK_SIZE     4096 /* 4KB */
#define BITS_PER_BYTE  8

/**
 * @brief Set block in the memory map.
 * 
 * @param [in] bit - given block to set.
 */
void pmm_set_block(u32 bit);

/**
 * @brief Unset block in the memory map.
 * 
 * @param [in] bit - given block to unset.
 */
void pmm_unset_block(u32 bit);

/**
 * @brief Test if a block in the memory map is set/used.
 * 
 * @param [in] bit - given block to test.
 * @return true - block is set;
 * @return false - otherwise.
 */
bool pmm_test_block(u32 bit);

/**
 * @brief Find the first free blocks in the memory map.
 * 
 * @param [in] n - given number of blocks to find.
 * @return the index of the first free block, or -1 if not found. 
 */
s32 pmm_find_first_free_blocks(u32 n);

/**
 * @brief Initialize the physical memory manager.
 * 
 * @param [in] start_addr - given starting address of the memory map.
 * @param [in] size - given size of the memory map.
 */
void pmm_init(u32 start_addr, u32 size);

/**
 * @brief Get information about memory regions.
 * Get largest free area of RAM & get free and total physical memory.
 * 
 * @param [in] mboot - given multiboot information structure.
 * @param [in] start_addr - given starting address of memory.
 * @param [in] size - given pointer to store the size of memory.
 */
void pmm_get_memory(const multiboot_t *mboot, u32 *start_addr, u32 *size);

/**
 * @brief Initialize a memory region.
 * 
 * @param [in] base_addr - given base address of the region.
 * @param [in] size - given size of the region.
 */
void pmm_region_init(u32 base_addr, u32 size);

/**
 * @brief Deinitialize a memory region.
 * 
 * @param [in] base_addr - given base address of the region.
 * @param [in] size - given size of the region.
 */
void pmm_region_deinit(u32 base_addr, u32 size);

/**
 * @brief Allocate a block of memory.
 * 
 * @param [in] n - given number of blocks to allocate.
 * @return pointer to the allocated memory block.
 */
u32 *pmm_blocks_alloc(u32 n);

/**
 * @brief Free a block of memory.
 * 
 * @param [in] addr - given pointer to the memory block to free.
 * @param [in] n - given number of blocks to free.
 */
void pmm_free_blocks(u32 *addr, u32 n);

/**
 * @brief Get max possible number of blocks.
 * 
 * @return max number of blocks. 
 */
u32 pmm_get_max_blocks(void);

/**
 * @brief Get number of used physical memory blocks.
 * 
 * @return number of used blocks. 
 */
u32 pmm_get_used_blocks(void);

/**
 * @brief Get RAM size.
 * 
 * @return total amount of physical memory in bytes.
 */
u32 pmm_get_phys_mem_total(void);

/**
 * @brief Get free RAM size.
 * 
 * @return amount of available physical memory in bytes.
 */
u32 pmm_get_phys_mem_free(void);

} // namespace memory
} // namespace core
} // namespace kernel

#endif /* _NOS_KERNEL_PMM_HPP_ */