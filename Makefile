OBJS_DIR    = objs
BUILD_DIR   = build
INCLUDE_DIR = include
KERNEL_DIR  = kernel
LIBC_DIR    = libc
ISO_DIR     = isodir
BOOT_DIR    = $(KERNEL_DIR)/boot
CPU_DIR     = $(KERNEL_DIR)/cpu
DRIVERS_DIR = $(KERNEL_DIR)/drivers
MM_DIR      = $(KERNEL_DIR)/mm
PM_DIR      = $(KERNEL_DIR)/pm
LIBK_DIR    = $(KERNEL_DIR)/libk
LIBC        = $(LIBC_DIR)/libc.a
KSH_DIR     = $(KERNEL_DIR)/shell
FS_DIR      = $(KERNEL_DIR)/fs

NAME     = $(BUILD_DIR)/nos.elf
NAME_ISO = nos.iso
LFLAGS   = -z noexecstack -m elf_i386 -T

OBJS = $(KERNEL_DIR)/_kernel.o \
       $(BOOT_DIR)/_boot.o \
       $(CPU_DIR)/_cpu.o \
       $(DRIVERS_DIR)/_drivers.o \
       $(MM_DIR)/_mm.o \
       $(PM_DIR)/_pm.o \
       $(KSH_DIR)/_ksh.o \
       $(FS_DIR)/_fs.o

$(OBJS):
	$(MAKE) -C $(LIBC_DIR) all
	$(MAKE) -C $(BOOT_DIR) all
	$(MAKE) -C $(KERNEL_DIR) all
	$(MAKE) -C $(CPU_DIR) all
	$(MAKE) -C $(DRIVERS_DIR) all
	$(MAKE) -C $(MM_DIR) all
	$(MAKE) -C $(PM_DIR) all
	$(MAKE) -C $(KSH_DIR) all
	$(MAKE) -C $(FS_DIR) all

$(NAME): $(OBJS)
	mkdir -p $(BUILD_DIR)
	ld $(LFLAGS) $(KERNEL_DIR)/linker.ld -o $(NAME) $(OBJS) $(LIBC)

all: $(NAME) build-iso

clean:
	$(MAKE) -C $(LIBC_DIR) fclean
	$(MAKE) -C $(KERNEL_DIR) fclean
	$(MAKE) -C $(BOOT_DIR) fclean
	$(MAKE) -C $(CPU_DIR) fclean
	$(MAKE) -C $(DRIVERS_DIR) fclean
	$(MAKE) -C $(MM_DIR) fclean
	$(MAKE) -C $(PM_DIR) fclean
	$(MAKE) -C $(KSH_DIR) fclean
	$(MAKE) -C $(FS_DIR) fclean

fclean: clean
	rm -f $(NAME)
	rm -rf $(ISO_DIR) $(NAME_ISO)
	rm -f $(NAME_ISO)
	rm -rf docs/doxygen/html/ docs/doxygen/man/ docs/doxygen/rtf/

re: clean all

build-iso: $(NAME)
	mkdir -p $(ISO_DIR) $(ISO_DIR)/boot/ $(ISO_DIR)/boot/grub/
	cp $(NAME) $(ISO_DIR)/boot/kernel.elf
	cp grub/grub.cfg $(ISO_DIR)/boot/grub/grub.cfg
	grub-mkrescue -o $(NAME_ISO) $(ISO_DIR)

init-iso: 
	qemu-system-i386 -m 2024 -cdrom $(NAME_ISO)

init: init-iso

debug: 
	qemu-system-i386 -s -S -m 2024 -cdrom $(NAME_ISO) & gdb $(NAME) -ex "target remote localhost:1234" -tui