CC = gcc
ASM = nasm

SRC_DIR     = src
OBJS_DIR    = objs
BUILD_DIR   = build
BOOT_DIR    = $(SRC_DIR)/boot
INCLUDE_DIR = include

#SRC_KERNEL = kernel
#SRCS_KERNEL= $(addprefix kernel/, $(addsuffix .c, $(SRC_KERNEL)))
#OBJS_KERNEL= $(addprefix kernel/, $(addsuffix .o, $(SRC_KERNEL)))

#SRCS = $(addsuffix .c, $(SRC))
#OBJS = $(addsuffix .o, $(SRC))

#SRCS_PREFIXED = $(addprefix $(SRC_DIR)/, $(SRCS))
#OBJS_PREFIXED = $(addprefix $(OBJS_DIR)/, $(OBJS))

SRCS_PREFIXED = $(SRC_DIR)/kernel/kernel.c
OBJS_PREFIXED = $(OBJS_DIR)/kernel.o $(OBJS_DIR)/boot.o

CFLAGS   = -Wall -Wextra -Werror -g -m32 -nostdlib -fno-pie -ffreestanding -I $(INCLUDE_DIR)
ASMFLAGS = -f elf
LFLAGS   = -z noexecstack -m elf_i386 -T

NAME = $(BUILD_DIR)/simple_os.bin

$(OBJS_PREFIXED): $(SRCS_PREFIXED)
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $(SRCS_PREFIXED)
	mv *.o $(OBJS_DIR)

$(NAME): $(OBJS_PREFIXED)
	$(ASM) $(ASMFLAGS) -o $(OBJS_DIR)/boot.o $(BOOT_DIR)/boot.s
	ld $(LFLAGS) linker.ld -o $(NAME) $(OBJS_PREFIXED)

all: $(NAME)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: clean all

init:
	qemu-system-i386 -kernel $(NAME)
