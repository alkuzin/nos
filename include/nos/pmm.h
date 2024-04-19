/*
MIT License

Copyright (c) 2024 Alexander (@alkuzin)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/* Physical Memory Management */

#ifndef _NOS_KERNEL_PMM_H_
#define _NOS_KERNEL_PMM_H_

#include <nos/multiboot.h>
#include <stdint.h>
#include <stddef.h>

#define BLOCK_SIZE     4096 /* 4KB */
#define BITS_PER_BYTE  8

/* set block in the memory map */
void pmm_set_block(uint32_t bit);

/* unset block in the memory map */
void pmm_unset_block(uint32_t bit);

/* test if a block in the memory map is set/used */
bool pmm_test_block(uint32_t bit);

/* n - number of blocks */
int32_t pmm_find_first_free_blocks(uint32_t n);

void pmm_init(uint32_t start_addr, uint32_t size);

/* get largest free area of RAM & get free and total physical memory */
void pmm_get_memory(const multiboot_t *boot_info, uint32_t *start_addr, uint32_t *size);

void pmm_region_init(uint32_t base_addr, uint32_t size);

void pmm_region_deinit(uint32_t base_addr, uint32_t size);

uint32_t *pmm_blocks_alloc(uint32_t n);

void pmm_free_blocks(uint32_t *addr, uint32_t n);

void __attribute__((unused)) __display_memory(multiboot_t *boot_info);

#endif /* _NOS_KERNEL_PMM_H_ */
