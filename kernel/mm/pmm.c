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

#include <string.h>
#include <stdio.h>

#include <nos/multiboot.h>
#include <nos/kernel.h>
#include <nos/types.h>
#include <nos/pmm.h>
#include <nos/tty.h>

static u32 *memory_map    = 0;
static u32 max_blocks     = 0;
static u32 used_blocks    = 0;
static u32 phys_mem_total = 0;
static u32 phys_mem_free  = 0;


void pmm_set_block(u32 bit) 
{
    memory_map[bit/32] |= (1 << (bit % 32));
}

void pmm_unset_block(u32 bit) 
{
    memory_map[bit/32] &= ~(1 << (bit % 32));
}

bool pmm_test_block(u32 bit) 
{
    return memory_map[bit/32] & (1 << (bit % 32));
}

s32 pmm_find_first_free_blocks(u32 n)
{
    s32 bit, start_bit;
    u32 free_blocks;

    /* not able to return memory */
    if(!n)
        return -1;

    for(u32 i = 0; i < max_blocks / 32; i++) {
        if(memory_map[i] != 0xFFFFFFFF) {

            for(s32 j = 0; j < 32; j++) {
                bit = 1 << j;

                if(!(memory_map[i] & bit)) {
                    start_bit = i * 32 + bit;
                    free_blocks = 0;

                    for(u32 count = 0; count <= n; count++) {
                        if(!pmm_test_block(start_bit + count))
                            free_blocks++;

                        /* found enough free space*/
                        if(free_blocks == n)
                            return i * 32 + j;
                    }
                }
            }
        }
    }

    return -1; /* there is no free region of memory with size n */
}

/* initialize physical memory manager */
void pmm_init(u32 start_addr, u32 size)
{
    memory_map  = (u32 *)start_addr;
    max_blocks  = size / BLOCK_SIZE;
    used_blocks = max_blocks;

    memset(memory_map, 0xFF, max_blocks / BITS_PER_BYTE);
}

void pmm_region_init(u32 base_addr, u32 size)
{
    s32 align, n; /* n - number of blocks */

    /* convert memory address to blocks */
    align = base_addr / BLOCK_SIZE;
    n     = size / BLOCK_SIZE;

    while(n > 0) {
        pmm_unset_block(align);
        used_blocks--;
        align++;
        n--;
    }

    pmm_set_block(0);
}

void pmm_region_deinit(u32 base_addr, u32 size)
{
    s32 align, n; /* n - number of blocks */

    /* convert memory address to blocks */
    align = base_addr / BLOCK_SIZE;
    n     = size / BLOCK_SIZE;

    while(n > 0) {
        pmm_set_block(align);
        used_blocks++;
        align++;
        n--;
    }
}

u32 *pmm_blocks_alloc(u32 n)
{
    s32 starting_block;
    u32 addr;

    if((max_blocks - used_blocks) <= n)
        return nullptr; /* not enough of free blocks */
    
    starting_block = pmm_find_first_free_blocks(n);

    if(starting_block == -1)
        return nullptr; /* there is no n blocks in a row to allocate */

    for(u32 i = 0; i < n; i++)
        pmm_set_block(starting_block + i);

    used_blocks += n;
    addr = starting_block * BLOCK_SIZE;

    return (u32 *)addr;
}

void pmm_free_blocks(u32 *addr, u32 n)
{
    s32 starting_block;

    starting_block = (u32)addr / BLOCK_SIZE;
    
    for(u32 i = 0; i < n; i++)
        pmm_unset_block(starting_block + i);

    used_blocks -= n;
}

void pmm_display_memory(multiboot_t *boot_info) 
{
    u32 free_blocks, total_bytes, used_bytes, free_bytes;
    multiboot_mmap_entry_t *mmmt;


    putk(" ---------------------------------------------------------------------\n"
         " low addr \t| high addr \t| low len \t| high len | size | type |\n"
         " ---------------------------------------------------------------------\n");

    for(u32 i = 0; i < boot_info->mmap_length; i += sizeof(multiboot_mmap_entry_t)) {
       mmmt = (multiboot_mmap_entry_t *)(boot_info->mmap_addr + i);
        
       printk(" <%#x> | <%#x> |  %#x | %#x |  %#x | ", mmmt->addr_low, 
       mmmt->addr_high, mmmt->len_low, mmmt->len_high, mmmt->size);

       switch(mmmt->type) {
            case MULTIBOOT_MEMORY_AVAILABLE:
                putk("(available)\n");
                break;
            
            case MULTIBOOT_MEMORY_RESERVED:
                putk("(reserved)\n");
                break;
            
            case MULTIBOOT_MEMORY_ACPI_RECLAIMABLE:
                putk("(reclaimable)\n");
                break;
            
            case MULTIBOOT_MEMORY_NVS:
                putk("(nvs)\n");
                break;
            
            case MULTIBOOT_MEMORY_BADRAM:
                putk("(bad RAM)\n");
                break;
       }
    }
    
    putk(" ---------------------------------------------------------------------\n");
    printk(" total: %u KB \t free: %u KB\n", phys_mem_total >> 10, phys_mem_free >> 10);
    putk(" ---------------------------------------------------------------------\n");

    free_blocks = max_blocks - used_blocks;
    total_bytes = max_blocks  * BLOCK_SIZE;
    used_bytes  = used_blocks * BLOCK_SIZE;
    free_bytes  = free_blocks * BLOCK_SIZE;
    
    printk(" total blocks: %u (%u KB) (%u MB)\n", max_blocks, total_bytes >> 10, total_bytes >> 20);
    printk(" used  blocks: %u (%u KB) (%u MB)\n", used_blocks, used_bytes >> 10, used_bytes >> 20);
    printk(" free  blocks: %u (%u KB) (%u MB)\n", free_blocks, free_bytes >> 10, free_bytes >> 20);
}

void pmm_get_memory(const multiboot_t *boot_info, u32 *start_addr, u32 *size)
{
    multiboot_mmap_entry_t *mmmt;
    u32 max_entry_size;

    max_entry_size = 0;

    for(u32 i = 0; i < boot_info->mmap_length; i += sizeof(multiboot_mmap_entry_t)) {
       mmmt = (multiboot_mmap_entry_t *)(boot_info->mmap_addr + i);
        
       if(mmmt->type == MULTIBOOT_MEMORY_AVAILABLE) {
            phys_mem_free += mmmt->len_low;
    
           if(mmmt->len_low > max_entry_size)
                max_entry_size = mmmt->len_low;
       }

       phys_mem_total += mmmt->len_low;
    }

    *start_addr = _kernel_end;
    *size       = max_entry_size;
}