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

#include <kernel/kstd/cstdlib.hpp>
#include <kernel/arch/x86/io.hpp>
#include <kernel/kstd/cstdio.hpp>
#include <kernel/shell/ksh.hpp>
#include <kernel/fs/initrd.hpp> 
#include <kernel/tty.hpp>
#include <kernel/mm.hpp>


namespace kernel {
namespace shell {

void warning(const char *cmd)
{
    kstd::printk("ksh: %s: command not found \n", cmd);
}

void help(void)
{
    kstd::putk(
         "help, ?      - display information about builtin commands.\n"
         "clear        - clear screen\n"
         "uname        - print system information\n"
         "ls           - display list of files\n"
         "cat          - display file content\n"
         "free         - display list of free memory\n"
         "theme <id>   - set CLI theme\n"
         "ps           - display list of current processes\n"
         "reboot       - reboot OS\n"
         "shutdown     - shutdown OS\n"
         "gfx          - test graphics\n\n"
    );
}

void clear(void)
{
    tty::clear();
}

void free(void)
{
    u32 max_blocks     = core::memory::pmm::get_max_blocks();
    u32 used_blocks    = core::memory::pmm::get_used_blocks();
    u32 phys_mem_total = core::memory::pmm::get_phys_mem_total();
    u32 phys_mem_free  = core::memory::pmm::get_phys_mem_free();
    u32 free_blocks    = max_blocks - used_blocks;
    u32 total_bytes    = max_blocks  * core::memory::pmm::BLOCK_SIZE;
    u32 used_bytes     = used_blocks * core::memory::pmm::BLOCK_SIZE;
    u32 free_bytes     = free_blocks * core::memory::pmm::BLOCK_SIZE;

    kstd::printk("\nMem: \n\t total: %u KB   free: %u KB   used: %u KB\n\n", phys_mem_total >> 10, 
    phys_mem_free >> 10, (phys_mem_total - phys_mem_free) >> 10);
    kstd::putk("Blocks:\n\n");
    kstd::printk("\ttotal: %u (%u KB) (%u MB)\n", max_blocks, total_bytes >> 10, total_bytes >> 20);
    kstd::printk("\tused : %u (%u KB) (%u MB)\n", used_blocks, used_bytes >> 10, used_bytes >> 20);
    kstd::printk("\tfree : %u (%u KB) (%u MB)\n \n", free_blocks, free_bytes >> 10, free_bytes >> 20);
}

void theme(theme_t theme)
{
    gfx::rgb fg, bg, primary_color, secondary_color;

    switch (theme) {

        case theme_t::based:
            fg              = gfx::color::white;
            bg              = gfx::color::black;
            primary_color   = gfx::color::gray;
            secondary_color = gfx::color::black;
            break;
        
        case  theme_t::classic:
            fg              = gfx::color::white;
            bg              = gfx::color::blue;
            primary_color   = gfx::color::white;
            secondary_color = gfx::color::blue;
            break;
        
        case theme_t::green_black:
            fg              = gfx::color::green;
            bg              = gfx::color::black;
            primary_color   = gfx::color::green;
            secondary_color = gfx::color::black;
            break;
        
        case theme_t::brown_black:
            fg              = gfx::color::brown;
            bg              = gfx::color::black;
            primary_color   = gfx::color::brown;
            secondary_color = gfx::color::black;
            break;
        
        case theme_t::purple_black:
            fg              = gfx::color::purple;
            bg              = gfx::color::black;
            primary_color   = gfx::color::purple;
            secondary_color = gfx::color::black;
            break;
    
        default:
            kstd::printk("theme: incorrect theme \"%d\" \nksh: type \"help\""
                   " to see list of available commands\n", theme);
            return;
    }
    
    tty::set_color(fg, bg);
    tty::set_primary_color(primary_color);
    tty::set_secondary_color(secondary_color);
    tty::update();
}

void ps(void)
{
    kstd::putk("comming soon ...\n");
    // sched_t *scheduler;
    // pcb_t   *proc;

    // scheduler = get_sched();

    // puts(" ------------------------------------------\n"
    //      " | pid | pr | ppid | name |   base | size |\n"
    //      " ------------------------------------------");

    // for (s32 i = 0; i < scheduler->rear + 1; i++) {
    //     proc = scheduler->processes[i];
    //     printk("   %u |  %u  |  %u | %s | %#x | %u \n", proc->pid, proc->priority, 
    //     proc->parent_pid, proc->name, proc->base, proc->size);
    // }

    // puts(" ------------------------------------------ ");
    // printk(" \n total processes: %d\n", scheduler->rear + 1);   
}

void readexe(void)
{
    // TODO: exstract exe header from file

    // if (!exe_is_valid(header))
    //     printk(" readexe: not NOS executable file. Incorrect signature: '%s'\n", 
    //     (char *)header->signature);

    // exe_display_info(header);
}

void cat(const char *pathname)
{
    char buffer[fs::initrd::INITRD_FILE_SIZE];
    s32 fd, ret;

    fd = fs::vfs::open(pathname, O_RDONLY);

    if (fd == -1) {
        kstd::printk("cat: error to open file \"%s\"\n", pathname);
        return;
    }

    ret = fs::vfs::read(fd, buffer, fs::initrd::INITRD_FILE_SIZE);

    if (ret == -1)
        kstd::printk("cat: error to read file \"%s\"\n", pathname);
    
    kstd::printk("%s", buffer);

    ret = fs::vfs::close(fd);

    if (ret == -1)
        kstd::printk("cat: error to close file \"%s\"\n", pathname);
}

void reboot(void)
{
    arch::x86::outb(0x64, 0xFE);
}

void shutdown(void)
{
    arch::x86::outw(0xB004, 0x2000);
    arch::x86::outw(0x0604, 0x2000);
    arch::x86::outw(0x4004, 0x3400);
}
        
} // namespace shell
} // namespace kernel