include ../kernel_common.mk

NAME = _cpu.o

SRC      = gdt idt irq
SRC_ASM  = gdt_flush idt_flush
SRCS     = $(addsuffix .c, $(SRC))
OBJS     = $(addsuffix .o, $(SRC))
OBJS_ASM = $(addsuffix .o, $(SRC_ASM))

OBJS_DIR = objs/
OBJS_PREFIXED     = $(addprefix $(OBJS_DIR), $(OBJS))
OBJS_PREFIXED_ASM = $(addprefix $(OBJS_DIR), $(OBJS_ASM))

$(OBJS_PREFIXED): $(SRCS)
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $(SRCS)
	mv *.o $(OBJS_DIR)

asm: 
	$(ASM) $(ASMFLAGS) -o gdt_flush.o gdt_flush.s
	$(ASM) $(ASMFLAGS) -o idt_flush.o idt_flush.s
	mv *.o $(OBJS_DIR)

$(NAME): $(OBJS_PREFIXED) asm 
	ld $(LFLAGS) $(OBJS_PREFIXED) $(OBJS_PREFIXED_ASM) -o $(NAME)

all: $(NAME) 

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: clean all
