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
#include <stdio.h>
#include <stdlib.h>

#include <nos/shell/ksh.h>
#include <nos/shell/ls.h>
#include <nos/keyboard.h>
#include <nos/kernel.h> 
#include <nos/nosstd.h>
#include <nos/types.h>
#include <nos/tty.h>
#include <nos/vga.h>
#include <nos/gfx.h>
#include <nos/mm.h>

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
static char input_buffer[INPUT_BUFFER_SIZE];

/** @brief Current character position of user input buffer. */
static u32 buf_pos;

rgb_t primary_color, secondary_color;

void ksh_init(void)
{
    char cc;

    /* initializing keyboard */
    keyboard_init();

    /* clear user input buffer */
    bzero(input_buffer, sizeof(input_buffer));
    kputchar('\n');

    buf_pos = 0;

    for(;;) {
        ksh_display_prompt();
        
        do {
            cc = (char)keyboard_getchar();

            if(cc != 0 && cc != '\n') {
                
                if (cc == '\b' && buf_pos == 0)
                    continue;

                if (cc == '\b' && buf_pos > 0) {
                    buf_pos--;
                    input_buffer[buf_pos] = 0;
                }
                
                kputchar(cc);

                if(buf_pos < INPUT_BUFFER_SIZE && isprint(cc)) {
                    input_buffer[buf_pos] = cc;
                    buf_pos++;
                }
            }

        } while(cc != '\n');

        input_buffer[buf_pos] = '\0';
        kputchar('\n');
        
        if(!ksh_is_empty())
            ksh_exec(input_buffer);
        
        bzero(input_buffer, sizeof(input_buffer));
        buf_pos = 0;
    }
    
    khalt(); 
}

static s32 ksh_is_valid(const char *cmd, const s32 cmd_len, const char *input, const s32 input_len)
{
    return (cmd_len == input_len) && (strncmp(cmd, input, cmd_len) == 0);
}

s32 ksh_exec(char *cmd)
{
    [[gnu::unused]]s32 cmd_len;

    cmd_len = strlen(cmd);
    
    if(ksh_is_valid("lsmem", 5, cmd, cmd_len))
        ksh_lsmem();
    else if(ksh_is_valid("clear", 5, cmd, cmd_len))
        ksh_clear();
    else if(ksh_is_valid("help", 4, cmd, cmd_len))
        ksh_help();
    else if(ksh_is_valid("theme", 5, cmd, 5)) {
        char *theme_type;

        theme_type = strtok(cmd, " ");
        theme_type = strtok(nullptr, " ");

        if (theme_type)
            ksh_theme(atoi(theme_type));
        else
            printk(" theme: %s\n", "incorrect argument\n");
    }
    else if(ksh_is_valid("lsproc", 6, cmd, cmd_len))
        ksh_lsproc();
    else if(ksh_is_valid("ls", 2, cmd, cmd_len))
        ksh_ls();
    else if(ksh_is_valid("cat", 3, cmd, 3)) {
        char *pathname;

        pathname = strtok(cmd, " ");
        pathname = strtok(nullptr, " ");

        if (pathname)
            ksh_cat(pathname);
        else
            printk("cat: %s\n", "incorrect argument\n");
    }
    else if(ksh_is_valid("gfx", 3, cmd, 3)) {
        gfx_test();
    }
    else {
        ksh_warning((char *)cmd);
        return -1;
    }

    return 0;
}

static void ksh_display_prompt(void)
{
    // TODO: handle different themes.
    primary_color   = tty_get_primary_color();
    secondary_color = tty_get_secondary_color();

    tty_printc(USERNAME, primary_color, secondary_color);
    kputchar('@');
    tty_printc("nos", primary_color, secondary_color);
    putk(":-/ ");
}

static bool ksh_is_empty(void)
{
    return input_buffer[0] == 0;
}