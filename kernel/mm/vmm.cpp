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

#include <kernel/arch/x86/system.hpp>
#include <kernel/kstd/cstring.hpp>
#include <kernel/memlayout.hpp>
#include <kernel/vmm.hpp>
#include <kernel/pmm.hpp>


namespace kernel {
namespace core {
namespace memory {
namespace vmm {

page_dir_t *cur_page_dir = 0;

u32 *get_pt_entry(page_table_t *pt, const u32 addr)
{
    if (!pt)
        return nullptr;

    return &pt->entries[PT_INDEX(addr)];
}

u32 *get_pd_entry(page_dir_t *pd, const u32 addr)
{
    if (!pd)
        return nullptr;

    return &pd->entries[PT_INDEX(addr)];
}

u32 *get_page(const u32 vaddr)
{
    // get page directory
    page_dir_t *pd = cur_page_dir;

    // get page table in directory
    u32 *entry          = &pd->entries[PD_INDEX(vaddr)];
    page_table_t *table = reinterpret_cast<page_table_t*>(PAGE_PADDRESS(entry));
    
    // get page in table
    u32 *page = &table->entries[PT_INDEX(vaddr)];

    return page;
}

void *page_alloc(u32 *page) 
{
    void *block = pmm::blocks_alloc(1);

    if(block) {
        SET_FRAME(page, reinterpret_cast<u32>(block));
        SET_ATTRIBUTE(page, PTE_PRESENT);
    }

    return block;
}

void free_page(u32 *page)
{
    void *addr = reinterpret_cast<void*>(PAGE_PADDRESS(page));

    if(addr)
        pmm::free_blocks(reinterpret_cast<u32*>(addr), 1);

    CLEAR_ATTRIBUTE(page, PTE_PRESENT);
}

bool set_page_dir(page_dir_t *pd)
{
    if(!pd)
        return false;

    cur_page_dir = pd;

    // cr3 register contains address of the current page directory
    __asm__ volatile("movl %%eax, %%cr3" :: "a"(reinterpret_cast<u32>(cur_page_dir)));

    return true;
}

void flush_tlb_entry(u32 vaddr)
{
    arch::x86::cli();
    __asm__ volatile("invlpg (%0);" : : "r"(vaddr));
    arch::x86::sti();
}

bool map_page(void *paddr, void *vaddr)
{
   page_table_t *table;

   page_dir_t *pd = cur_page_dir;
   u32 *entry     = &pd->entries[PD_INDEX(reinterpret_cast<u32>(vaddr))];

   if((*entry & PTE_PRESENT) != PTE_PRESENT) {
        table = reinterpret_cast<page_table_t*>(pmm::blocks_alloc(1));

        if(!table)
            return false;

        kstd::bzero(table, sizeof(page_table_t));

        entry = &pd->entries[PD_INDEX(reinterpret_cast<u32>(vaddr))];

        SET_ATTRIBUTE(entry, PDE_PRESENT);
        SET_ATTRIBUTE(entry, PDE_READ_WRITE);
        SET_FRAME(entry, reinterpret_cast<u32>(table));
   }

    table     = reinterpret_cast<page_table_t*>(PAGE_PADDRESS(entry));
    u32 *page = &table->entries[PT_INDEX(reinterpret_cast<u32>(vaddr))];
    
    SET_ATTRIBUTE(page, PTE_PRESENT);
    SET_FRAME(page, reinterpret_cast<u32>(paddr));

    vmm::flush_tlb_entry(reinterpret_cast<u32>(vaddr));

    return true;
}

void vmm_unmap_page(void *vaddr)
{
    u32 *page = vmm::get_page(reinterpret_cast<u32>(vaddr));

    SET_FRAME(page, 0);
    CLEAR_ATTRIBUTE(page, PTE_PRESENT);
    
    vmm::flush_tlb_entry(reinterpret_cast<u32>(vaddr));
}

bool vmm_init(void)
{
    page_table_t *table, *table3G;
    u32 page, frame, vaddr;
    u32 *entry1, *entry2;


    // default page directory
    page_dir_t *dir = reinterpret_cast<page_dir_t*>(pmm::blocks_alloc(3));

    // out of memory
    if(!dir)
        return false;

    // clear page directory and set as current
    kstd::bzero(dir, sizeof(page_dir_t));

    for(u32 i = 0; i < 1024; i++)
        dir->entries[i] = 0x02;
    
    // default page table
    table = reinterpret_cast<page_table_t*>(pmm::blocks_alloc(1));

    // out of memory
    if(!table)
        return false;

    table3G = reinterpret_cast<page_table_t*>(pmm::blocks_alloc(1));

    // out of memory
    if(!table3G)
        return false;

    kstd::bzero(table, sizeof(page_table_t));
    kstd::bzero(table3G, sizeof(page_table_t));

    frame = 0x0;
    vaddr = 0x0;

    for(u32 i = 0; i < 1024; i++) {
        page = 0;
        SET_ATTRIBUTE(&page, PTE_PRESENT);
        SET_ATTRIBUTE(&page, PTE_READ_WRITE);
        SET_FRAME(&page, frame);

        // add page to 3GB page table
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

        // add page to 3GB page table
        table->entries[PT_INDEX(vaddr)] = page;
    
        frame += PAGE_SIZE;
        vaddr += PAGE_SIZE;
    }

    entry1 = &dir->entries[PD_INDEX(0xC0000000)];

    SET_ATTRIBUTE(entry1, PDE_PRESENT);
    SET_ATTRIBUTE(entry1, PDE_READ_WRITE);

    // 3GB directory entry points to default page table
    SET_FRAME(entry1, reinterpret_cast<u32>(table)); 

    entry2 = &dir->entries[PD_INDEX(0x00000000)];

    SET_ATTRIBUTE(entry2, PDE_PRESENT);
    SET_ATTRIBUTE(entry2, PDE_READ_WRITE);

    // default directory entry points to 3GB page table
    SET_FRAME(entry2, (u32)table3G);

    vmm::set_page_dir(dir);
    arch::x86::enable_paging();

    return true;
}

} // namespace vmm
} // namespace memory
} // namespace core
} // namespace kernel