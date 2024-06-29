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
 * @file  login.h
 * @brief Contain kernel login functions.
 *
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   10.06.2024 
 */

#ifndef _NOS_KERNEL_LOGIN_H_
#define _NOS_KERNEL_LOGIN_H_

#include <nos/types.h>

#define MAX_ATTEMPTS 3

// TODO: create structure for containing login & password
#define MAX_USERNAME_SIZE 5
#define USERNAME          "alex"

#define SUPER_SECURE_PASSWORD      "12345"
#define SUPER_SECURE_PASSWORD_SIZE 6

#define LOGIN_BANNER "   _  ______  ____ \n" \
                     "  / |/ / __ \\/ __/ \n" \
                     " /    / /_/ /\\ \\   \n" \
                     "/_/|_/\\____/___/   \n" \
                     "----------------------------------\n"

/** @brief Initialize kernel login. */
void login_init(void);

/**
 * @brief Get secure user input. 
 * 
 * @param [out] buffer - given buffer for input.
 * @param [in] size - given max size of input.
 */
void getinput(char *buffer, u32 size);

#endif /* _NOS_KERNEL_LOGIN_H_ */