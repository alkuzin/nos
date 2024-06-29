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

#include <nos/multiboot.h>
#include <nos/memlayout.h>
#include <nos/string.h>
#include <nos/types.h>
#include <nos/vmm.h>
#include <nos/pmm.h>

#include <asm/system.h>


page_dir_t *cur_page_dir = 0;

u32 *vmm_get_pt_entry(page_table_t *pt, const u32 addr)
{
    if (!pt)
        return nullptr;

    return &pt->entries[PT_INDEX(addr)];
}

u32 *vmm_get_pd_entry(page_dir_t *pd, const u32 addr)
{
    if (!pd)
        return nullptr;

    return &pd->entries[PT_INDEX(addr)];
}

u32 *vmm_get_page(const u32 vaddr)
{
    u32 *entry, *page;
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

void *vmm_page_alloc(u32 *page) 
{
    void *block;

    block = pmm_blocks_alloc(1);

    if(block) {
        SET_FRAME(page, (u32)block);
        SET_ATTRIBUTE(page, PTE_PRESENT);
    }

    return block;
}

void vmm_free_page(u32 *page)
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
    __asm__ volatile("movl %%eax, %%cr3" :: "a"((u32)cur_page_dir));

    return true;
}

void vmm_flush_tlb_entry(u32 vaddr)
{
    cli();
    __asm__ volatile("invlpg (%0);" : : "r"(vaddr));
    sti();
}

bool vmm_map_page(void *paddr, void *vaddr)
{
   u32     *entry, *page;
   page_table_t *table;
   page_dir_t   *pd;

   pd    = cur_page_dir;
   entry = &pd->entries[PD_INDEX((u32)vaddr)];

   if((*entry & PTE_PRESENT) != PTE_PRESENT) {
        table = (page_table_t *)pmm_blocks_alloc(1);

        if(!table)
            return false;

        bzero(table, sizeof(page_table_t));

        entry = &pd->entries[PD_INDEX((u32)vaddr)];

        SET_ATTRIBUTE(entry, PDE_PRESENT);
        SET_ATTRIBUTE(entry, PDE_READ_WRITE);
        SET_FRAME(entry, (u32)table);
   }

    table = (page_table_t *)PAGE_PADDRESS(entry);
    page  = &table->entries[PT_INDEX((u32)vaddr)];
    
    SET_ATTRIBUTE(page, PTE_PRESENT);
    SET_FRAME(page, (u32)paddr);

    vmm_flush_tlb_entry((u32)vaddr);

    return true;
}

void vmm_unmap_page(void *vaddr)
{
    u32 *page;

    page = vmm_get_page((u32)vaddr);

    SET_FRAME(page, 0);
    CLEAR_ATTRIBUTE(page, PTE_PRESENT);
    
    vmm_flush_tlb_entry((u32)vaddr);
}

bool vmm_init(void)
{
    page_table_t *table, *table3G;
    u32 page, frame, vaddr;
    u32 *entry1, *entry2;
    page_dir_t *dir;


    /* default page directory */
    dir = (page_dir_t *)pmm_blocks_alloc(3);

    /* out of memory */
    if(!dir)
        return false;

    /* clear page directory and set as current */
    bzero(dir, sizeof(page_dir_t));

    for(u32 i = 0; i < 1024; i++)
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

    for(u32 i = 0; i < 1024; i++) {
        page = 0;
        SET_ATTRIBUTE(&page, PTE_PRESENT);
        SET_ATTRIBUTE(&page, PTE_READ_WRITE);
        SET_FRAME(&page, frame);

        /* add page to 3GB page table */
        table3G->entries[PT_INDEX(vaddr)] = page;
    
        frame += PAGE_SIZE;
        vaddr += PAGE_SIZE;
    }
    
    frame = KERNEL_START_PADDR;
    vaddr = 0xC0000000;

    for(u32 i = 0; i < 1024; i++) {
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
    SET_FRAME(entry1, (u32)table); 

    entry2 = &dir->entries[PD_INDEX(0x00000000)];

    SET_ATTRIBUTE(entry2, PDE_PRESENT);
    SET_ATTRIBUTE(entry2, PDE_READ_WRITE);

    /* default directory entry points to 3GB page table*/
    SET_FRAME(entry2, (u32)table3G);

    vmm_set_page_dir(dir);
    enable_paging();

    return true;
}