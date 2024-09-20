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

#include <kernel/klog.hpp>
#include <kernel/tty.hpp>


namespace kernel {
namespace log {

void success(const char *fmt, ...) noexcept
{
    va_list args;
    va_start(args, fmt);
    klog(kmessage::success, fmt, args);
    va_end(args);
}

void debug(const char *fmt, ...) noexcept
{
    va_list args;
    va_start(args, fmt);
    klog(kmessage::debug, fmt, args);
    va_end(args);
}

void error(const char *fmt, ...) noexcept
{
    va_list args;
    va_start(args, fmt);
    klog(kmessage::error, fmt, args);
    va_end(args);
}

void klog(kmessage type, const char *fmt, va_list args) noexcept
{
    tty::kputchar('[');

    switch (type) {
    case kmessage::success:
        kstd::putk("  OK   ", gfx::color::green, tty::get_bg());
        break;
    
    case kmessage::error:
        kstd::putk("  ERR  ", gfx::color::red, tty::get_bg());
        break;
    
    case kmessage::debug:
        kstd::putk(" DEBUG ", gfx::color::gray, tty::get_bg());
        break;
    
    default:
        break;
    }
    
    tty::kputchar(']');
    tty::kputchar(' ');

    va_list args_copy;
    va_copy(args_copy, args);
    kstd::vprintk(fmt, args);
    va_end(args_copy);
}

} // namespace log
} // namespace kernel