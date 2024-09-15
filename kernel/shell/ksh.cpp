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

#include <nos/shell/ksh.hpp>
#include <nos/shell/ls.hpp>
#include <nos/keyboard.hpp>
#include <nos/version.hpp>
#include <nos/string.hpp>
#include <nos/printk.hpp>
#include <nos/kernel.hpp>
#include <nos/nosstd.hpp>
#include <nos/stdlib.hpp>
#include <nos/types.hpp>
#include <nos/ctype.hpp>
#include <nos/login.hpp>
#include <nos/tty.hpp>
#include <nos/gfx.hpp>
#include <nos/mm.hpp>


namespace kernel {
namespace shell {

/** @brief Display promt for user input. */
static void ksh_display_prompt(void);

/** @brief Check if user input buffer is empty. */
static bool ksh_is_empty(void);

/**
 * @brief Check shell command is valid.
 * 
 * @param [in] cmd - given builtin command.
 * @param [in] cmd_len - given builtin command string length.
 * @param [in] input - given user input.
 * @param [in] input_len - given user input length.
 * 
 * @return 0 - if command is correct.
 * @return -1 - otherwise.
 */
static s32 ksh_is_valid(const char *cmd, const s32 cmd_len, const char *input,
                        const s32 input_len);

/** @brief Shell commands input buffer. */
static char input_buffer[driver::INPUT_BUFFER_SIZE];

/** @brief Current character position of user input buffer. */
static u32 buf_pos;

gfx::rgb primary_color, secondary_color;

void ksh_init(void)
{
    char cc;

    /* initializing keyboard */
    driver::keyboard_init();

    /* clear user input buffer */
    lib::bzero(input_buffer, sizeof(input_buffer));
    lib::kputchar('\n');

    buf_pos = 0;

    for(;;) {
        ksh_display_prompt();
        
        do {
            cc = (char)driver::keyboard_getchar();

            if(cc != 0 && cc != '\n') {
                
                if (cc == '\b' && buf_pos == 0)
                    continue;

                if (cc == '\b' && buf_pos > 0) {
                    buf_pos--;
                    input_buffer[buf_pos] = 0;
                }
                
                lib::kputchar(cc);

                if(buf_pos < driver::INPUT_BUFFER_SIZE && lib::isprint(cc)) {
                    input_buffer[buf_pos] = cc;
                    buf_pos++;
                }
            }

        } while(cc != '\n');

        input_buffer[buf_pos] = '\0';
        lib::kputchar('\n');
        
        if(!ksh_is_empty())
            ksh_exec(input_buffer);
        
        lib::bzero(input_buffer, sizeof(input_buffer));
        buf_pos = 0;
    }
    
    lib::khalt(); 
}

static s32 ksh_is_valid(const char *cmd, const s32 cmd_len, const char *input, const s32 input_len)
{
    return (cmd_len == input_len) && (lib::strncmp(cmd, input, cmd_len) == 0);
}

s32 ksh_exec(char *cmd)
{
    [[gnu::unused]]s32 cmd_len;

    cmd_len = lib::strlen(cmd);
    
    if(ksh_is_valid("free", 4, cmd, cmd_len))
        ksh_free();
    else if(ksh_is_valid("clear", 5, cmd, cmd_len))
        ksh_clear();
    else if(ksh_is_valid("help", 4, cmd, cmd_len) || ksh_is_valid("?", 1, cmd, cmd_len))
        ksh_help();
    else if(ksh_is_valid("theme", 5, cmd, 5)) {
        char *theme_type;

        theme_type = lib::strtok(cmd, " ");
        theme_type = lib::strtok(nullptr, " ");

        if (theme_type)
            ksh_theme(static_cast<theme_t>(lib::atoi(theme_type)));
        else
            lib::printk(" theme: %s\n", "incorrect argument\n");
    }
    else if(ksh_is_valid("ps", 2, cmd, cmd_len))
        ksh_ps();
    else if(ksh_is_valid("ls", 2, cmd, cmd_len))
        ksh_ls();
    else if(ksh_is_valid("cat", 3, cmd, 3)) {
        char *pathname;

        pathname = lib::strtok(cmd, " ");
        pathname = lib::strtok(nullptr, " ");

        if (pathname)
            ksh_cat(pathname);
        else
            lib::printk("cat: %s\n", "incorrect argument\n");
    }
    else if(ksh_is_valid("gfx", 3, cmd, 3))
        gfx::gfx_test();
    else if(ksh_is_valid("uname", 5, cmd, 5))
        info::__DISPLAY_OS_INFO();
    else if(ksh_is_valid("reboot", 5, cmd, 5))
        ksh_reboot();
    else if(ksh_is_valid("shutdown", 8, cmd, 8))
        ksh_shutdown();
    else {
        ksh_warning((char *)cmd);
        return -1;
    }

    return 0;
}

static void ksh_display_prompt(void)
{
    primary_color   = gfx::tty_get_primary_color();
    secondary_color = gfx::tty_get_secondary_color();

    tty_printc(USERNAME, primary_color, secondary_color);
    lib::kputchar('@');
    tty_printc("nos", primary_color, secondary_color);
    lib::putk(":-/ ");
}

static bool ksh_is_empty(void)
{
    return input_buffer[0] == 0;
}

} // namespace shell
} // namespace kernel