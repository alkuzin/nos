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

/*
Global Descriptor Table (GDT) is a structure specific to the IA-32 
and x86-64 architectures. It contains entries telling the CPU about memory segments.
*/

#ifndef _KERNEL_KEYBOARD_H_
#define _KERNEL_KEYBOARD_H_

#include <kernel/ports.h>
#include <kernel/irq.h>

#define INPUT_BUFFER_SIZE 256

typedef enum {
    KEY_ESC         = 0x01,
    KEY_BACKSPACE   = 0x0E,
    KEY_TAB         = 0x0F,
    KEY_ENTER       = 0x1C,
    KEY_LCTRL       = 0x1D,
    KEY_LSHFT       = 0x2A,
    KEY_BACKSLASH   = 0x2B,
    KEY_LALT        = 0x38,
    KEY_SPACE       = 0x39,
    KEY_CAPS_LOCK   = 0x3A,
    KEY_LEFT_ARROW  = 0x4B,
    KEY_RIGHT_ARROW = 0x4D,
    KEY_UP_ARROW    = 0x48,
    KEY_DOWN_ARROW  = 0x50
} keycode_t;

/* keyboard initialization */
void keyboard_init(void);

/* keyboard key press handler */
void keyboard_handler(int_reg_t *regs);

/* keyboard wait for user to press a key */
void keyboard_wait(void);

/* keyboard get character on key press */
uint8_t keyboard_getchar(void);

#endif /* _KERNEL_KEYBOARD_H_ */
