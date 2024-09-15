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

#include <nos/kheap.hpp>
#include <nos/types.hpp>
#include <nos/pmm.hpp>
#include <nos/vmm.hpp>


namespace kernel {
namespace core {
namespace memory {

kmalloc_block_t *kmalloc_head = nullptr; /* start of kmalloc blocks linked list */
u32 kmalloc_vaddr = 0; /* kmalloc virtual address */
u32 kmalloc_paddr = 0; /* kmalloc physical address */
u32 kmalloc_pages = 0; /* total kmalloc pages */

void *kmalloc_get_head(void)
{
    return (void *)(kmalloc_head);
}

void kmalloc_init(const usize n) /* n - number of bytes */
{
    u32 *page;
    u32 i, v;

    kmalloc_pages = n / PAGE_SIZE;
    
    if(n % PAGE_SIZE > 0)
        kmalloc_pages++;

    kmalloc_paddr = (u32)pmm_blocks_alloc(kmalloc_pages);
    kmalloc_head  = (kmalloc_block_t *)kmalloc_vaddr;

    /* map in pages */
    i = 0;
    v = kmalloc_vaddr;

    while(i < kmalloc_pages) {
        /* allocate contiguous physical & virtual memory */ 
        vmm_map_page((void *)(kmalloc_paddr + i * PAGE_SIZE), (void *)v);

        page = vmm_get_page(v);

        /* read/write access for dynamically allocated pages */
        SET_ATTRIBUTE(page, PTE_READ_WRITE);

        v += PAGE_SIZE;
        i++;
    }

    if(kmalloc_head) {
        kmalloc_head->size    = (kmalloc_pages * PAGE_SIZE) - sizeof(kmalloc_block_t);
        kmalloc_head->is_free = true;
        kmalloc_head->next    = nullptr;
    }
}

void kmalloc_split(kmalloc_block_t *node, const u32 size)
{
    kmalloc_block_t *new_node;

    new_node = (kmalloc_block_t *)(reinterpret_cast<u8*>(node) + size + sizeof(kmalloc_block_t));

    new_node->size    = node->size - size - sizeof(kmalloc_block_t);
    new_node->is_free = true;
    new_node->next    = node->next;

    node->size    = size;
    node->is_free = false;
    node->next    = new_node;
}

void *kmalloc_next_block(const u32 size)
{
    kmalloc_block_t *cur;
    u32 vaddr, page;
    u32 *temp_page;
    u8  pages;

    cur  = nullptr;

    /* nothing to allocate */
    if(size == 0)
        return nullptr;

    /* if there is no bytes to allocate - init it first */
    if(!kmalloc_head->size)
        kmalloc_init(size);

    /* find first available block in list */
    cur = kmalloc_head;
    while(((cur->size < size) || !cur->is_free) && cur->next) {
        cur  = cur->next;
    }

    if(cur->size == size) {
        /* node size is equal to the size that we need */
        cur->is_free = false;
    }
    else if(cur->size > size + sizeof(kmalloc_block_t)) {
        /* node size is larger than the size that we need */
        /* split it into two nodes */
        kmalloc_split(cur, size);
    }
    else {
        /* if node size is too small - allocate more pages */
        pages = 1;
        while(cur->size + pages * PAGE_SIZE < size + sizeof(kmalloc_block_t))
            pages++;
        
        vaddr = kmalloc_vaddr + kmalloc_pages * PAGE_SIZE;

        for(u8 i = 0; i < pages; i++) {
            page = 0;
            temp_page = static_cast<u32*>(vmm_page_alloc(&page));

            vmm_map_page((void *)temp_page, (void *)vaddr);
            SET_ATTRIBUTE(&page, PTE_READ_WRITE);
            vaddr += PAGE_SIZE;
            cur->size += PAGE_SIZE;
            kmalloc_pages++;
        }

        kmalloc_split(cur, size);
    }

    return reinterpret_cast<u8*>(cur) + sizeof(kmalloc_block_t);
}

void kmalloc_merge_free_blocks(void) 
{
    kmalloc_block_t *cur;

    cur  = kmalloc_head;

    while(cur && cur->next) {
        if(cur->is_free && cur->next->is_free) {
            cur->size += cur->next->size + sizeof(kmalloc_block_t);
            cur->next = cur->next->next;
        }
        cur  = cur->next;
    }
}

void kmalloc_free(void *ptr)
{
    kmalloc_block_t *cur;

    cur = kmalloc_head;
    while(cur->next) {
        if(reinterpret_cast<u8*>(cur) + sizeof(kmalloc_block_t) == ptr) {
            cur->is_free = true;
            kmalloc_merge_free_blocks();
            break;
        }
        cur = cur->next;
    }
}

} // namespace memory
} // namespace core
} // namespace kernel