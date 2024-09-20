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

#include <kernel/drivers/keyboard.hpp>
#include <kernel/kstd/cstring.hpp>
#include <kernel/kstd/cstring.hpp>
#include <kernel/kstd/cstdio.hpp>
#include <kernel/kstd/ctype.hpp>
#include <kernel/terminal.hpp>
#include <kernel/version.hpp>
#include <kernel/login.hpp>


namespace kernel {
namespace login {

void login_init(void)
{
    char password[SUPER_SECURE_PASSWORD_SIZE];
    char login[MAX_USERNAME_SIZE];
    s32  attempts;
    
    tty::clear();
    driver::keyboard::init();

    kstd::printk("%s", LOGIN_BANNER);

    info::display_general_info();
    info::display_build_info();

    tty::kputchar('\n');

    attempts = MAX_ATTEMPTS;

    do {
        kstd::printk("%s", "login: ");
        getinput(login, MAX_USERNAME_SIZE);
        
        if (kstd::strncmp(login, USERNAME, MAX_USERNAME_SIZE) != 0) {
            kstd::printk("nos: %s\n", "incorrect login");
            break;
        }

        kstd::printk("%s", "password: ");
        getinput(password, SUPER_SECURE_PASSWORD_SIZE);
    
        if (kstd::strncmp(password, SUPER_SECURE_PASSWORD, SUPER_SECURE_PASSWORD_SIZE) != 0)
            kstd::printk("nos: %s\n", "incorrect password");
        else
            return;
        
        attempts--;
    } while (attempts > 0);

    login_init();
}

void getinput(char *buffer, u32 size)
{
    char cc;
    u32  i;

    i = 0;

    if (size > driver::keyboard::INPUT_BUFFER_SIZE)
        size = driver::keyboard::INPUT_BUFFER_SIZE;

    do {
        cc = (char)driver::keyboard::getchar();

        if(cc != 0 && cc != '\n') {    
            if (cc == '\b' && i == 0)
                continue;

            if (cc == '\b' && i > 0) {
                i--;
                buffer[i] = 0;
            }
            
            tty::kputchar(cc);

            if(i < size && kstd::isprint(cc)) {
                buffer[i] = cc;
                i++;
            }
        }

    } while(cc != '\n');

    buffer[i] = '\0';
    tty::kputchar('\n');
}
    
} // namespace login
} // namespace kernel
