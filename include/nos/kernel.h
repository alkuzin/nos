/*
MIT License

Copyright (c) 2024 Alexander (@alkuzin)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef _NOS_KERNEL_H_
#define _NOS_KERNEL_H_

#include <nos/multiboot.h>
#include <nos/tty.h>
#include <stdint.h>

#define __OS_NAME__            "nos"
#define __OS_VERSION__         "v0.0.1"
#define __OS_ARCH__            "x86_32"
#define __OS_BUILD_DATE__      __DATE__
#define __OS_BUILD_TIME__      __TIME__
#define __OS_INFO_FMT__        " %s (%s %s) (c) @alkuzin - 2024\n"
#define __OS_BUILD_INFO_FMT__  "%s %s <%s>\n"

#define __DISPLAY_OS_INFO() \
kprintf(__OS_INFO_FMT__, __OS_NAME__, __OS_VERSION__, __OS_ARCH__)

#define __DISPLAY_OS_BUILD_INFO() \
kprintf(__OS_BUILD_INFO_FMT__, " Build time:", __OS_BUILD_TIME__, __OS_BUILD_DATE__)

/* boot kernel */
void kboot(multiboot_t *boot_info);

/* kernel main function */
extern void kmain(uint32_t magic, multiboot_t *boot_info);

#endif /* _NOS_KERNEL_H_ */
