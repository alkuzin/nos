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

/**
 * @file  memlayout.h
 * @brief Kernel memory layout.
 * 
 * @details Contains kernel memory map addresses.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   25.06.2024
 */

#ifndef _NOS_KERNEL_MEMLAYOUT_H_
#define _NOS_KERNEL_MEMLAYOUT_H_

extern u32 kernel_phys_start;
extern u32 kernel_phys_end;

#define KERNEL_START_PADDR ((u32) &kernel_phys_start)
#define KERNEL_END_PADDR   ((u32) &kernel_phys_end)
#define KERNEL_SIZE        (KERNEL_END_PADDR - KERNEL_START_PADDR)

#endif /* _NOS_KERNEL_MEMLAYOUT_H_ */