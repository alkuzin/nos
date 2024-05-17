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
 * @file  ports.h
 * @brief Contains functions for input/output operations on ports.
 * 
 * @details
 * This header file contains inline functions for input/output operations
 * on ports in x86 architecture.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   17.05.2024 
 */

#ifndef _NOS_KERNEL_PORTS_H_
#define _NOS_KERNEL_PORTS_H_

#include <stdint.h>

/**
 * @brief Output a byte to a specified port.
 *
 * @param [in] port -given port to which the data will be written.
 * @param [in] data - given data byte to be written to the port.
 */
static inline void outb(u16 port, u8 data)
{
    __asm__ volatile("outb %1, %0" : : "dN" (port), "a" (data));
}

/**
 * @brief Receive a byte of data from a specified input/output port.
 *
 * @param port - given port from which the data will be read.
 * @return the byte of data read from the port.
 */
static inline u8 inb(u16 port)
{
    u8 rv;
    __asm__ volatile("inb %1, %0" : "=a" (rv) : "dN" (port));
    return rv;
}

#endif /* _NOS_KERNEL_PORTS_H_ */