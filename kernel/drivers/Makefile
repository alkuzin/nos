CC = gcc

INCLUDE_DIR = ../../include
LIBC_DIR    = $(INCLUDE_DIR)/libc

LFLAGS = -m elf_i386 -relocatable -z noexecstack 
CFLAGS = -Wall -Wextra -Werror -g -m32 -O2 -Oz -nostdlib -nodefaultlibs \
         -fno-pie -fno-exceptions -fno-stack-protector -fno-builtin  \
         -ffreestanding -I $(INCLUDE_DIR) -I $(LIBC_DIR)

NAME = _drivers.o

SRC  = keyboard timer vga
SRCS = $(addsuffix .c, $(SRC))
OBJS = $(addsuffix .o, $(SRC))

OBJS_DIR = objs/
OBJS_PREFIXED     = $(addprefix $(OBJS_DIR), $(OBJS))
OBJS_PREFIXED_ASM = $(addprefix $(OBJS_DIR), $(OBJS_ASM))

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
