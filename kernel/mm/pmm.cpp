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

#include <kernel/kstd/cstring.hpp>
#include <kernel/kstd/cstdio.hpp>
#include <kernel/pmm.hpp>


namespace kernel {
namespace core {
namespace memory {
namespace pmm {

static u32 *memory_map    = 0;
static u32 max_blocks     = 0;
static u32 used_blocks    = 0;
static u32 phys_mem_total = 0;
static u32 phys_mem_free  = 0;


void set_block(u32 bit) 
{
    memory_map[bit/32] |= (1 << (bit % 32));
}

void unset_block(u32 bit) 
{
    memory_map[bit/32] &= ~(1 << (bit % 32));
}

bool test_block(u32 bit) 
{
    return memory_map[bit/32] & (1 << (bit % 32));
}

s32 find_first_free_blocks(u32 n)
{
    s32 bit, start_bit;
    u32 free_blocks;

    // not able to return memory
    if(!n)
        return -1;

    for(u32 i = 0; i < max_blocks / 32; i++) {
        if(memory_map[i] != 0xFFFFFFFF) {

            for(s32 j = 0; j < 32; j++) {
                bit = 1 << j;

                if(!(memory_map[i] & bit)) {
                    start_bit   = i * 32 + bit;
                    free_blocks = 0;

                    for(u32 count = 0; count <= n; count++) {
                        if(!test_block(start_bit + count))
                            free_blocks++;

                        // found enough free space
                        if(free_blocks == n)
                            return i * 32 + j;
                    }
                }
            }
        }
    }

    return -1; // there is no free region of memory with size n
}

void init(u32 start_addr, u32 size)
{
    memory_map  = reinterpret_cast<u32*>(start_addr);
    max_blocks  = size / BLOCK_SIZE;
    used_blocks = max_blocks;

    kstd::memset(memory_map, 0xFF, max_blocks / BITS_PER_BYTE);
}

void region_init(u32 base_addr, u32 size)
{
    // convert memory address to blocks
    s32 align = base_addr / BLOCK_SIZE;
    s32 n     = size / BLOCK_SIZE;

    while(n > 0) {
        unset_block(align);
        used_blocks--;
        align++;
        n--;
    }

    set_block(0);
}

void region_deinit(u32 base_addr, u32 size)
{
    // convert memory address to blocks
    s32 align = base_addr / BLOCK_SIZE;
    s32 n     = size / BLOCK_SIZE;

    while(n > 0) {
        set_block(align);
        used_blocks++;
        align++;
        n--;
    }
}

u32 *blocks_alloc(u32 n)
{
    if((max_blocks - used_blocks) <= n)
        return nullptr; // not enough of free blocks
    
    s32 starting_block = find_first_free_blocks(n);

    if(starting_block == -1)
        return nullptr; // there is no n blocks in a row to allocate

    for(u32 i = 0; i < n; i++)
        set_block(starting_block + i);

    used_blocks += n;
    s32 addr = starting_block * BLOCK_SIZE;

    return reinterpret_cast<u32*>(addr);
}

void free_blocks(u32 *addr, u32 n)
{
    s32 starting_block = reinterpret_cast<u32>(addr) / BLOCK_SIZE;
    
    for(u32 i = 0; i < n; i++)
        unset_block(starting_block + i);

    used_blocks -= n;
}

void get_memory(const multiboot_t& mboot, u32 *start_addr, u32 *size)
{
    multiboot_memory_map_t *mmmt;
    u32 max_entry_size = 0;

    for(u32 i = 0; i < mboot.mmap_length; i += sizeof(multiboot_memory_map_t)) {
       mmmt = reinterpret_cast<multiboot_memory_map_t*>((mboot.mmap_addr + i));
        
       if(mmmt->type == MULTIBOOT_MEMORY_AVAILABLE) {
            phys_mem_free += mmmt->len;
    
           if(mmmt->len > max_entry_size)
                max_entry_size = mmmt->len;
       }

       phys_mem_total += mmmt->len;
    }

    *start_addr = KERNEL_END_PADDR;
    *size       = max_entry_size;
}

u32 get_max_blocks(void)
{
    return max_blocks;
}

u32 get_used_blocks(void)
{
    return used_blocks;
}

u32 get_phys_mem_total(void)
{
    return phys_mem_total;
}

u32 get_phys_mem_free(void)
{
    return phys_mem_free;
}

} // namespace pmm
} // namespace memory
} // namespace core
} // namespace kernel