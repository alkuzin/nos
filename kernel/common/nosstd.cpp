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

#include <nos/nosstd.hpp>
#include <asm/system.h>
#include <nos/kheap.h>


namespace kernel {
namespace lib {

void *kmalloc(usize n)
{
    static void *ptr;

    if(!kmalloc_get_head())
        kmalloc_init(n);

    ptr = kmalloc_next_block(n);
    kmalloc_merge_free_blocks();

    return ptr;
}

void kfree(void *ptr) {
    if(!ptr)
        return;

    kmalloc_free(ptr);
}

void __ksleep(u32 microsec)
{
	u32 i;

	for (i = 0; i < microsec * 10000; i++) {
		for (i = 0; i < microsec * 10000; i++)
			nop(); /* do nothing */
	}
}

void ksleep(u32 sec)
{
	__ksleep(sec * 10000);
}

void khalt(void) 
{
	cli(); /* disable interrupts */
	for(;;);
}

} // namespace lib
} // namespace kernel