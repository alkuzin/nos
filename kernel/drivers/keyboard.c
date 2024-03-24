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
#include <kernel/ports.h>
#include <libk/stdint.h>
#include <libk/stddef.h>
#include <libk/ctype.h>
#include <kernel/irq.h>
#include <kernel/tty.h>

const uint32_t UNKNOWN = 0xFFFFFFFF;
const uint32_t ESC     = 0xFFFFFFFF - 1;
const uint32_t CTRL    = 0xFFFFFFFF - 2;
const uint32_t LSHFT   = 0xFFFFFFFF - 3;
const uint32_t RSHFT   = 0xFFFFFFFF - 4;
const uint32_t ALT     = 0xFFFFFFFF - 5;
const uint32_t F1      = 0xFFFFFFFF - 6;
const uint32_t F2      = 0xFFFFFFFF - 7;
const uint32_t F3      = 0xFFFFFFFF - 8;
const uint32_t F4      = 0xFFFFFFFF - 9;
const uint32_t F5      = 0xFFFFFFFF - 10;
const uint32_t F6      = 0xFFFFFFFF - 11;
const uint32_t F7      = 0xFFFFFFFF - 12;
const uint32_t F8      = 0xFFFFFFFF - 13;
const uint32_t F9      = 0xFFFFFFFF - 14;
const uint32_t F10     = 0xFFFFFFFF - 15;
const uint32_t F11     = 0xFFFFFFFF - 16;
const uint32_t F12     = 0xFFFFFFFF - 17;
const uint32_t SCRLCK  = 0xFFFFFFFF - 18;
const uint32_t HOME    = 0xFFFFFFFF - 19;

const uint32_t UP      = 0xFFFFFFFF - 20;
const uint32_t LEFT    = 0xFFFFFFFF - 21;
const uint32_t RIGHT   = 0xFFFFFFFF - 22;
const uint32_t DOWN    = 0xFFFFFFFF - 23;

const uint32_t PGUP    = 0xFFFFFFFF - 24;
const uint32_t PGDOWN  = 0xFFFFFFFF - 25;
const uint32_t END     = 0xFFFFFFFF - 26;
const uint32_t INS     = 0xFFFFFFFF - 27;
const uint32_t DEL     = 0xFFFFFFFF - 28;
const uint32_t CAPS    = 0xFFFFFFFF - 29;
const uint32_t NONE    = 0xFFFFFFFF - 30;
const uint32_t ALTGR   = 0xFFFFFFFF - 31;
const uint32_t NUMLCK  = 0xFFFFFFFF - 32;

const uint32_t lowercase[128] = {
UNKNOWN,ESC,'1','2','3','4','5','6','7','8',
'9','0','-','=','\b','\t','q','w','e','r',
't','y','u','i','o','p','[',']','\n',CTRL,
'a','s','d','f','g','h','j','k','l',';',
'\'','`',LSHFT,'\\','z','x','c','v','b','n',
'm',',','.','/',RSHFT,'*',ALT,' ',CAPS,F1,
F2,F3,F4,F5,F6,F7,F8,F9,F10,NUMLCK,
SCRLCK,HOME,UP,PGUP,'-',LEFT,UNKNOWN,RIGHT,'+',END,
DOWN,PGDOWN,INS,DEL,UNKNOWN,UNKNOWN,UNKNOWN,F11,F12,UNKNOWN,
UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
UNKNOWN,UNKNOWN,UNKNOWN 
};

const uint32_t uppercase[128] = {
UNKNOWN,ESC,'!','@','#','$','%','^','&','*',
'(',')','_','+','\b','\t','Q','W','E','R',
'T','Y','U','I','O','P','{','}','\n',CTRL,
'A','S','D','F','G','H','J','K','L',':',
'"','~',LSHFT,'|','Z','X','C','V','B','N',
'M','<','>','?',RSHFT,'*',ALT,' ',CAPS,F1,
F2,F3,F4,F5,F6,F7,F8,F9,F10,NUMLCK,
SCRLCK,HOME,UP,PGUP,'-',LEFT,UNKNOWN,RIGHT,'+',END,
DOWN,PGDOWN,INS,DEL,UNKNOWN,UNKNOWN,UNKNOWN,F11,F12,UNKNOWN,
UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
UNKNOWN,UNKNOWN,UNKNOWN };

bool caps_is_on, caps_lock_is_on;


void keyboard_init(void)
{
    caps_is_on = false;
    caps_lock_is_on = false;

    irq_install_handler(1, &keyboard_handler);
}

void keyboard_handler(__attribute__((unused)) int_reg_t *regs)
{
    /* do nothing */
}

void keyboard_wait(void) {
    while((in_port_b(0x64) & 0x01) == 0);
}

uint8_t keyboard_getchar(void) {
    uint8_t scan_code, press, cc;
    
    keyboard_wait();

    /* get code of key that is pressed */
    scan_code = in_port_b(0x60) & 0x7F;

    /* is key is pressed down or released */
    press = in_port_b(0x60) & 0x80;
    
    switch(scan_code) {    
        case KEY_UP_ARROW:
        case KEY_DOWN_ARROW:
        case KEY_LEFT_ARROW:
        case KEY_RIGHT_ARROW:
        case KEY_LSHFT:
            if(!press)
                caps_is_on = true;
            else
                caps_is_on = false;
            break;

        case KEY_CAPS_LOCK:
            if(!caps_lock_is_on && !press)
                caps_lock_is_on = true;
            else if(caps_lock_is_on && !press)
                caps_lock_is_on = false;
            break;

        default:
            if(!press) {
                if((caps_is_on || caps_lock_is_on) && (lowercase[scan_code] != UNKNOWN))
                    cc = uppercase[scan_code];
                else
                    cc = lowercase[scan_code];

                return cc;
            }
            break;
    }
    return 0;
}
