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
 * @file  ksh.hpp
 * @brief Contain kernel shell functions.
 *
 * @details This header file contain main kernel shell functions
 * and builtin commands.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   15.05.2024 
 */

#ifndef _KERNEL_SHELL_SHELL_HPP_
#define _KERNEL_SHELL_SHELL_HPP_

#include <kernel/kstd/types.hpp>
#include <kernel/multiboot.hpp>


namespace kernel {
namespace shell {

/** @brief Enumeration of builtin CLI themes. */
enum class theme_t {
    based,
    classic,
    green_black,
    brown_black,
    purple_black
};

/** @brief Initialize kernel shell. */
void init(void);

/**
 * @brief Execute builtin shell commands.
 * 
 * @param [in] cmd - given shell command string.
 * @return 0 - in case of success.
 * @return -1 - in case of error.
 */
s32 exec(char *cmd);

/**
 * @brief print shell warning in case of incorrect command.
 * 
 * @param [in] cmd - given shell command string.
 */
void warning(const char *cmd);

/** @brief Clear terminal. */
void clear(void);

/** @brief Display list of free memory. */
void free(void);

/** @brief Display list of available shell commands. */
void help(void);

/**
 * @brief Change CLI theme.
 * 
 * @param [in] theme - given theme type.
 */
void theme(theme_t theme);

/** @brief Display list of current processes. */
void ps(void);

/** @brief Display executable information. */
void readexe(void);

/**
 * @brief Read file. 
 * 
 * @param [in] pathname - given file path.
 */
void cat(const char *pathname);

/** @brief Reboot OS. */
void reboot(void);

/** @brief Shutdown OS. */
void shutdown(void);

} // namespace shell
} // namespace kernel

#endif // _KERNEL_SHELL_SHELL_HPP_