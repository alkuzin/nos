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

#include <string.h>

#include <nos/shell/ksh.h>
#include <nos/multiboot.h>
#include <nos/keyboard.h>
#include <nos/nosstd.h>
#include <nos/initrd.h>
#include <nos/kernel.h>
#include <nos/timer.h>
#include <nos/types.h>
#include <nos/sched.h>
#include <nos/login.h>
#include <nos/tty.h>
#include <nos/gdt.h>
#include <nos/idt.h>
#include <nos/vfs.h>
#include <nos/vbe.h>
#include <nos/gfx.h>
#include <nos/mm.h>
#include <nos/pm.h>


static void test_initrd(void)
{
    s32 fd;
    char *author_content = " \nAuthor: Alexander (@alkuzin) \n"
                           "GitHub: https://github.com/alkuzin \n";    

    vfs_creat("AUTHOR", S_IFREG | S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
    vfs_creat("hw.txt", S_IFREG | S_IRUSR | S_IWUSR);
    
    fd = vfs_open("AUTHOR", O_RDWR);
    vfs_write(fd, author_content, 69);
    vfs_close(fd);
    
    fd = vfs_open("hw.txt", O_RDWR);
    vfs_write(fd, "Hello, World!\n", 15);
    vfs_close(fd);
}

void kboot(multiboot_t *boot_info)
{
    /* initializing Global Descriptor Table */
    gdt_init();
    printk(" %s\n", "kernel: initialized Global Descriptor Table");
    
    /* initializing Interrupt Descriptor Table */
    idt_init();
    printk(" %s\n", "kernel: initialized Interrupt Descriptor Table");	
    
    /* initializing timer */
    timer_init();
    printk(" %s\n", "kernel: initialized timer");	

    /* initializing memory management */
    memory_init(boot_info);
    printk(" %s\n", "kernel: initialized memory management");

    /* initializing initial ramdisk */
    initrd_init();
    printk(" %s\n", "kernel: initialized initial ramdisk");

    /* initializing Virtual File System */
    vfs_adapter_t *initrd_adapter = initrd_get_adapter();

    vfs_init(INITRD, initrd_adapter);
    printk(" %s\n", "kernel: initialized Virtual File System");

    test_initrd();
}

/* kernel entry point */
extern void kmain(u32 magic, multiboot_t *mboot)
{
    multiboot_t boot_info = *mboot;
    
    vbe_init(&boot_info);
    printk(" %s\n", "kernel: initialized VBE mode"); // TODO: add kmesg() for logs: "[ OK ] ..."

    tty_init();
    tty_set_color(RGB(255, 255, 255), RGB(0, 0, 0)); // TODO: define colors
	tty_clear(); 
    printk(" %s\n", "kernel: initialized TTY");
    	
    printk("kernel: magic: %#X\n", magic);
    
    if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        printk(" kernel: Invalid magic number: %#X\n", magic);
        return;
    }

    kboot(&boot_info);

    login_init();

    printk("Logged in at %s \n", __TIME__);
    printk("NOS - hobby Unix-like OS (%s)\n \n", __OS_VERSION__);
    printk("%s\n", "The programs included in NOS are free software.\n"
    "The software is provided \"as is\", without warranty of any kind.\n");

    /* initializing kernel shell */
    ksh_init();

    khalt();
}