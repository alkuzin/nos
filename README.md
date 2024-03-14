# Simple OS

<img src="res/simple-os-banner.png">

## Description

Test OS project for x86_32 platform. ([documentation](doc/README.md))

## Tools
The project was made on Debian 12

 - GCC (13.2.0)
 - NASM (2.16.01)
 - GNU Make (4.3)
 - GNU ld (2.42)
 - GNU ar (2.42)
 - truncate (9.4)
 - QEMU emulator (8.2.1)
 - GNU GRUB (2.12-1)

## License

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

## Updates history

> simple-os (v0.0.1):
- added `kmain()`
- added kernel library `libk` (`<string.h>`, `<ctype.h>`, `<stddef.h>`, `<stdint.h>`)
- added text output to VGA

> simple-os (v0.0.2):
- added `kprintf()` function (*%#xXidpusc* options of standard C library printf)
- added to libk `<stdarg.h>`, `<memory.h>`, `<math.h> `

> simple-os (v0.0.3):
- added VGA driver
- added color printing function `kprintc()` with 16 colors

<img src="res/simple-os-vga-output.png">

> simple-os (v0.0.4):
- added `ksleep()` & `__ksleep()` functions in `<kernel.h>`
- modified VGA driver (added new functions: `update_cursor()`, `port_byte_out()`)
- added default background and foreground colors in `kernel/tty.h`
- added VGA scrolling (`__kscroll()`)

<img src="res/simple-os-vga-scroll.gif">

> simple-os (v0.0.5):
- added `\v` `\t` `\r` `\b` special characters support in `kputchar()`
- define a signed integer types in `<stdint.h>`
- added `kvprintf()` function
- added kernel halt `khalt()` & kernel panic `kpanic()` for detecting errors 
- added Global Descriptor Table

<img src="res/simple-os-kernel-panic.png">

> simple-os (v0.0.6):
- added ports in `<ports.h>`
- added TSS (Task State Segment) entry in `<gdt.h>`
- added IDT (Interrupt Descriptor Table) in `<idt.h>`
- added GNU GRUB support
- added IRQ (Interrupt Request) in `<irq.h>`

> simple-os (v0.0.7):
- added PIT (Programmable Interval Timer) in `<timer.h>`
- added keyboard driver in `<keyboard.h>`

<img src="res/simple-os-keyboard.gif">
