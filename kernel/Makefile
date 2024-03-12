CC = gcc

INCLUDE_DIR = ../include

CFLAGS = -Wall -Wextra -Werror -g -m32 -nostdlib -fno-pie -ffreestanding -I $(INCLUDE_DIR)

NAME = _kernel.o

SRC  = kernel tty kprintf vga
SRCS = $(addsuffix .c, $(SRC))
OBJS = $(addsuffix .o, $(SRC))

OBJS_DIR = objs/
OBJS_PREFIXED = $(addprefix $(OBJS_DIR), $(OBJS))

$(OBJS_PREFIXED): $(SRCS)
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $(SRCS)
	mv *.o $(OBJS_DIR)

$(NAME): $(OBJS_PREFIXED)
	ld -m elf_i386 -relocatable $(OBJS_PREFIXED) -o $(NAME)

all: $(NAME) 

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: clean all
