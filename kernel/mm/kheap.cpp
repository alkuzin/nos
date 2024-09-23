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

#include <kernel/kheap.hpp>


namespace kernel {
namespace core {
namespace memory {
namespace kmalloc {

block_t *kmalloc_head = nullptr; // start of kmalloc blocks linked list
u32     kmalloc_vaddr = 0;       // kmalloc virtual address
u32     kmalloc_paddr = 0;       // kmalloc physical address
u32     kmalloc_pages = 0;       // total kmalloc pages

void *get_head(void)
{
    return (void *)(kmalloc_head);
}

void init(const usize n)
{
    u32 *page;

    kmalloc_pages = n / PAGE_SIZE;
    
    if(n % PAGE_SIZE > 0)
        kmalloc_pages++;

    kmalloc_paddr = reinterpret_cast<u32>(pmm.blocks_alloc(kmalloc_pages));
    kmalloc_head  = reinterpret_cast<block_t*>(kmalloc_vaddr);

    // map in pages
    u32 i = 0;
    u32 v = kmalloc_vaddr;

    while(i < kmalloc_pages) {
        // allocate contiguous physical & virtual memory
        vmm::map_page(
            reinterpret_cast<void*>((kmalloc_paddr + i * PAGE_SIZE)),
            reinterpret_cast<void*>(v)
        );

        page = vmm::get_page(v);

        // read/write access for dynamically allocated pages
        SET_ATTRIBUTE(page, vmm::PTE_READ_WRITE);

        v += PAGE_SIZE;
        i++;
    }

    if(kmalloc_head) {
        kmalloc_head->size    = (kmalloc_pages * PAGE_SIZE) - sizeof(block_t);
        kmalloc_head->is_free = true;
        kmalloc_head->next    = nullptr;
    }
}

void split(block_t *node, const u32 size)
{
    block_t *new_node = reinterpret_cast<block_t*>(
        (reinterpret_cast<u8*>(node) + size + sizeof(block_t))
    );

    new_node->size    = node->size - size - sizeof(block_t);
    new_node->is_free = true;
    new_node->next    = node->next;
    node->size        = size;
    node->is_free     = false;
    node->next        = new_node;
}

void *next_block(const u32 size)
{
    u32 vaddr, page;
    u32 *temp_page;
    u8  pages;

    block_t *cur = nullptr;

    // nothing to allocate
    if(size == 0)
        return nullptr;

    // if there is no bytes to allocate - init it first
    if(!kmalloc_head->size)
        init(size);

    // find first available block in list
    cur = kmalloc_head;
    while(((cur->size < size) || !cur->is_free) && cur->next)
        cur = cur->next;

    if(cur->size == size) {
        // node size is equal to the size that we need
        cur->is_free = false;
    }
    else if(cur->size > size + sizeof(block_t)) {
        // node size is larger than the size that we need
        // split it into two nodes
        split(cur, size);
    }
    else {
        // if node size is too small - allocate more pages
        pages = 1;
        while(cur->size + pages * PAGE_SIZE < size + sizeof(block_t))
            pages++;
        
        vaddr = kmalloc_vaddr + kmalloc_pages * PAGE_SIZE;

        for(u8 i = 0; i < pages; i++) {
            page = 0;
            temp_page = static_cast<u32*>(vmm::page_alloc(&page));

            vmm::map_page(
                reinterpret_cast<void*>(temp_page),
                reinterpret_cast<void*>(vaddr)
            );

            SET_ATTRIBUTE(&page, vmm::PTE_READ_WRITE);
            vaddr     += PAGE_SIZE;
            cur->size += PAGE_SIZE;
            kmalloc_pages++;
        }

        split(cur, size);
    }

    return reinterpret_cast<u8*>(cur) + sizeof(block_t);
}

void merge_free_blocks(void) 
{
    block_t *cur = kmalloc_head;

    while(cur && cur->next) {
        if(cur->is_free && cur->next->is_free) {
            cur->size += cur->next->size + sizeof(block_t);
            cur->next = cur->next->next;
        }
        cur = cur->next;
    }
}

void free(void *ptr)
{
    block_t *cur = kmalloc_head;

    while(cur->next) {
        if(reinterpret_cast<u8*>(cur) + sizeof(block_t) == ptr) {
            cur->is_free = true;
            merge_free_blocks();
            break;
        }
        cur = cur->next;
    }
}
    
} // namespace kmalloc
} // namespace memory
} // namespace core
} // namespace kernel