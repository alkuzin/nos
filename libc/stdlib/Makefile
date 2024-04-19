CC = gcc

INCLUDE_DIR = ../../include/libc

LFLAGS = -m elf_i386 -relocatable -z noexecstack 
CFLAGS = -Wall -Wextra -Werror -m32 -O2 -Oz -nostdlib -nodefaultlibs \
         -fno-pie -fno-exceptions -fno-stack-protector -fno-builtin  \
         -ffreestanding -I $(INCLUDE_DIR)

NAME = libc_stdlib.o

SRC  = kmalloc kfree
SRCS = $(addsuffix .c, $(SRC))
OBJS = $(addsuffix .o, $(SRC))

OBJS_DIR = objs/
OBJS_PREFIXED = $(addprefix $(OBJS_DIR), $(OBJS))

$(OBJS_PREFIXED): $(SRCS)
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $(SRCS)
	mv *.o $(OBJS_DIR)

$(NAME): $(OBJS_PREFIXED)
	ld $(LFLAGS) $(OBJS_PREFIXED) -o $(NAME)

all: $(NAME) 

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: clean all
