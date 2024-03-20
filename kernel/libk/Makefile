CC = gcc

INCLUDE_DIR = ../../include

CFLAGS = -Wall -Wextra -Werror -g -m32 -nostdlib -fno-pie -ffreestanding -I $(INCLUDE_DIR)

NAME = libk.a

SRC  = math string memory stdlib
SRCS = $(addsuffix .c, $(SRC))
OBJS = $(addsuffix .o, $(SRC))

OBJS_DIR = objs/
OBJS_PREFIXED = $(addprefix $(OBJS_DIR), $(OBJS))

$(OBJS_PREFIXED): $(SRCS)
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $(SRCS)
	mv *.o $(OBJS_DIR)

$(NAME): $(OBJS_PREFIXED)
	ar rcs $(NAME) $(OBJS_PREFIXED)

all: $(NAME) 

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: clean all
