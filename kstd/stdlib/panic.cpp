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

#include <nos/stdarg.hpp>
#include <nos/nosstd.hpp>
#include <nos/printk.hpp>
#include <nos/panic.hpp>


namespace kernel {
namespace lib {
	
void __panic(const char *file, const char *func, u32 line, const char *fmt, ...)
{
	va_list args;
	
	va_start(args, fmt);
    printk("kernel: panic: in \"%s\" in \"%s()\" at line %d: ", file, func, line);
	vprintk(fmt, args);
    va_end(args);

	khalt();
}

} // namespace lib
} // namespace kernel