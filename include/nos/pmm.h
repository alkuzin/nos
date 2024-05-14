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

/* Physical Memory Management */

#ifndef _NOS_KERNEL_PMM_H_
#define _NOS_KERNEL_PMM_H_

#include <stdint.h>
#include <stddef.h>

#include <nos/multiboot.h>

#define BLOCK_SIZE     4096 /* 4KB */
#define BITS_PER_BYTE  8


extern u32 _kernel_end;

/* set block in the memory map */
void pmm_set_block(u32 bit);

/* unset block in the memory map */
void pmm_unset_block(u32 bit);

/* test if a block in the memory map is set/used */
bool pmm_test_block(u32 bit);

/* n - number of blocks */
i32  pmm_find_first_free_blocks(u32 n);

void pmm_init(u32 start_addr, u32 size);

/* get largest free area of RAM & get free and total physical memory */
void pmm_get_memory(const multiboot_t *boot_info, u32 *start_addr, u32 *size);

void pmm_region_init(u32 base_addr, u32 size);

void pmm_region_deinit(u32 base_addr, u32 size);

u32  *pmm_blocks_alloc(u32 n);

void pmm_free_blocks(u32 *addr, u32 n);

void __attribute__((unused)) __display_memory(multiboot_t *boot_info);

#endif /* _NOS_KERNEL_PMM_H_ */
