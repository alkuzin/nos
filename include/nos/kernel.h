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
 * @file  kernel.h
 * @brief Contains declarations for kernel functions and structures.
 * 
 * @details This header file includes functions related to kernel setup & kernel entry point.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   17.05.2024 
 */

#ifndef _NOS_KERNEL_H_
#define _NOS_KERNEL_H_

#include <nos/multiboot.h>
#include <nos/types.h>

/**
 * @brief Setup kernel.
 * 
 * Initializes kernel components such as TTY, GDT, 
 * IDT, timer and etc.
 * 
 * @param [in] mboot - given multiboot information structure.
 */
void kboot(multiboot_t *mboot);

/**
 * @brief Kernel entry point.
 * 
 * @param [in] magic - given magic number.
 * @param [in] mboot - given multiboot information structure.
 */
extern void kmain(u32 magic, multiboot_t *mboot);

#endif /* _NOS_KERNEL_H_ */