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
 * @file  version.h
 * @brief Contains declarations for kernel functions and structures.
 * 
 * @details This header file includes constants, definitions related to the OS information.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   29.06.2024 
 */

#ifndef _NOS_KERNEL_VERSION_H_
#define _NOS_KERNEL_VERSION_H_

#include <nos/printk.h>
#include <nos/types.h>

#define __os_name__   "NOS"
#define __os_arch__   "x86_32"
#define __os_author__ "@alkuzin"

#define __os_version_major__  0
#define __os_version_minor__  0
#define __os_version_lower__  3

#define __os_version_format__ "v%d.%d.%d"

#define __os_build_date__       __DATE__
#define __os_build_time__       __TIME__
#define __os_compiler_version__ __VERSION__

#define __os_info_format__        "%s (" __os_version_format__ " %s) (c) %s - 2024\n"
#define __os_build_info_format__  "build time: %s %s [gcc-%s]\n"  

/**
 * @brief Macro for displaying main OS info: name, version 
 * and architecture.
 */
#define __DISPLAY_OS_INFO() \
printk(__os_info_format__, __os_name__, __os_version_major__, __os_version_minor__, \
__os_version_lower__, __os_arch__, __os_author__)

/**
 * @brief Macro for displaying kernel build info: build time
 * and build date.
 */
#define __DISPLAY_OS_BUILD_INFO() \
printk(__os_build_info_format__, __os_build_time__, __os_build_date__, __os_compiler_version__)

#endif /* _NOS_KERNEL_VERSION_H_ */