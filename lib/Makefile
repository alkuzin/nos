include common.mk

INCLUDE_DIR = ../../include

NAME = lib.a

LIB_MATH_DIR   = math/
LIB_STRING_DIR = string/
LIB_STDLIB_DIR = stdlib/

OBJS = $(LIB_MATH_DIR)lib_math.o $(LIB_STRING_DIR)lib_string.o $(LIB_STDLIB_DIR)lib_stdlib.o

$(OBJS):
	$(MAKE) -C $(LIB_MATH_DIR) all
	$(MAKE) -C $(LIB_STRING_DIR) all
	$(MAKE) -C $(LIB_STDLIB_DIR) all

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

all: $(NAME) 

clean:
	$(MAKE) -C $(LIB_MATH_DIR) fclean
	$(MAKE) -C $(LIB_STRING_DIR) fclean
	$(MAKE) -C $(LIB_STDLIB_DIR) fclean

fclean: clean
	rm -f $(NAME)

re: clean all