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

#include <nos/keyboard.hpp>
#include <arch/x86/io.hpp>
#include <nos/ctype.hpp>


namespace kernel {
namespace driver {
    
const u32 UNKNOWN = 0xFFFFFFFF;
const u32 ESC     = 0xFFFFFFFF - 1;
const u32 CTRL    = 0xFFFFFFFF - 2;
const u32 LSHFT   = 0xFFFFFFFF - 3;
const u32 RSHFT   = 0xFFFFFFFF - 4;
const u32 ALT     = 0xFFFFFFFF - 5;
const u32 F1      = 0xFFFFFFFF - 6;
const u32 F2      = 0xFFFFFFFF - 7;
const u32 F3      = 0xFFFFFFFF - 8;
const u32 F4      = 0xFFFFFFFF - 9;
const u32 F5      = 0xFFFFFFFF - 10;
const u32 F6      = 0xFFFFFFFF - 11;
const u32 F7      = 0xFFFFFFFF - 12;
const u32 F8      = 0xFFFFFFFF - 13;
const u32 F9      = 0xFFFFFFFF - 14;
const u32 F10     = 0xFFFFFFFF - 15;
const u32 F11     = 0xFFFFFFFF - 16;
const u32 F12     = 0xFFFFFFFF - 17;
const u32 SCRLCK  = 0xFFFFFFFF - 18;
const u32 HOME    = 0xFFFFFFFF - 19;

const u32 UP      = 0xFFFFFFFF - 20;
const u32 LEFT    = 0xFFFFFFFF - 21;
const u32 RIGHT   = 0xFFFFFFFF - 22;
const u32 DOWN    = 0xFFFFFFFF - 23;

const u32 PGUP    = 0xFFFFFFFF - 24;
const u32 PGDOWN  = 0xFFFFFFFF - 25;
const u32 END     = 0xFFFFFFFF - 26;
const u32 INS     = 0xFFFFFFFF - 27;
const u32 DEL     = 0xFFFFFFFF - 28;
const u32 CAPS    = 0xFFFFFFFF - 29;
const u32 NONE    = 0xFFFFFFFF - 30;
const u32 ALTGR   = 0xFFFFFFFF - 31;
const u32 NUMLCK  = 0xFFFFFFFF - 32;

const u32 lowercase[128] = {
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

const u32 uppercase[128] = {
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
    caps_is_on      = false;
    caps_lock_is_on = false;

    irq_install_handler(1, &keyboard_handler);
}

void keyboard_handler([[gnu::unused]] arch::x86::int_reg_t *regs)
{
    /* do nothing */
}

void keyboard_wait(void)
{
    while((arch::x86::inb(0x64) & 0x01) == 0);
}

u8 keyboard_getchar(void)
{
    u8 scan_code, press, cc;
    
    keyboard_wait();

    /* get code of key that is pressed */
    scan_code = arch::x86::inb(0x60) & 0x7F;

    /* is key is pressed down or released */
    press = arch::x86::inb(0x60) & 0x80;
    
    switch(static_cast<KEY>(scan_code)) {    
        case KEY::UP_ARROW:
        case KEY::DOWN_ARROW:
        case KEY::LEFT_ARROW:
        case KEY::RIGHT_ARROW:
        case KEY::LSHFT:
            if(!press)
                caps_is_on = true;
            else
                caps_is_on = false;
            break;

        case KEY::CAPS_LOCK:
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

} // namespace driver
} // namespace kernel