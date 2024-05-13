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

#ifndef _NOS_KERNEL_SHELL_H_
#define _NOS_KERNEL_SHELL_H_

#include <stddef.h>
#include <stdint.h>

#include <nos/multiboot.h>

typedef enum {
    THEME_DEFAULT,
    THEME_CLASSIC
} theme_t;

/* initialize kernel shell */
void ksh_init(multiboot_t *boot_info);

/* execute builtin shell commands */
void ksh_exec(multiboot_t *boot_info, const char *cmd);

/* shell warning in case of incorrect command */
void ksh_warning(const char *cmd);

/* clear terminal */
void ksh_clear(void);

/* display list of available memory */
void ksh_lsmem(multiboot_t *boot_info);

/* display list of available shell commands */
void ksh_help(void);

/* change cli theme */
void ksh_theme(theme_t theme);

#endif /* _NOS_KERNEL_SHELL_H_ */
