CC = gcc

OBJS_DIR    = objs
BUILD_DIR   = build
BOOT_DIR    = $(KERNEL_DIR)/boot
INCLUDE_DIR = include
KERNEL_DIR  = kernel
LIBK_DIR    = $(KERNEL_DIR)/libk

KERNEL_LIB  = $(LIBK_DIR)/libk.a

NAME   = $(BUILD_DIR)/simple_os.bin
LFLAGS = -z noexecstack -m elf_i386 -T

OBJS = $(KERNEL_DIR)/_kernel.o \
       $(BOOT_DIR)/_boot.o

$(OBJS):
	$(MAKE) -C $(BOOT_DIR) all
	$(MAKE) -C $(KERNEL_DIR) all
	$(MAKE) -C $(LIBK_DIR) all

$(NAME): $(OBJS)
	ld $(LFLAGS) linker.ld -o $(NAME) $(OBJS) $(KERNEL_LIB)

all: $(NAME)
	mkdir -p $(BUILD_DIR)

clean:
	$(MAKE) -C $(KERNEL_DIR) fclean
	$(MAKE) -C $(BOOT_DIR) fclean
	$(MAKE) -C $(LIBK_DIR) fclean

fclean: clean
	rm -f $(NAME)
	rm -f $(BUILD_DIR)/simple_os.img

re: clean all

build-img: all $(NAME)
	cp $(NAME) $(BUILD_DIR)/simple_os.img
	truncate -s 1440k $(BUILD_DIR)/simple_os.img

init:
	qemu-system-i386 -kernel $(NAME)
