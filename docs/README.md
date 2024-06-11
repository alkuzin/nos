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
cd nos/
```

To build kernel as `.iso` and run on QEMU use:

```console
make all && make init
```

To return everything to original state:
```console
make fclean
```