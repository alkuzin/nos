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


extern "C" void __cxa_construct(void *obj, void *type_info)
{
    (void)obj;
    (void)type_info;
}

extern "C" void __cxa_desstruct(void *obj, void *type_info)
{
    (void)obj;
    (void)type_info;
}

extern "C" void *__cxa_new(kernel::usize size)
{
    return kernel::kstd::kmalloc(size);
}

extern "C" void __cxa_delete(void *ptr, void (*destructor)(void*))
{
    if (ptr) {
        if (destructor)
            destructor(ptr);
        
        kernel::kstd::kfree(ptr);
    }
}

void *operator new(kernel::u32 size)
{
    return kernel::kstd::kmalloc(size);
}

void operator delete(void *ptr, kernel::u32 size)
{
    if (ptr)
        kernel::kstd::kfree(ptr);

    (void)size;
}

void operator delete(void *ptr)
{
    if (ptr)
        kernel::kstd::kfree(ptr);
}