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

#include <nos/shell/ksh.h>
#include <nos/keyboard.h>
#include <nos/kernel.h> 
#include <nos/nosstd.h>
#include <nos/types.h>
#include <nos/tty.h>
#include <nos/vga.h>
#include <nos/mm.h>

/* display promt for user input */
static void ksh_display_prompt(void);

/* check if user input buffer is empty */
static bool ksh_is_empty(void);

/* check shell command is valid */
static s32 ksh_is_valid(const char *cmd, const s32 cmd_len, const char *input,
                        const s32 input_len);

/* shell commands input buffer */
static char input_buffer[INPUT_BUFFER_SIZE]; 

/* current character position of user input buffer */
static u32 buf_pos;


void ksh_init(multiboot_t *boot_info)
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
            ksh_exec(boot_info, input_buffer);
        
        bzero(input_buffer, sizeof(input_buffer));
        buf_pos = 0;
    }
    
    khalt(); 
}

static s32 ksh_is_valid(const char *cmd, const s32 cmd_len, const char *input, const s32 input_len)
{
    return (cmd_len == input_len) && (strncmp(cmd, input, cmd_len) == 0);
}

void ksh_exec(multiboot_t *boot_info, const char *cmd)
{
    [[gnu::unused]]s32 cmd_len;

    cmd_len = strlen(cmd);
    
    if(ksh_is_valid("lsmem", 5, cmd, cmd_len))
        ksh_lsmem(boot_info);
    else if(ksh_is_valid("clear", 5, cmd, cmd_len))
        ksh_clear();
    else if(ksh_is_valid("help", 4, cmd, cmd_len))
        ksh_help();
        // TODO: make shell arguments parser
    else if(ksh_is_valid("theme_0", 7, cmd, cmd_len))
        ksh_theme(THEME_DEFAULT);
    else if(ksh_is_valid("theme_1", 7, cmd, cmd_len))
        ksh_theme(THEME_CLASSIC);
    else if(ksh_is_valid("lsproc", 6, cmd, cmd_len))
        ksh_lsproc();
    else if(ksh_is_valid("ls", 2, cmd, cmd_len))
        ksh_ls();
    else
        ksh_warning((char *)cmd);
}

static void ksh_display_prompt(void)
{
    putk(" sh: ");
}

static bool ksh_is_empty(void)
{
    return input_buffer[0] == 0;
}