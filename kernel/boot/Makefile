include ../kernel_common.mk

NAME     = _boot.o

$(NAME):
	$(ASM) $(ASMFLAGS) -o $(NAME) boot.s

all: $(NAME) 

clean:
	rm -f $(NAME)

fclean: clean

re: clean all
