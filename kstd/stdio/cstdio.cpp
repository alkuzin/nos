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


namespace kernel {
namespace kstd {

static constexpr u32 BUF_SIZE {1024};
static char buf[BUF_SIZE];


void vprintk(const char *fmt, va_list args) noexcept
{
    va_list args_copy;

    va_copy(args_copy, args);
    vsnprintk(buf, BUF_SIZE, fmt, args);
    va_end(args_copy);

	putk(buf);
}

void printk(const char *fmt, ...) noexcept
{
    va_list args;

    va_start(args, fmt);
    vsnprintk(buf, BUF_SIZE, fmt, args);
    va_end(args);

    putk(buf);
}

void putk(const char *str) noexcept
{
    u32 i = 0;

    while(str[i]) {
        kstd::kputchar(str[i]);       
        i++;
	}
}

void putk(const char *str, gfx::rgb fg, gfx::rgb bg) noexcept
{
	s32 i = 0;

    while (str[i]) {
        tty::terminal.put_c(str[i], fg, bg);
		i++;
	}
}
	
void __panic(const char *file, const char *func, u32 line, const char *fmt, ...) noexcept
{
	va_list args;
	
	va_start(args, fmt);
    printk("kernel: panic: in \"%s\" in \"%s()\" at line %d: ", file, func, line);
	vprintk(fmt, args);
    va_end(args);

	khalt();
}

void printc(const char *str, gfx::rgb fg, gfx::rgb bg) noexcept
{
    u32 i = 0;

    while(str[i]) {
        tty::terminal.put_c(str[i], fg, bg);
        i++;
	}
}

} // namespace kstd
} // namespace kernel