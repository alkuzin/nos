# The Null Operating System documentation

<img src="../res/nos_docs_banner.png">

## Contents

1. [Introduction](#1-introduction)
2. [Tools installation](#2-tools-installation)
3. [Installation](#3-installation)
4. [Project structure](#4-project-structure)
5. [Headers overview](#5-headers-overview)

## 1. Introduction
NOS - hobby Unix-like x86-32 operating system.

## 2. Tools installation

List of tools:

 - GCC (13.2.0)
 - NASM (2.16.01)
 - GNU Make (4.3)
 - GNU ld (2.42)
 - GNU ar (2.42)
 - truncate (9.4)
 - QEMU emulator (8.2.1)
 - GNU GRUB (2.12-1)

For Debian/Ubuntu:
```console
sudo apt install gcc nasm make qemu-system-x86 binutils
sudo apt-get install grub-pc-bin mtools
```

## 3. Installation
First clone this repository:
```console
https://github.com/alkuzin/nos.git
```
Then move to the `nos/` directory:
```console
cd simple-os/
```

To build kernel as `.iso` and run on QEMU use:

```console
make all && make init
```

To return everything to original state:
```console
make fclean
```

## 4. Project structure

 - `build/`   - contains .elf files
 - `docs/`    - documentation
 - `grub/`    - contains GNU GRUB config file
 - `include/` - contains kernel & libk header files
 - `isodir/`  - contains GNU GRUB config file & compiled kernel 
 - `kernel/`  - kernel source code
 - `libc/`    - C standard library
 - `res/`     - screenshots & documentation images
 - LICENSE    - MIT license
 - Makefile   - main makefile
 - README.md  - OS description

In `kernel/`:

 - `boot/`    - contains bootloader
 - `cpu/`     - contains GDT, IDT, IRQ        
 - `drivers/` - contains OS drivers (VGA, keyboard, timer)        
 - `libk/`    - contains kernel library `libk` source
 - `mm/`      - contains virtual & physical memory managers
 - `shell/`   - contains kernel shell


## 5. Headers overview 

## Kernel
 - `gdt.h`       - Global Descriptor Table
 - `idt.h`       - Interrupt Descriptor Table
 - `irq.h`       - Interrupt Requests
 - `kernel.h`    - kernel main header file (contains OS name, version, kernel entry point `kmain()`)
 - `keyboard.h`  - keyboard driver
 - `mm.h`        - main memory manager
 - `multiboot.h` - multiboot information structure
 - `pmm.h`       - physical memory manager
 - `ports.h`     - input/output ports
 - `timer.h`     - Programmable Interval Timer driver
 - `tty.h`       - kernel terminal output functions
 - `vga.h`       - vga driver
 - `vmm.h`       - virtual memory manager
 - `kmalloc.h`   - dynamic memory allocation functions

## Libc
 - `ctype.h`  - declares several macros that are useful for testing and mapping characters
 - `math.h`   - defines various mathematical functions
 - `memory.h` - defines several memory management functions
 - `stdarg.h` - declares defines several macros for stepping through a list of arguments 
 				whose number and types are not known to the called function
 - `stddef.h` - defines NULL & size_t
 - `stdint.h` - defines an integer types of a fixed width
 - `stdio.h`  - defines several input/output functions
 - `string.h` - defines several strings management functions

## Shell
 - `ksh.h`    - contains kernel shell functions