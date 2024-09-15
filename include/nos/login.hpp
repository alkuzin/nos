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
 * @file  login.hpp
 * @brief Contain kernel login functions.
 *
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   10.06.2024 
 */

#ifndef _NOS_KERNEL_LOGIN_HPP_
#define _NOS_KERNEL_LOGIN_HPP_

#include <nos/types.hpp>


namespace kernel {
namespace login {

#define MAX_ATTEMPTS 3

// TODO: create structure for containing login & password
#define MAX_USERNAME_SIZE 5
#define USERNAME          "alex"

#define SUPER_SECURE_PASSWORD      "12345"
#define SUPER_SECURE_PASSWORD_SIZE 6

#define LOGIN_BANNER "   _  ______  ____ \n" \
                     "  / |/ / __ \\/ __/ \n" \
                     " /    / /_/ /\\ \\   \n" \
                     "/_/|_/\\____/___/   \n" \
                     "----------------------------------\n"

/** @brief Initialize kernel login. */
void login_init(void);

/**
 * @brief Get secure user input. 
 * 
 * @param [out] buffer - given buffer for input.
 * @param [in] size - given max size of input.
 */
void getinput(char *buffer, u32 size);

} // namespace login
} // namespace kernel

#endif /* _NOS_KERNEL_LOGIN_HPP_ */