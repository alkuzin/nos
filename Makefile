# Project name: NOS (Null Operating System).
# Description: Monolithic UNIX-like operating system.
# Licence: GPL-3.0.
# Author: Alexander (@alkuzin).

# Assembler & linker settings.
ASM    		 = as
ASM_FLAGS    = --32
LINKER 		 = ld
LINKER_FLAGS = -z noexecstack -melf_i386

SELECTED_TARGET = x86

KERNEL_PATH  	 = .
BUILD_PATH   	 = build
ISO_PATH     	 = $(BUILD_PATH)/iso
ARCH_PATH    	 = $(KERNEL_PATH)/src/arch
ASM_PATH     	 = $(ARCH_PATH)/$(SELECTED_TARGET)/asm
TARGETS_PATH 	 = targets/$(SELECTED_TARGET)
GRUB_CONFIG_PATH = targets

NAME 	   		  = nos
ISO_NAME   		  = $(BUILD_PATH)/$(NAME).iso
KERNEL_ELF 		  = $(ISO_PATH)/boot/$(NAME).elf
KERNEL_STATIC_LIB = $(KERNEL_PATH)/target/$(SELECTED_TARGET)-unknown-none/debug/lib$(NAME).a
BUILD_TARGET      = $(TARGETS_PATH)/$(SELECTED_TARGET)-unknown-none.json

ASM_SRC  = $(ASM_PATH)/boot
ASM_SRCS = $(addsuffix .asm, $(ASM_SRC))
ASM_OBJS = $(addsuffix .o,   $(ASM_SRC))

# TODO: decribe "rustup override set nightly-2025-05-24" in installation docs.

compile_tests:
	cargo build --manifest-path $(KERNEL_PATH)/Cargo.toml --features ktest

$(KERNEL_STATIC_LIB):
	cargo build --manifest-path $(KERNEL_PATH)/Cargo.toml

OBJS = $(ASM_OBJS) $(KERNEL_STATIC_LIB)

$(ASM_PATH)/%.o: $(ASM_PATH)/%.asm
	$(ASM) $(ASM_FLAGS) -c $< -o $@

$(NAME): $(OBJS) $(KERNEL_STATIC_LIB)
	$(LINKER) $(LINKER_FLAGS) -o $(KERNEL_ELF) -T $(TARGETS_PATH)/linker.ld $(OBJS)

build_tests: $(OBJS) compile_tests
	$(LINKER) $(LINKER_FLAGS) -o $(KERNEL_ELF) -T $(TARGETS_PATH)/linker.ld $(OBJS)

$(ISO_PATH):
	mkdir -p $(ISO_PATH)/boot/grub/

$(BUILD_PATH):
	mkdir -p $(BUILD_PATH)

all: check $(BUILD_PATH) $(ISO_PATH) $(NAME)

clean:
	rm -f $(OBJS) $(KERNEL_ELF)

fclean: clean
	rm -f $(ISO_NAME)
	rm -rf $(BUILD_PATH)/
	cargo clean --manifest-path $(KERNEL_PATH)/Cargo.toml

re: fclean all

build-iso:
	cp $(GRUB_CONFIG_PATH)/grub.cfg $(ISO_PATH)/boot/grub/grub.cfg
	grub-mkrescue -o $(ISO_NAME) $(ISO_PATH)

init:
	qemu-system-i386 -enable-kvm -m 256 -cdrom $(ISO_NAME) -serial stdio

compile_default:
	cargo build --manifest-path $(KERNEL_PATH)/Cargo.toml

run: compile_default all build-iso init

test: compile_tests all build-iso init

check-clippy:
	cargo clippy --manifest-path $(KERNEL_PATH)/Cargo.toml -- -D warnings -W clippy::all

check: check-clippy
	cargo check --manifest-path $(KERNEL_PATH)/Cargo.toml

build-doc:
	cargo doc --document-private-items --manifest-path $(KERNEL_PATH)/Cargo.toml

doc:
	cargo doc --document-private-items --open --manifest-path $(KERNEL_PATH)/Cargo.toml

debug:
	qemu-system-i386 -enable-kvm -s -S -m 256 -cdrom $(ISO_NAME) & gdb $(KERNEL_ELF) -ex "target remote localhost:1234" -tui