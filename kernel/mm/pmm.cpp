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

PhysicalMemoryManager::PhysicalMemoryManager(void) noexcept
{
    m_memory_map  = nullptr;
    m_max_blocks  = 0;
    m_used_blocks = 0;
    m_mem_total   = 0;
    m_mem_free    = 0;
}

void PhysicalMemoryManager::set_block(u32 bit) 
{
    m_memory_map[bit/32] |= (1 << (bit % 32));
}

void PhysicalMemoryManager::unset_block(u32 bit) 
{
    m_memory_map[bit/32] &= ~(1 << (bit % 32));
}

bool PhysicalMemoryManager::test_block(u32 bit) 
{
    return m_memory_map[bit/32] & (1 << (bit % 32));
}

s32 PhysicalMemoryManager::find_first_free_blocks(u32 n) noexcept
{
    s32 bit, start_bit;
    u32 free_blocks;

    // not able to return memory
    if(!n)
        return -1;

    for(u32 i = 0; i < m_max_blocks / 32; i++) {
        if(m_memory_map[i] != 0xFFFFFFFF) {

            for(s32 j = 0; j < 32; j++) {
                bit = 1 << j;

                if(!(m_memory_map[i] & bit)) {
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

void PhysicalMemoryManager::initialize(const multiboot_t& mboot) noexcept
{
    // set start address, size of available memory
    // set total, used & free physical memory
    get_memory(mboot);

    m_memory_map  = reinterpret_cast<u32*>(m_start_addr);
    m_max_blocks  = m_size / BLOCK_SIZE;
    m_used_blocks = m_max_blocks;

    kstd::memset(m_memory_map, 0xFF, m_max_blocks / BITS_PER_BYTE);
    
    // free some available blocks of memory
    region_init(m_start_addr, m_size);
}

void PhysicalMemoryManager::region_init(u32 base_addr, u32 size) noexcept
{
    // convert memory address to blocks
    s32 align = base_addr / BLOCK_SIZE;
    s32 n     = size / BLOCK_SIZE;

    while(n > 0) {
        unset_block(align);
        m_used_blocks--;
        align++;
        n--;
    }

    set_block(0);
}

void PhysicalMemoryManager::region_deinit(u32 base_addr, u32 size) noexcept
{
    // convert memory address to blocks
    s32 align = base_addr / BLOCK_SIZE;
    s32 n     = size / BLOCK_SIZE;

    while(n > 0) {
        set_block(align);
        m_used_blocks++;
        align++;
        n--;
    }
}

u32 *PhysicalMemoryManager::blocks_alloc(u32 n) noexcept
{
    if((m_max_blocks - m_used_blocks) <= n)
        return nullptr; // not enough of free blocks
    
    s32 starting_block = find_first_free_blocks(n);

    if(starting_block == -1)
        return nullptr; // there is no n blocks in a row to allocate

    for(u32 i = 0; i < n; i++)
        set_block(starting_block + i);

    m_used_blocks += n;
    s32 addr = starting_block * BLOCK_SIZE;

    return reinterpret_cast<u32*>(addr);
}

void PhysicalMemoryManager::free_blocks(u32 *addr, u32 n) noexcept
{
    s32 starting_block = reinterpret_cast<u32>(addr) / BLOCK_SIZE;
    
    for(u32 i = 0; i < n; i++)
        unset_block(starting_block + i);

    m_used_blocks -= n;
}

u32 PhysicalMemoryManager::get_max_blocks(void) const noexcept
{
    return m_max_blocks;
}

u32 PhysicalMemoryManager::get_used_blocks(void) const noexcept
{
    return m_used_blocks;
}

u32 PhysicalMemoryManager::get_total_memory(void) const noexcept
{
    return m_mem_total;
}

u32 PhysicalMemoryManager::get_free_memory(void) const noexcept
{
    return m_mem_free;
}

void PhysicalMemoryManager::get_memory(const multiboot_t& mboot) noexcept
{
    multiboot_memory_map_t *mmmt;
    u32 max_entry_size = 0;
    

    if(!(mboot.flags >> 6 & 0x1))
        kstd::panic("%s\n", "invalid memory map given by GRUB bootloader");

    for(u32 i = 0; i < mboot.mmap_length; i += sizeof(multiboot_memory_map_t)) {
       mmmt = reinterpret_cast<multiboot_memory_map_t*>((mboot.mmap_addr + i));
        
       if(mmmt->type == MULTIBOOT_MEMORY_AVAILABLE) {
            m_mem_free += mmmt->len;
    
           if(mmmt->len > max_entry_size)
                max_entry_size = mmmt->len;
       }

       m_mem_total += mmmt->len;
    }

    m_start_addr = KERNEL_END_PADDR;
    m_size       = max_entry_size;
}

PhysicalMemoryManager pmm;

} // namespace memory
} // namespace core
} // namespace kernel