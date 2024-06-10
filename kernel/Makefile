include kernel_common.mk

INCLUDE_DIR = ../include
LIBC_DIR    = $(INCLUDE_DIR)/libc

NAME = _kernel.o

SRC  = kernel tty printk nosstd panic login
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