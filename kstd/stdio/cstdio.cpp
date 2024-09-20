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
#include <kernel/kstd/cstdio.hpp>
#include <kernel/terminal.hpp>


namespace kernel {
namespace kstd {

static constexpr u32 BUF_SIZE {1024};
static char buf[BUF_SIZE];


void vprintk(const char *fmt, va_list args)
{
    va_list args_copy;

    va_copy(args_copy, args);
    vsnprintk(buf, BUF_SIZE, fmt, args);
    va_end(args_copy);

	putk(buf);
}

void printk(const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    vsnprintk(buf, BUF_SIZE, fmt, args);
    va_end(args);

    putk(buf);
}

void putk(const char *str)
{
    u32 i = 0;

    while(str[i]) {
        kstd::kputchar(str[i]);       
        i++;
	}
}

void putk(const char *str, gfx::rgb fg, gfx::rgb bg)
{
	s32 i = 0;

    while (str[i]) {
        tty::terminal.put_c(str[i], fg, bg);
		i++;
	}
}
	
void __panic(const char *file, const char *func, u32 line, const char *fmt, ...)
{
	va_list args;
	
	va_start(args, fmt);
    printk("kernel: panic: in \"%s\" in \"%s()\" at line %d: ", file, func, line);
	vprintk(fmt, args);
    va_end(args);

	khalt();
}

void printc(const char *str, gfx::rgb fg, gfx::rgb bg)
{
    u32 i = 0;

    while(str[i]) {
        tty::terminal.put_c(str[i], fg, bg);
        i++;
	}
}

void kputchar(const s32 c)
{
	tty::terminal.put_c(c, tty::terminal.fg(), tty::terminal.bg());
}

} // namespace kstd
} // namespace kernel