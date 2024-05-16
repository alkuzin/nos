CC  = gcc
ASM = nasm

INCLUDE_DIR = ../../include
LIBC_DIR    = $(INCLUDE_DIR)/libc

LFLAGS   = -m elf_i386 -relocatable -z noexecstack 
ASMFLAGS = -f elf
CFLAGS   = -Wall -Wextra -Werror -g -std=c2x -m32 -O2 -Oz -nostdlib -nodefaultlibs \
         -fno-pie -fno-exceptions -fno-stack-protector -fno-builtin  \
         -ffreestanding -I $(INCLUDE_DIR) -I $(LIBC_DIR)