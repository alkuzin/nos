include libc_common.mk

INCLUDE_DIR = ../../include
LIBC_DIR    = $(INCLUDE_DIR)/libc

NAME = libc.a

LIBC_MATH_DIR   = math/
LIBC_STRING_DIR = string/
LIBC_STDIO_DIR  = stdio/
LIBC_STDLIB_DIR = stdlib/

OBJS = $(LIBC_MATH_DIR)libc_math.o $(LIBC_STRING_DIR)libc_string.o $(LIBC_STDIO_DIR)libc_stdio.o \
	   $(LIBC_STDLIB_DIR)libc_stdlib.o

$(OBJS):
	$(MAKE) -C $(LIBC_MATH_DIR) all
	$(MAKE) -C $(LIBC_STRING_DIR) all
	$(MAKE) -C $(LIBC_STDIO_DIR) all
	$(MAKE) -C $(LIBC_STDLIB_DIR) all

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

all: $(NAME) 

clean:
	$(MAKE) -C $(LIBC_MATH_DIR) fclean
	$(MAKE) -C $(LIBC_STRING_DIR) fclean
	$(MAKE) -C $(LIBC_STDIO_DIR) fclean
	$(MAKE) -C $(LIBC_STDLIB_DIR) fclean

fclean: clean
	rm -f $(NAME)

re: clean all
