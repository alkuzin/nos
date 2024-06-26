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
 * @details This header file includes constants, definitions related to the OS information,
 * kernel setup, kernel entry point and several auxilary functions.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   17.05.2024 
 */

#ifndef _NOS_KERNEL_H_
#define _NOS_KERNEL_H_

#include <nos/multiboot.h>
#include <nos/types.h>
#include <nos/tty.h>

/** @brief OS information definitions. */
#define __OS_NAME__            "NOS"
#define __OS_VERSION__         "v0.0.3"
#define __OS_ARCH__            "x86_32"
#define __OS_BUILD_DATE__      __DATE__
#define __OS_BUILD_TIME__      __TIME__
#define __OS_INFO_FMT__        "%s (%s %s) (c) @alkuzin - 2024\n"
#define __OS_BUILD_INFO_FMT__  "%s %s <%s>\n"

#define MAX_USERNAME_SIZE 5
#define USERNAME          "alex"

#define SUPER_SECURE_PASSWORD      "12345"
#define SUPER_SECURE_PASSWORD_SIZE 6

/**
 * @brief Macro for displaying main OS info: name, version 
 * and architecture.
 */
#define __DISPLAY_OS_INFO() \
printk(__OS_INFO_FMT__, __OS_NAME__, __OS_VERSION__, __OS_ARCH__)

/**
 * @brief Macro for displaying kernel build info: build time
 * and build date.
 */
#define __DISPLAY_OS_BUILD_INFO() \
printk(__OS_BUILD_INFO_FMT__, "Build time:", __OS_BUILD_TIME__, __OS_BUILD_DATE__)

/**
 * @brief Macro for kernel panic (detecting an internal fatal error).
 * 
 * It displaying error message, file, function and line where error occured.
 * 
 * @param [in] fmt - given format string.
 * @param [in] ... - given variable number of arguments.
 */
#define panic(fmt, ...) __panic(__FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)

/* detatiled kernel panic */
/**
 * @brief Detailed kernel panic function.
 * 
 * It displaying error message, file, function and line where error occured.
 * 
 * @param [in] file - given filename, where error occured.
 * @param [in] func - given function name, where error occured.
 * @param [in] line - given line number, where error occured.
 * @param [in] fmt - given format string.
 * @param [in] ... - given variable number of arguments.
 */
void __panic(const char *file, const char *func, u32 line, const char *fmt, ...);

/**
 * @brief Formats and prints data.
 * 
 * @param [in] fmt - given format string.
 * @param [in] ... - given variable number of arguments.
 */
void printk(const char *fmt, ...);

/**
 * @brief Auxilar function for formating and printing data.
 * 
 * @param [in] fmt - given format string.
 * @param [in] args - given variable number of arguments.
 */
void vprintk(const char *fmt, va_list args);

/* boot kernel */

/**
 * @brief Setup kernel.
 * 
 * Initializes kernel components such as TTY, GDT, 
 * IDT, timer and etc.
 * 
 * @param [in] boot_info - given multiboot information structure.
 */
void kboot(multiboot_t *boot_info);

/**
 * @brief Kernel entry point.
 * 
 * @param [in] magic - given magic number.
 * @param [in] mb - given multiboot information structure.
 */
extern void kmain(u32 magic, multiboot_t *mboot);

#endif /* _NOS_KERNEL_H_ */