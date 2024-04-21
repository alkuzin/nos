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

/* Virtual Memory Management */

#ifndef _NOS_KERNEL_VMM_H_
#define _NOS_KERNEL_VMM_H_

#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include <nos/multiboot.h>
#include <nos/vmm.h>

#define TABLES_PER_DIR  1024
#define PAGES_PER_TABLE 1024
#define PAGE_SIZE       4096

#define KERNEL_ADDR 0x50000 // TODO: move to other header file

#define PD_INDEX(addr) ((addr) >> 22)
#define PT_INDEX(addr) (((addr) >> 12) & 0x3FF) /* max index 1023 (0x3FF) */
#define PAGE_PADDRESS(dir_entry) ((*dir_entry) & ~0xFFF)
#define SET_ATTRIBUTE(entry, attr) (*entry |= attr) 
#define CLEAR_ATTRIBUTE(entry, attr) (*entry &= ~attr) 
#define TEST_ATTRIBUTE(entry, attr) (*entry & attr) 
#define SET_FRAME(entry, addr) (*entry = (*entry & ~ 0x7FFFF000) | addr)

/* PTE - Page Table Entry */
typedef enum {
    PTE_PRESENT       = 0x01,
    PTE_READ_WRITE    = 0x02, 
    PTE_USER          = 0x04,
    PTE_WRITE_THROUGH = 0x08,
    PTE_CACHE_DISABLE = 0x10,
    PTE_ACCESSED      = 0x20,
    PTE_DIRTY         = 0x40,
    PTE_PAT           = 0x80, /* PAT - Page Attribute Table */
    PTE_GLOBAL        = 0x100,
    PTE_FRAME         = 0x7FFFF000
}PAGE_TABLE_FLAGS;

/* PDE - Page Directory Entry */
typedef enum {
    PDE_PRESENT       = 0x01,
    PDE_READ_WRITE    = 0x02, 
    PDE_USER          = 0x04,
    PDE_WRITE_THROUGH = 0x08,
    PDE_CACHE_DISABLE = 0x10,
    PDE_ACCESSED      = 0x20,
    PDE_DIRTY         = 0x40,
    PDE_PAGE_SIZE     = 0x80, /* 0 - 4KB page, 1 - 4MB page */
    PDE_GLOBAL        = 0x100,
    PDE_PAT           = 0x2000,
    PDE_FRAME         = 0x7FFFF000
}PAGE_DIR_FLAGS;

typedef struct {
    u32 entries[PAGES_PER_TABLE];
} page_table_t;

typedef struct {
    u32 entries[TABLES_PER_DIR];
} page_dir_t;


/* pt - page table */
u32 *vmm_get_pt_entry(page_table_t *pt, const u32 addr);

/* pd - page directory */
u32 *vmm_get_pd_entry(page_dir_t *pd, const u32 addr);

u32 *vmm_get_page(const u32 vaddr);

/* page allocation */
void *vmm_page_alloc(u32 *page);

void vmm_free_page(u32 *page);

bool vmm_set_page_dir(page_dir_t *pd);

/* TLB - Translation Lookaside Buffer */
void vmm_flush_tlb_entry(u32 vaddr);

bool vmm_map_page(void *paddr, void *vaddr);

void vmm_unmap_page(void *vaddr);

bool vmm_init(void);

#endif /* _NOS_KERNEL_VMM_H_ */
