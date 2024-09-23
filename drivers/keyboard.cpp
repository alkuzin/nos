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
#include <kernel/arch/x86/irq.hpp>
#include <kernel/arch/x86/io.hpp>
#include <kernel/kstd/ctype.hpp>
#include <kernel/klog.hpp>


namespace kernel {
namespace driver {

constexpr u32 UNKNOWN = 0xFFFFFFFF;
constexpr u32 ESC     = 0xFFFFFFFF - 1;
constexpr u32 CTRL    = 0xFFFFFFFF - 2;
constexpr u32 LSHFT   = 0xFFFFFFFF - 3;
constexpr u32 RSHFT   = 0xFFFFFFFF - 4;
constexpr u32 ALT     = 0xFFFFFFFF - 5;
constexpr u32 F1      = 0xFFFFFFFF - 6;
constexpr u32 F2      = 0xFFFFFFFF - 7;
constexpr u32 F3      = 0xFFFFFFFF - 8;
constexpr u32 F4      = 0xFFFFFFFF - 9;
constexpr u32 F5      = 0xFFFFFFFF - 10;
constexpr u32 F6      = 0xFFFFFFFF - 11;
constexpr u32 F7      = 0xFFFFFFFF - 12;
constexpr u32 F8      = 0xFFFFFFFF - 13;
constexpr u32 F9      = 0xFFFFFFFF - 14;
constexpr u32 F10     = 0xFFFFFFFF - 15;
constexpr u32 F11     = 0xFFFFFFFF - 16;
constexpr u32 F12     = 0xFFFFFFFF - 17;
constexpr u32 SCRLCK  = 0xFFFFFFFF - 18;
constexpr u32 HOME    = 0xFFFFFFFF - 19;

constexpr u32 UP      = 0xFFFFFFFF - 20;
constexpr u32 LEFT    = 0xFFFFFFFF - 21;
constexpr u32 RIGHT   = 0xFFFFFFFF - 22;
constexpr u32 DOWN    = 0xFFFFFFFF - 23;

constexpr u32 PGUP    = 0xFFFFFFFF - 24;
constexpr u32 PGDOWN  = 0xFFFFFFFF - 25;
constexpr u32 END     = 0xFFFFFFFF - 26;
constexpr u32 INS     = 0xFFFFFFFF - 27;
constexpr u32 DEL     = 0xFFFFFFFF - 28;
constexpr u32 CAPS    = 0xFFFFFFFF - 29;
constexpr u32 NONE    = 0xFFFFFFFF - 30;
constexpr u32 ALTGR   = 0xFFFFFFFF - 31;
constexpr u32 NUMLCK  = 0xFFFFFFFF - 32;

constexpr u32 lowercase[128] = {
UNKNOWN,ESC,'1','2','3','4','5','6','7','8', '9','0','-','=','\b','\t','q','w','e','r',
't','y','u','i','o','p','[',']','\n',CTRL, 'a','s','d','f','g','h','j','k','l',';',
'\'','`',LSHFT,'\\','z','x','c','v','b','n', 'm',',','.','/',RSHFT,'*',ALT,' ',CAPS,F1,
F2,F3,F4,F5,F6,F7,F8,F9,F10,NUMLCK, SCRLCK,HOME,UP,PGUP,'-',LEFT,UNKNOWN,RIGHT,'+',END,
DOWN,PGDOWN,INS,DEL,UNKNOWN,UNKNOWN,UNKNOWN,F11,F12,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN, UNKNOWN,UNKNOWN,UNKNOWN
};

constexpr u32 uppercase[128] = {
UNKNOWN,ESC,'!','@','#','$','%','^','&','*', '(',')','_','+','\b','\t','Q','W','E','R',
'T','Y','U','I','O','P','{','}','\n',CTRL, 'A','S','D','F','G','H','J','K','L',':',
'"','~',LSHFT,'|','Z','X','C','V','B','N', 'M','<','>','?',RSHFT,'*',ALT,' ',CAPS,F1,
F2,F3,F4,F5,F6,F7,F8,F9,F10,NUMLCK, SCRLCK,HOME,UP,PGUP,'-',LEFT,UNKNOWN,RIGHT,'+',END,
DOWN,PGDOWN,INS,DEL,UNKNOWN,UNKNOWN,UNKNOWN,F11,F12,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN 
};

/**
 * @brief Inerrupt handler.
 * 
 * @param [in] regs - given pointer to interrupt register state.
 */
static void handler(arch::x86::int_reg_t *regs) noexcept
{
    (void)regs; // do nothing
}

Keyboard::Keyboard(void) noexcept
{
    m_is_caps      = false;
    m_is_caps_lock = false;
}

void Keyboard::initialize(void) noexcept
{
    log::success("%s\n", "initialized keyboard driver");
}

void Keyboard::shutdown(void) noexcept
{
    log::success("%s\n", "shutdown keyboard driver");
}

kstd::string Keyboard::name(void) const noexcept
{
    return "PS/2 Keyboard Driver";
}

driver::dtype Keyboard::type(void) const noexcept
{
    return driver::dtype::device;
}

void Keyboard::wait(void) const noexcept
{
    while((arch::x86::inb(0x64) & 0x01) == 0);
}

void Keyboard::handle_interrupt(void) const noexcept
{
    arch::x86::irq_install_handler(1, &handler);
}

u8 Keyboard::getchar(void) const noexcept
{
    wait();

    u8 scan_code = arch::x86::inb(0x60) & 0x7F; // get code of key that is pressed
    u8 press     = arch::x86::inb(0x60) & 0x80; // is key is pressed down or released
    
    switch(static_cast<key>(scan_code)) {    
        case key::up_arrow:
        case key::down_arrow:
        case key::left_arrow:
        case key::right_arrow:

        case key::lshft:
            if(!press)
                m_is_caps = true;
            else
                m_is_caps = false;
            break;

        case key::caps_lock:
            if(!m_is_caps_lock && !press)
                m_is_caps_lock = true;
            else if(m_is_caps_lock && !press)
                m_is_caps_lock = false;
            break;

        default:
            if(!press) {
                u8 cc;

                if((m_is_caps || m_is_caps_lock) && (lowercase[scan_code] != UNKNOWN))
                    cc = uppercase[scan_code];
                else
                    cc = lowercase[scan_code];

                return cc;
            }
            break;
    }

    return 0;
}

Keyboard keyboard;

} // namespace driver
} // namespace kernel