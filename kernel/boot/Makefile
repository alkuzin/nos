ASM      = nasm
ASMFLAGS = -f elf
NAME     = _boot.o

$(NAME):
	$(ASM) $(ASMFLAGS) -o $(NAME) boot.s

all: $(NAME) 

clean:
	rm -f $(NAME)

fclean: clean

re: clean all
