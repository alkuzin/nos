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

#include <nos/panic.hpp>
#include <nos/mm.hpp>


namespace kernel {
namespace core {
namespace memory {

void memory_init(multiboot_t *mboot)
{
    u32  start_addr, size;

    if(!(mboot->flags >> 6 & 0x1))
        lib::panic("%s\n", "invalid memory map given by GRUB bootloader");

    /* initializing physical memory manager */

    /* set start address, size of available memory
     * set total, used & free physical memory */
    pmm_get_memory(mboot, &start_addr, &size);
    pmm_init(start_addr, size);
    
    /* free some available blocks of memory */
    pmm_region_init(start_addr, size);
}

} // namespace memory
} // namespace core
} // namespace kernel