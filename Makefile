OBJS_DIR    = objs
BUILD_DIR   = build
INCLUDE_DIR = include
KERNEL_DIR  = kernel
ISO_DIR     = isodir
BOOT_DIR    = $(KERNEL_DIR)/boot


CPU_DIR     = $(KERNEL_DIR)/cpu
DRIVERS_DIR = $(KERNEL_DIR)/drivers

LIBK_DIR    = $(KERNEL_DIR)/libk
KERNEL_LIB  = $(LIBK_DIR)/libk.a

NAME     = $(BUILD_DIR)/simple_os.elf
NAME_ISO = simple_os.iso
LFLAGS   = -z noexecstack -m elf_i386 -T

OBJS = $(KERNEL_DIR)/_kernel.o \
       $(BOOT_DIR)/_boot.o \
       $(CPU_DIR)/_cpu.o \
       $(DRIVERS_DIR)/_drivers.o

$(OBJS):
	$(MAKE) -C $(BOOT_DIR) all
	$(MAKE) -C $(KERNEL_DIR) all
	$(MAKE) -C $(LIBK_DIR) all
	$(MAKE) -C $(CPU_DIR) all
	$(MAKE) -C $(DRIVERS_DIR) all

$(NAME): $(OBJS)
	mkdir -p $(BUILD_DIR)
	ld $(LFLAGS) $(KERNEL_DIR)/linker.ld -o $(NAME) $(OBJS) $(KERNEL_LIB)

all: $(NAME) build-iso

clean:
	$(MAKE) -C $(KERNEL_DIR) fclean
	$(MAKE) -C $(BOOT_DIR) fclean
	$(MAKE) -C $(LIBK_DIR) fclean

fclean: clean
	rm -f $(NAME)
	rm -rf $(ISO_DIR) $(NAME_ISO)
	rm -f $(NAME_ISO)

re: clean all

build-iso: $(NAME)
	mkdir -p $(ISO_DIR) $(ISO_DIR)/boot/ $(ISO_DIR)/boot/grub/
	cp $(NAME) $(ISO_DIR)/boot/kernel.elf
	cp grub/grub.cfg  $(ISO_DIR)/boot/grub/grub.cfg
	grub-mkrescue -o $(NAME_ISO) $(ISO_DIR)

init-iso: 
	qemu-system-i386 -m 2024 -cdrom $(NAME_ISO)

init: init-iso
