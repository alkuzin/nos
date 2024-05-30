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
 * @file  exe.h
 * @brief Contains declarations for kernel executable.
 * 
 * @details This header file includes functions, structs related
 * to the kernel executable handeling.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   30.05.2024
 */

#ifndef _NOS_KERNEL_EXE_H_
#define _NOS_KERNEL_EXE_H_

#include <stdint.h>

#define EXE_SIGNATURE ".NOS_EXE"
#define EXE_SIGN_SIZE 8 ///< Size of executable signature.

/** @brief Kernel executable structure. */
struct exe_s {
    u8  signature[EXE_SIGN_SIZE]; ///< Signature to identify the executable format.
    u32 entry_point; ///< Entry point of the program.
    u32 end_image;   ///< Address of the end of the executable image.
    u32 stack_top;   ///< Address of the top of the stack.
    u32 memory;      ///< Amount of memory needed for executable.
}__attribute__((packed)); ///< prevent the compiler from optimizing

typedef struct exe_s exe_t;

/**
 * @brief Check is executable signature is valid.
 * 
 * @param [in] header - given executable header structure. 
 * @return true - if signature is valid.
 * @return false - otherwise.
 */
bool exe_is_valid(const exe_t *header);

/**
 * @brief Display kernel executable information.
 * 
 * @param [in] header - given executable header structure. 
 */
void exe_display_info(const exe_t *header);

/**
 * @brief Run kernel executable.
 * 
 */
void exe_run(void);

#endif /* _NOS_KERNEL_EXE_H_ */