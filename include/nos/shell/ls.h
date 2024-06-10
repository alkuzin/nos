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
 * @file  ls.h
 * @brief Contain kernel shell Unix-like ls implementation.
 *
 * @details This header file contain ls auxilary functions.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   10.06.2024 
 */

#ifndef _NOS_KERNEL_SHELL_LS_H_
#define _NOS_KERNEL_SHELL_LS_H_

#include <nos/initrd.h>
#include <nos/types.h>
#include <nos/stat.h>

/* file structure */
typedef struct __ls_file_s {
    stat_t stat;
    char   mode[12];
    // char date[16];    // TODO: add datetime
    // char   user[256]; // TODO: add user name
    // time_t mtime;     // TODO: add time
} ls_file_t;

/* ls structure */
typedef struct __ls_s {
    char      dirname[INITRD_MAX_NAME_SIZE];
    ls_file_t files[INITRD_MAX_FILES];
    u32       count;
} ls_t;

/** @brief Display list of files. */
void ksh_ls(void);

#endif /* _NOS_KERNEL_SHELL_LS_H_ */