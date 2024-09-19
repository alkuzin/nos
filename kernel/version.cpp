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

#include <kernel/version.hpp>


namespace kernel {
namespace info {

const char *__os_name__               {"NOS"};
const char *__os_arch__               {"x86_32"};
const char *__os_author__             {"@alkuzin"};
const char *__os_build_date__         {__DATE__};
const char *__os_build_time__         {__TIME__};
const char *__os_compiler_version__   {__VERSION__};
const u32   __os_version_major__      {0};
const u32   __os_version_minor__      {3};
const u32   __os_version_lower__      {0};

} // namespace info
} // namespace kernel