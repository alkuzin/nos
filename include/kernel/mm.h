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

#ifndef _KERNEL_MM_H_
#define _KERNEL_MM_H_

#include <kernel/multiboot.h>
#include <libk/stdint.h>


#define KERNEL_START  0xC0000000
#define PFLAG_PRESENT (1 << 0)
#define PFLAG_WRITE   (1 << 1)
#define PAGE_SIZE     0x1000
#define PAGES_DIRS    256
#define PAGES_FRAMES  (0x100000000 / PAGE_SIZE / 8)


extern uint32_t initial_page_dir[1024];

void memory_init(uint32_t mem_high, uint32_t physical_alloc_start);

void pmm_init(uint32_t mem_low, uint32_t mem_high);

void invalidate(uint32_t vaddr);

#endif /* _KERNEL_MM_H_ */
