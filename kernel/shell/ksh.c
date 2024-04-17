/*
MIT License

Copyright (c) 2024 Alexander (@alkuzin)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <kernel/keyboard.h>
#include <kernel/kernel.h> 
#include <kernel/sstd.h> 
#include <libk/stdlib.h>
#include <libk/stddef.h>
#include <libk/stdint.h>
#include <libk/string.h>
#include <libk/memory.h>
#include <kernel/tty.h>
#include <kernel/vga.h>
#include <kernel/mm.h>
#include <shell/ksh.h>

static char input_buffer[INPUT_BUFFER_SIZE]; /* user input buffer */
static uint32_t buf_pos = 0; /* user input buffer current character position */

void __display_help(void);

void ksh_init(multiboot_t *boot_info)
{
    char cc;

    /* initializing keyboard */
    keyboard_init();

    /* clear user input buffer */
    bzero(input_buffer, sizeof(input_buffer));
    kputchar('\n');

    for(;;) {
        ksh_display_prompt();
        
        do {
            cc = (char)keyboard_getchar();
            if(cc != 0 && cc != '\n') {
                kputchar(cc);
                if(buf_pos < INPUT_BUFFER_SIZE) {
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

void ksh_exec(multiboot_t *boot_info, const char *cmd)
{
    int cmd_length;

    cmd_length = strlen(cmd);
    
    if(strncmp(cmd, "lsmem", 5) == 0 && cmd_length == 5)
        __display_memory(boot_info);
    else if(strncmp(cmd, "clear", 5) == 0 && cmd_length == 5) {
        __kclear();

        __tty_set_x(0);
        __tty_set_y(0);
        update_cursor(0, 0);
    }
    else if(strncmp(cmd, "help", 4) == 0 && cmd_length == 4)
        __display_help();
    else {
        kprintf(" ksh: incorrect command \"%s\"\n", (char *)cmd);
        kprint(" ksh: type \"help\" to see list of available commands\n");
    }
}

void ksh_display_prompt(void) {
    kprint(" <simple-os>-$ ");
}

bool ksh_is_empty(void) {
    return input_buffer[0] == 0;
}

void __display_help(void)
{
    kprint("----------------------< help >------------------------\n \n"
           "\thelp         - display this help menu\n \n"
           "\tclear        - clear screen\n \n"
           "\tlsmem        - display list of memory segments\n \n"
           "------------------------------------------------------\n");
}
