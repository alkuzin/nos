CC  = gcc
ASM = nasm

INCLUDE_DIR = ../include

CFLAGS = -Wall -Wextra -Werror -g -m32 -nostdlib -fno-pie -ffreestanding -I $(INCLUDE_DIR)
ASMFLAGS = -f elf

NAME = _kernel.o

SRC      = kernel tty kprintf vga gdt idt irq ports
SRC_ASM  = gdt_flush idt_flush
SRCS     = $(addsuffix .c, $(SRC))
OBJS     = $(addsuffix .o, $(SRC))
OBJS_ASM = $(addsuffix .o, $(SRC_ASM))

OBJS_DIR = objs/
OBJS_PREFIXED     = $(addprefix $(OBJS_DIR), $(OBJS))
OBJS_PREFIXED_ASM = $(addprefix $(OBJS_DIR), $(OBJS_ASM))

$(OBJS_PREFIXED): $(SRCS)
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $(SRCS)
	mv *.o $(OBJS_DIR)

asm: 
	$(ASM) $(ASMFLAGS) -o gdt_flush.o gdt_flush.s
	$(ASM) $(ASMFLAGS) -o idt_flush.o idt_flush.s
	mv *.o $(OBJS_DIR)

$(NAME): $(OBJS_PREFIXED) asm 
	ld -m elf_i386 -relocatable -z noexecstack $(OBJS_PREFIXED) $(OBJS_PREFIXED_ASM) -o $(NAME)

all: $(NAME) 

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: clean all
