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
#include <kernel/kstd/cstdlib.hpp>
#include <kernel/kstd/cstdio.hpp>
#include <kernel/kstd/ctype.hpp>
#include <kernel/shell/ksh.hpp>
#include <kernel/shell/ls.hpp>
#include <kernel/version.hpp>
#include <kernel/kernel.hpp>
#include <kernel/login.hpp>
#include <kernel/tty.hpp>
#include <kernel/mm.hpp>


namespace kernel {
namespace shell {

static gfx::rgb primary_color, secondary_color;

/** @brief Display promt for user input. */
static constexpr inline void display_prompt(void) noexcept
{
    primary_color   = tty::get_primary_color();
    secondary_color = tty::get_secondary_color();

    tty::printc(USERNAME, primary_color, secondary_color);
    tty::kputchar('@');
    tty::printc("nos", primary_color, secondary_color);
    kstd::putk(":-/ ");
}

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
static inline s32 is_valid(const char *cmd, const s32 cmd_len, const char *input, const s32 input_len) noexcept
{
    return (cmd_len == input_len) && (kstd::strncmp(cmd, input, cmd_len) == 0);
}


void init(void)
{
    char input_buffer[driver::keyboard::INPUT_BUFFER_SIZE];
    u32  buf_pos = 0;
    char cc;

    // initializing keyboard
    driver::keyboard::init();

    // clear user input buffer
    kstd::bzero(input_buffer, sizeof(input_buffer));
    tty::kputchar('\n');

    for(;;) {
        display_prompt();
        
        do {
            cc = static_cast<char>(driver::keyboard::getchar());

            if(cc != 0 && cc != '\n') {

                if (cc == '\b' && buf_pos == 0)
                    continue;
                    
                if (cc == '\b' && buf_pos > 1) {
                    buf_pos--;
                    input_buffer[buf_pos] = 0;
                }
            
                tty::kputchar(cc);

                if(buf_pos < driver::keyboard::INPUT_BUFFER_SIZE && kstd::isprint(cc)) {
                    input_buffer[buf_pos] = cc;
                    buf_pos++;
                }
            }

        } while(cc != '\n');

        input_buffer[buf_pos] = '\0';
        tty::kputchar('\n');

        if(input_buffer[0])
            exec(input_buffer);

        kstd::bzero(input_buffer, sizeof(input_buffer));
        buf_pos = 0;
    }
    
    kstd::khalt(); 
}

s32 exec(char *cmd)
{
    [[gnu::unused]]s32 cmd_len = kstd::strlen(cmd);
    
    if(is_valid("free", 4, cmd, cmd_len))
        free();
    else if(is_valid("clear", 5, cmd, cmd_len))
        clear();
    else if(is_valid("help", 4, cmd, cmd_len) || is_valid("?", 1, cmd, cmd_len))
        help();
    else if(is_valid("theme", 5, cmd, 5)) {
        char *theme_type;

        theme_type = kstd::strtok(cmd, " ");
        theme_type = kstd::strtok(nullptr, " ");

        if (theme_type)
            theme(static_cast<theme_t>(kstd::atoi(theme_type)));
        else
            kstd::printk(" theme: %s\n", "incorrect argument\n");
    }
    else if(is_valid("ps", 2, cmd, cmd_len))
        ps();
    else if(is_valid("ls", 2, cmd, cmd_len))
        ls();
    else if(is_valid("cat", 3, cmd, 3)) {
        char *pathname;

        pathname = kstd::strtok(cmd, " ");
        pathname = kstd::strtok(nullptr, " ");

        if (pathname)
            cat(pathname);
        else
            kstd::printk("cat: %s\n", "incorrect argument\n");
    }
    else if(is_valid("gfx", 3, cmd, 3))
        gfx::test();
    else if(is_valid("uname", 5, cmd, 5))
        info::display_general_info();
    else if(is_valid("reboot", 5, cmd, 5))
        reboot();
    else if(is_valid("shutdown", 8, cmd, 8))
        shutdown();
    else {
        warning(cmd);
        return -1;
    }

    return 0;
}

} // namespace shell
} // namespace kernel