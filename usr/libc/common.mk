INCLUDE_DIR = ../../include/
CC          = gcc
LFLAGS      = -m elf_i386 -relocatable -z noexecstack 
CFLAGS      = -Wall -Wextra -Werror -g -std=c2x -m32 -O2 -Oz -nostdlib -nodefaultlibs \
              -fno-pie -fno-exceptions -fno-stack-protector -fno-builtin  \
              -ffreestanding -I $(INCLUDE_DIR)