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

/**
 * @file  ls.hpp
 * @brief Contain kernel shell Unix-like ls implementation.
 *
 * @details This header file contain ls auxilary functions.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   10.06.2024 
 */

#ifndef _KERNEL_SHELL_LS_HPP_
#define _KERNEL_SHELL_LS_HPP_

#include <kernel/fs/initrd.hpp>


namespace kernel {
namespace shell {

/** @brief Ls file structure.*/
struct ls_file {
    fs::stat_t stat;
    char       mode[12];
};

/** @brief Ls structure.*/
struct ls_t {
    char    dirname[fs::initrd::INITRD_MAX_NAME_SIZE];
    ls_file files[fs::initrd::INITRD_MAX_FILES];
    u32     count;
};

/** @brief Display list of files.*/
void ls(void);
    
} // namespace shell
} // namespace kernel

#endif // _KERNEL_SHELL_LS_HPP_