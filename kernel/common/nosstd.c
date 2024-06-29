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

#include <nos/nosstd.h>
#include <asm/system.h>
#include <nos/kheap.h>
#include <nos/types.h>


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

void ksleep(u32 sec) {
	__ksleep(sec * 10000);
}

void khalt(void) 
{
	cli(); /* disable interrupts */
	for(;;);
}