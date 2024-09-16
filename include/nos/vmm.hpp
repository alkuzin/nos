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

/**
 * @file  vmm.hpp
 * @brief Contains declarations for virtual memory management.
 * 
 * @details This header file includes functions related to the
 * virtual memory management.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   17.05.2024 
 */

#ifndef _NOS_KERNEL_VMM_HPP_
#define _NOS_KERNEL_VMM_HPP_

#include <nos/multiboot.hpp>
#include <nos/string.hpp>


namespace kernel {
namespace core {
namespace memory {
    

///< Virtual memory management main macros
#define TABLES_PER_DIR  1024 ///< 1 KB
#define PAGES_PER_TABLE 1024 ///< 1 KB
#define PAGE_SIZE       4096 ///< 4 KB

#define PD_INDEX(addr) ((addr) >> 22)
#define PT_INDEX(addr) (((addr) >> 12) & 0x3FF) /* max index 1023 (0x3FF) */
#define PAGE_PADDRESS(dir_entry) ((*dir_entry) & ~0xFFF)
#define SET_ATTRIBUTE(entry, attr) (*entry |= attr) 
#define CLEAR_ATTRIBUTE(entry, attr) (*entry &= ~attr) 
#define TEST_ATTRIBUTE(entry, attr) (*entry & attr) 
#define SET_FRAME(entry, addr) (*entry = (*entry & ~ 0x7FFFF000) | addr)

///< Flags for Page Table Entry (PTE).
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

///< Flags for Page Directory Entry (PDE).
typedef enum {
    PDE_PRESENT       = 0x01,
    PDE_READ_WRITE    = 0x02, 
    PDE_USER          = 0x04,
    PDE_WRITE_THROUGH = 0x08,
    PDE_CACHE_DISABLE = 0x10,
    PDE_ACCESSED      = 0x20,
    PDE_DIRTY         = 0x40,
    PDE_PAGE_SIZE     = 0x80, /* 0 - 4 KB page, 1 - 4 MB page */
    PDE_GLOBAL        = 0x100,
    PDE_PAT           = 0x2000,
    PDE_FRAME         = 0x7FFFF000
}PAGE_DIR_FLAGS;

///< Structure for a page table.
typedef struct {
    u32 entries[PAGES_PER_TABLE];
} page_table_t;

///< Structure for a page directory.
typedef struct {
    u32 entries[TABLES_PER_DIR];
} page_dir_t;

/**
 * @brief Get the page table entry for a virtual address.
 * 
 * @param [in] pt - given pointer to page table.
 * @param [in] addr - given address.
 * @return pointer to the page table entry in case of success.
 * @return null pointer otherwise.
 */
u32 *vmm_get_pt_entry(page_table_t *pt, const u32 addr);

/**
 * @brief Get the page directory entry for a given virtual address.
 * 
 * @param [in] pd - given pointer to page directory.
 * @param [in] addr - given address.
 * @return pointer to the page directory entry in case of success.
 * @return null pointer otherwise.
 */
u32 *vmm_get_pd_entry(page_dir_t *pd, const u32 addr);

/**
 * @brief Get the page entry for a given virtual address.
 * 
 * @param [in] vaddr - given virtual address.
 * @return pointer to the page entry.
 */
u32 *vmm_get_page(const u32 vaddr);

/**
 * @brief Allocate a page.
 * 
 * @param [in] page - given page pointer.
 * @return pointer to allocated page. 
 */
void *vmm_page_alloc(u32 *page);

/**
 * @brief Free a page.
 * 
 * @param [in] page - given pointer to the page to be freed.
 */
void vmm_free_page(u32 *page);

/**
 * @brief Set the page directory. 
 * 
 * @param [in] pd - given pointer to the page directory.
 * @return true - if page directory is set successfully.
 * @return false - otherwise.
 */
bool vmm_set_page_dir(page_dir_t *pd);

/**
 * @brief Flush a TLB (Translation Lookaside Buffer) entry.
 * 
 * The Translation Lookaside Buffer (TLB) is a cache memory in a
 * computer system that stores recent translations of 
 * virtual memory to physical memory addresses.
 * 
 * @param [in] vaddr - given virtual address to flush. 
 */
void vmm_flush_tlb_entry(u32 vaddr);

/**
 * @brief Map a physical address to a virtual address.
 * 
 * @param [in] paddr - given physical address. 
 * @param [out] vaddr - given virtual address. 
 * @return true - if translation is successfull.
 * @return false - otherwise.
 */
bool vmm_map_page(void *paddr, void *vaddr);

/**
 * @brief Unmap a virtual address.
 * 
 * @param [in] vaddr - given virtual address to unmap. 
 */
void vmm_unmap_page(void *vaddr);

/**
 * @brief Initialize the virtual memory manager.
 * 
 * @return true - if initialization is successfull.
 * @return false - otherwise.
 */
bool vmm_init(void);

} // namespace memory
} // namespace core
} // namespace kernel

#endif /* _NOS_KERNEL_VMM_HPP_ */