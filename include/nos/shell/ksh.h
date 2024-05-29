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
 * @file  ksh.h
 * @brief Contain kernel shell functions.
 *
 * @details This header file contain main kernel shell functions
 * and builtin commands.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   15.05.2024 
 */

#ifndef _NOS_KERNEL_SHELL_H_
#define _NOS_KERNEL_SHELL_H_

#include <stddef.h>
#include <stdint.h>

#include <nos/multiboot.h>

/** @brief Enumeration of builtin CLI themes. */
typedef enum {
    THEME_DEFAULT,
    THEME_CLASSIC
} theme_t;

/**
 * @brief Initialize kernel shell.
 * 
 * @param [in] boot_info - given multiboot information structure.
 */
void ksh_init(multiboot_t *boot_info);

/**
 * @brief Execute builtin shell commands.
 * 
 * @param [in] boot_info - given multiboot information structure.
 * @param [in] cmd - given shell command string.
 */
void ksh_exec(multiboot_t *boot_info, const char *cmd);

/**
 * @brief print shell warning in case of incorrect command.
 * 
 * @param [in] cmd - given shell command string.
 */
void ksh_warning(const char *cmd);

/** @brief Clear terminal. */
void ksh_clear(void);

/**
 * @brief Display list of available memory.
 * 
 * @param [in] boot_info - given multiboot information structure.
 */
void ksh_lsmem(multiboot_t *boot_info);

/** @brief Display list of available shell commands. */
void ksh_help(void);

/**
 * @brief Change CLI theme.
 * 
 * @param [in] theme - given theme type.
 */
void ksh_theme(theme_t theme);

/** @brief Display list of current processes. */
void ksh_lsproc(void);

#endif /* _NOS_KERNEL_SHELL_H_ */