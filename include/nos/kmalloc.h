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

#ifndef _NOS_KERNEL_KMALLOC_H_
#define _NOS_KERNEL_KMALLOC_H_

#include <nos/pmm.h>
#include <nos/vmm.h>
#include <stdint.h>
#include <stddef.h>

#define PAGE_SIZE 4096

/* using linked list nodes for blocks of memory */
typedef struct kmalloc_block_s {
    size_t size; /* size of memory block */
    bool is_free; /* is this block of memory is free */
    struct kmalloc_block_s *next; /* pointer to the next block of memory */
} kmalloc_block_t;

/* return start of kmalloc blocks linked list */
void *kmalloc_get_head(void);

/* initialize kernel dynamic memory allocation */
void kmalloc_init(const size_t n); 

/* split memory block into two by inserting a new block */
void kmalloc_split(kmalloc_block_t *node, const uint32_t size);

/* find and allocate next block of memory */
void *kmalloc_next_block(const uint32_t size);

/* merge free blocks of memory to (partically) prevent memory fragmentation */
void kmalloc_merge_free_blocks(void);

/* free allocated memory */
void kmalloc_free(void *ptr);

#endif /* _NOS_KERNEL_KMALLOC_H_ */
