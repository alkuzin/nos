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

/*
Global Descriptor Table (GDT) is a structure specific to the IA-32 
and x86-64 architectures. It contains entries telling the CPU about memory segments.
*/

#include <kernel/multiboot.h>
#include <libk/stdint.h>
#include <libk/memory.h>
#include <kernel/tty.h>
#include <libk/math.h>
#include <kernel/mm.h>


static uint32_t page_frame_min;
static uint32_t page_frame_max;
static uint32_t total_alloc;

static uint32_t page_dirs[PAGES_DIRS][1024] __attribute__((aligned(PAGE_SIZE)));
static uint32_t page_dir_used[PAGES_DIRS];

uint8_t physical_memory_bitmap[PAGES_FRAMES / 8];


void pmm_init(uint32_t mem_low, uint32_t mem_high)
{
    page_frame_min = ceil_div(mem_low, PAGE_SIZE);
    page_frame_max = mem_high / PAGE_SIZE;
    total_alloc    = 0;

    bzero(physical_memory_bitmap, sizeof(physical_memory_bitmap));
}

void memory_init(uint32_t mem_high, uint32_t physical_alloc_start)
{
    initial_page_dir[0] = 0;

    initial_page_dir[1023] = ((uint32_t) initial_page_dir - KERNEL_START) | PFLAG_PRESENT | PFLAG_WRITE;

    pmm_init(physical_alloc_start, mem_high);
    bzero(page_dirs, PAGE_SIZE * PAGES_DIRS);
    bzero(page_dir_used, PAGES_DIRS);
}

void invalidate(uint32_t vaddr) {
    __asm__ volatile("invlpg %0" :: "m" (vaddr));
}
