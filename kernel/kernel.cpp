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

// drivers
#include <kernel/drivers/keyboard.hpp>
#include <kernel/drivers/timer.hpp>
#include <kernel/drivers/vbe.hpp>

// x86 architecture
#include <kernel/arch/x86/gdt.hpp>
#include <kernel/arch/x86/idt.hpp>

// kernel standard library
#include <kernel/kstd/cstdlib.hpp>
#include <kernel/kstd/cstdio.hpp>
#include <kernel/shell/ksh.hpp>

// filesystem
#include <kernel/fs/initrd.hpp>
#include <kernel/fs/stat.hpp>
#include <kernel/fs/vfs.hpp>

// core
#include <kernel/version.hpp>
#include <kernel/kernel.hpp>
#include <kernel/login.hpp>
#include <kernel/tty.hpp>
#include <kernel/mm.hpp>


namespace kernel {
namespace core {

static void test_initrd(void)
{
    s32 fd;
    const char *author_content = " \nAuthor: Alexander (@alkuzin) \n"
                           "GitHub: https://github.com/alkuzin \n";    

    fs::vfs::creat("AUTHOR", S_IFREG | S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
    fs::vfs::creat("hw.txt", S_IFREG | S_IRUSR | S_IWUSR);
    
    fd = fs::vfs::open("AUTHOR", O_RDWR);
    fs::vfs::write(fd, const_cast<char*>(author_content), 69);
    fs::vfs::close(fd);
    
    fd = fs::vfs::open("hw.txt", O_RDWR);
    fs::vfs::write(fd, const_cast<char*>("Hello, World!\n"), 15);
    fs::vfs::close(fd);
}

void kboot(u32 magic, const multiboot_t& mboot)
{
    driver::vbe::init(mboot);
    tty::init();

    tty::set_color(gfx::color::white, gfx::color::black);
    tty::set_primary_color(gfx::color::gray);
    tty::set_secondary_color(gfx::color::black);
	tty::clear(); 

    kstd::kmesg(true, "%s\n", "initialized VBE mode");
    kstd::kmesg(true, "%s\n", "initialized TTY");
    	
    if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        kstd::kmesg(false, "Invalid magic number: %#X\n", magic);
        return;
    }
    
    // initializing Global Descriptor Table
    arch::x86::gdt_init();
    kstd::kmesg(true, "%s\n", "initialized Global Descriptor Table");
    
    // initializing Interrupt Descriptor Table
    arch::x86::idt_init();
    kstd::kmesg(true, "%s\n", "initialized Interrupt Descriptor Table");	
    
    // initializing timer
    driver::timer::init();
    kstd::kmesg(true, "%s\n", "initialized timer");	

    // initializing memory management
    memory::init(mboot);
    kstd::kmesg(true, "%s\n", "initialized memory management");

    // initializing initial ramdisk
    fs::initrd::init();
    kstd::kmesg(true, "%s\n", "initialized initial ramdisk");

    // initializing Virtual File System
    fs::vfs::fs_adapter *initrd_adapter = fs::initrd::get_adapter();

    fs::vfs::init(fs::vfs::fs_type::INITRD, initrd_adapter);
    kstd::kmesg(true, "%s\n", "initialized Virtual File System");

    test_initrd();

    // Disabled for debugging
    // login::init();

    kstd::printk("\n\nLogged in at %s \n", __TIME__);
    info::display_general_info();
    kstd::printk("%s\n", "The programs included in NOS are free software.\n"
    "The software is provided \"as is\", without warranty of any kind.\n");

    // initializing kernel shell
    shell::init();
}

} // namespace core
} // namespace kernel

extern "C" void kmain(kernel::u32 magic, multiboot_t *mboot)
{
    multiboot_t boot_info = *mboot;
    
    kernel::core::kboot(magic, boot_info);
    kernel::kstd::khalt();
}