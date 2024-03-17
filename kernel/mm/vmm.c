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

#include <kernel/multiboot.h>
#include <libk/stdint.h>
#include <libk/stddef.h>
#include <libk/memory.h>
#include <kernel/vmm.h>
#include <kernel/pmm.h>
#include <kernel/tty.h>

page_dir_t *cur_page_dir = 0;

uint32_t *vmm_get_pt_entry(page_table_t *pt, const uint32_t addr)
{
    if (!pt)
        return NULL;

    return &pt->entries[PT_INDEX(addr)];
}

uint32_t *vmm_get_pd_entry(page_dir_t *pd, const uint32_t addr)
{
    if (!pd)
        return NULL;

    return &pd->entries[PT_INDEX(addr)];
}

uint32_t *vmm_get_page(const uint32_t vaddr)
{
    uint32_t *entry, *page;
    page_table_t *table;
    page_dir_t   *pd;

    /* get page directory */
    pd = cur_page_dir;

    /* get page table in directory */
    entry = &pd->entries[PD_INDEX(vaddr)];
    table = (page_table_t *)PAGE_PADDRESS(entry);
    
    /* get page in table */
    page = &table->entries[PT_INDEX(vaddr)];

    return page;
}

void *vmm_page_alloc(uint32_t *page) 
{
    void *block;

    block = pmm_blocks_alloc(1);

    if(block) {
        SET_FRAME(page, (uint32_t)block);
        SET_ATTRIBUTE(page, PTE_PRESENT);
    }

    return block;
}

void vmm_free_page(uint32_t *page)
{
    void *addr;

    addr = (void *)PAGE_PADDRESS(page);

    if(addr)
        pmm_free_blocks(addr, 1);

    CLEAR_ATTRIBUTE(page, PTE_PRESENT);
}

bool vmm_set_page_dir(page_dir_t *pd)
{
    if(!pd)
        return false;

    cur_page_dir = pd;

    /* cr3 register contains address of the current page directory */
    __asm__ volatile("mov %0, %%cr3" :: "r"((uint32_t)pd));

    return true;
}

void vmm_flush_tlb_entry(uint32_t vaddr) {
    __asm__ volatile("cli; invlpg (%0); sti" : : "r"(vaddr));
}

bool vmm_map_page(void *paddr, void *vaddr)
{
   uint32_t     *entry, *page;
   page_table_t *table;
   page_dir_t   *pd;

   pd    = cur_page_dir;
   entry = &pd->entries[PD_INDEX((uint32_t)vaddr)];

   if((*entry & PTE_PRESENT) != PTE_PRESENT) {
        table = (page_table_t *)pmm_blocks_alloc(1);

        if(!table)
            return false;

        bzero(table, sizeof(page_table_t));

        entry = &pd->entries[PD_INDEX((uint32_t)vaddr)];

        SET_ATTRIBUTE(entry, PDE_PRESENT);
        SET_ATTRIBUTE(entry, PDE_READ_WRITE);
        SET_FRAME(entry, (uint32_t)table);
   }

    table = (page_table_t *)PAGE_PADDRESS(entry);
    page  = &table->entries[PT_INDEX((uint32_t)vaddr)];
    
    SET_ATTRIBUTE(page, PTE_PRESENT);
    SET_FRAME(page, (uint32_t)paddr);

    return true;
}

void vmm_unmap_page(void *vaddr)
{
    uint32_t *page;

    page = vmm_get_page((uint32_t)vaddr);

    SET_FRAME(page, 0);
    CLEAR_ATTRIBUTE(page, PTE_PRESENT);
}

bool vmm_init(void)
{
    page_table_t *table, *table3G;
    uint32_t page, frame, vaddr;
    uint32_t *entry1, *entry2;
    page_dir_t *dir;


    /* default page directory */
    dir = (page_dir_t *)pmm_blocks_alloc(3);

    /* out of memory */
    if(!dir)
        return false;

    /* clear page directory and set as current */
    bzero(dir, sizeof(page_dir_t));

    for(uint32_t i = 0; i < 1024; i++)
        dir->entries[i] = 0x02;
    
    /* default page table */
    table = (page_table_t *)pmm_blocks_alloc(1);


    /* out of memory */
    if(!table)
        return false;

    table3G = (page_table_t *)pmm_blocks_alloc(1);

    /* out of memory */
    if(!table3G)
        return false;

    bzero(table, sizeof(page_table_t));
    bzero(table3G, sizeof(page_table_t));

    frame = 0x0;
    vaddr = 0x0;

    for(uint32_t i = 0; i < 1024; i++) {
        page = 0;
        SET_ATTRIBUTE(&page, PTE_PRESENT);
        SET_ATTRIBUTE(&page, PTE_READ_WRITE);
        SET_FRAME(&page, frame);

        /* add page to 3GB page table */
        table3G->entries[PT_INDEX(vaddr)] = page;
    
        frame += PAGE_SIZE;
        vaddr += PAGE_SIZE;
    }
    
    frame = KERNEL_ADDR;
    vaddr = 0xC0000000;

    for(uint32_t i = 0; i < 1024; i++) {
        page = 0;
        SET_ATTRIBUTE(&page, PTE_PRESENT);
        SET_ATTRIBUTE(&page, PTE_READ_WRITE);
        SET_FRAME(&page, frame);

        /* add page to 3GB page table */
        table->entries[PT_INDEX(vaddr)] = page;
    
        frame += PAGE_SIZE;
        vaddr += PAGE_SIZE;
    }

    entry1 = &dir->entries[PD_INDEX(0xC0000000)];

    SET_ATTRIBUTE(entry1, PDE_PRESENT);
    SET_ATTRIBUTE(entry1, PDE_READ_WRITE);

    /* 3GB directory entry points to default page table*/
    SET_FRAME(entry1, (uint32_t)table); 

    entry2 = &dir->entries[PD_INDEX(0x00000000)];

    SET_ATTRIBUTE(entry2, PDE_PRESENT);
    SET_ATTRIBUTE(entry2, PDE_READ_WRITE);

    /* default directory entry points to 3GB page table*/
    SET_FRAME(entry2, (uint32_t)table3G);

    cur_page_dir = dir;

    /* enable paging */
    __asm__ volatile(
        "movl %cr0, %eax;"
        "orl $0x80000001, %eax;"
        "movl %eax, %cr0;"
    );

    return true;
}
