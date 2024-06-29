INCLUDE_DIR = include
LIBC_DIR    = libc
LIB_DIR     = lib
LIBC        = $(LIBC_DIR)/libc.a
NAME        = $(LIB_DIR)/libc.a

all:
	$(MAKE) -C $(LIBC_DIR) all
	mv $(LIBC) $(LIB_DIR)

clean:
	$(MAKE) -C $(LIBC_DIR) fclean

fclean: clean
	rm -f $(NAME)

re: clean all