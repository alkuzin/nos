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

#ifndef _NOS_KERNEL_SHELL_HPP_
#define _NOS_KERNEL_SHELL_HPP_

#include <nos/multiboot.hpp>
#include <nos/types.hpp>


namespace kernel {
namespace shell {

/** @brief Enumeration of builtin CLI themes. */
typedef enum {
    THEME_DEFAULT,
    THEME_CLASSIC,
    THEME_GREEN_BLACK,
    THEME_BROWN_BLACK,
    THEME_PURPLE_BLACK
} theme_t;

/** @brief Initialize kernel shell. */
void ksh_init(void);

/**
 * @brief Execute builtin shell commands.
 * 
 * @param [in] cmd - given shell command string.
 * @return 0 - in case of success.
 * @return -1 - in case of error.
 */
s32 ksh_exec(char *cmd);

/**
 * @brief print shell warning in case of incorrect command.
 * 
 * @param [in] cmd - given shell command string.
 */
void ksh_warning(const char *cmd);

/** @brief Clear terminal. */
void ksh_clear(void);

/** @brief Display list of free memory. */
void ksh_free(void);

/** @brief Display list of available shell commands. */
void ksh_help(void);

/**
 * @brief Change CLI theme.
 * 
 * @param [in] theme - given theme type.
 */
void ksh_theme(theme_t theme);

/** @brief Display list of current processes. */
void ksh_ps(void);

/** @brief Display executable information. */
void ksh_readexe(void);

/**
 * @brief Read file. 
 * 
 * @param [in] pathname - given file path.
 */
void ksh_cat(const char *pathname);

/** @brief Reboot OS. */
void ksh_reboot(void);

/** @brief Shutdown OS. */
void ksh_shutdown(void);

} // namespace shell
} // namespace kernel

#endif /* _NOS_KERNEL_SHELL_HPP_ */