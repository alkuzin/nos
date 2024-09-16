/**
 * The Null Operating System (NOS).
 * Copyright (C) 2024  Alexander (@alkuzin).
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <nos/shell/ksh.hpp>
#include <nos/keyboard.hpp>
#include <nos/version.hpp>
#include <nos/nosstd.hpp>
#include <nos/initrd.hpp>
#include <nos/kernel.hpp>
#include <nos/printk.hpp>
#include <nos/timer.hpp>
#include <nos/login.hpp>
#include <nos/panic.hpp>
#include <nos/tty.hpp>
#include <nos/gdt.hpp>
#include <nos/idt.hpp>
#include <nos/vfs.hpp>
#include <nos/vbe.hpp>
#include <nos/gfx.hpp>
#include <nos/mm.hpp>


namespace kernel {
namespace core {

static void test_initrd(void)
{
    s32 fd;
    const char *author_content = " \nAuthor: Alexander (@alkuzin) \n"
                           "GitHub: https://github.com/alkuzin \n";    

    kernel::fs::vfs_creat("AUTHOR", S_IFREG | S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
    kernel::fs::vfs_creat("hw.txt", S_IFREG | S_IRUSR | S_IWUSR);
    
    fd = kernel::fs::vfs_open("AUTHOR", O_RDWR);
    kernel::fs::vfs_write(fd, const_cast<char*>(author_content), 69);
    kernel::fs::vfs_close(fd);
    
    fd = kernel::fs::vfs_open("hw.txt", O_RDWR);
    kernel::fs::vfs_write(fd, const_cast<char*>("Hello, World!\n"), 15);
    kernel::fs::vfs_close(fd);
}

void kboot(multiboot_t *mboot)
{
    /* initializing Global Descriptor Table */
    gdt_init();
    lib::kmesg(true, "%s\n", "initialized Global Descriptor Table");
    
    /* initializing Interrupt Descriptor Table */
    idt_init();
    lib::kmesg(true, "%s\n", "initialized Interrupt Descriptor Table");	
    
    /* initializing timer */
    driver::timer_init();
    lib::kmesg(true, "%s\n", "initialized timer");	

    /* initializing memory management */
    memory::memory_init(mboot);
    lib::kmesg(true, "%s\n", "initialized memory management");

    /* initializing initial ramdisk */
    fs::initrd_init();
    lib::kmesg(true, "%s\n", "initialized initial ramdisk");

    /* initializing Virtual File System */
    fs::vfs_adapter_t *initrd_adapter = fs::initrd_get_adapter();

    fs::vfs_init(fs_type_t::INITRD, initrd_adapter);
    lib::kmesg(true, "%s\n", "initialized Virtual File System");

    test_initrd();
}

} // namespace core
} // namespace kernel

extern "C" void kmain(kernel::u32 magic, multiboot_t *mboot)
{
    multiboot_t boot_info = *mboot;
    
    kernel::driver::vbe_init(&boot_info);
    kernel::gfx::tty_init();

    kernel::gfx::tty_set_color(kernel::gfx::color::white, kernel::gfx::color::black);
    kernel::gfx::tty_set_primary_color(kernel::gfx::color::gray);
    kernel::gfx::tty_set_secondary_color(kernel::gfx::color::black);
	kernel::gfx::tty_clear(); 

    kernel::lib::kmesg(true, "%s\n", "initialized VBE mode");
    kernel::lib::kmesg(true, "%s\n", "initialized TTY");
    	
    if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        kernel::lib::kmesg(false, "Invalid magic number: %#X\n", magic);
        return;
    }

    kernel::core::kboot(&boot_info);
    kernel::login::login_init();

    kernel::lib::printk("\n\nLogged in at %s \n", __TIME__);
    kernel::info::display_general_info();
    kernel::lib::printk("%s\n", "The programs included in NOS are free software.\n"
    "The software is provided \"as is\", without warranty of any kind.\n");

    /* initializing kernel shell */
    kernel::shell::ksh_init();
    kernel::lib::khalt();
}