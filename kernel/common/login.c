/* MIT License
 *
 * Copyright (c) 2024 Alexander (@alkuzin)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. */

#include <string.h>
#include <ctype.h>

#include <nos/keyboard.h>
#include <nos/kernel.h>
#include <nos/nosstd.h>
#include <nos/login.h>
#include <nos/tty.h>


void login_init(void)
{
    char password[SUPER_SECURE_PASSWORD_SIZE];
    char login[MAX_USERNAME_SIZE];
    s32  attempts;
    
    tty_clear();
    keyboard_init();

    printk("%s", LOGIN_BANNER);

    __DISPLAY_OS_INFO();
    __DISPLAY_OS_BUILD_INFO();

    kputchar('\n');

    attempts = MAX_ATTEMPTS;

    do {
        printk("%s", "login: ");
        getinput(login, MAX_USERNAME_SIZE);
        
        if (strncmp(login, USERNAME, MAX_USERNAME_SIZE) != 0) {
            printk("nos: %s\n", "incorrect login");
            break;
        }

        printk("%s", "password: ");
        getinput(password, SUPER_SECURE_PASSWORD_SIZE);
    
        if (strncmp(password, SUPER_SECURE_PASSWORD, SUPER_SECURE_PASSWORD_SIZE) != 0)
            printk("nos: %s\n", "incorrect password");
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

    if (size > INPUT_BUFFER_SIZE)
        size = INPUT_BUFFER_SIZE;

    do {
        cc = (char)keyboard_getchar();

        if(cc != 0 && cc != '\n') {    
            if (cc == '\b' && i == 0)
                continue;

            if (cc == '\b' && i > 0) {
                i--;
                buffer[i] = 0;
            }
            
            kputchar(cc);

            if(i < size && isprint(cc)) {
                buffer[i] = cc;
                i++;
            }
        }

    } while(cc != '\n');

    buffer[i] = '\0';
    kputchar('\n');
}