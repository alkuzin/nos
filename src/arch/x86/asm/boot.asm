# Project name: NOS (Null Operating System).
# Description: Monolithic UNIX-like operating system.
# Licence: GPL-3.0.
# Author: Alexander (@alkuzin).

# Magic number is a value that BIOS recognize as a kernel.
.set MBOOT_MAGIC, 0x1BADB002

# Flags can control various functions of the BIOS such as:
# enabling/disabling specific hardware components, setting up boot options,
# adjusting power management settings and etc.
.set MBOOT_PAGE_ALIGN, 1 << 0 # Memory should be page-aligned to 4 KB.
.set MBOOT_MEM_INFO,   1 << 1 # Request memory information from the bootloader.
.set MBOOT_USE_GFX,    1 << 2 # Enable graphics mode.

# Indicates a bootable device.
.set MBOOT_FLAGS, (MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO | MBOOT_USE_GFX)

# The purpose of checksum is to ensure OS stability & security
# by detecting any unauthorised changes to the BIOS firmware.
.set MBOOT_CHECKSUM, -(MBOOT_MAGIC + MBOOT_FLAGS)

.section .multiboot
.align 4
    .long MBOOT_MAGIC       # Declare double word of magic number.
    .long MBOOT_FLAGS       # Declare double word of magic number flags.
    .long MBOOT_CHECKSUM    # Declare double word of magic number checksum.
    .long 0, 0, 0, 0, 0     # Declare double words for some fields.

    .long 0                 # Linear graphics mode.
    .long 1024              # Screen width.
    .long 768               # Screen height.
    .long 32                # Depth.

# Higher-half kernel virtual base address (3 GB).
.set base_address, 0xC0000000

.section .bss               # Stores uninitialized global and static variables.
.align 16                   # Reserving space for the stack.
                            # Setup stack.
.global stack_bottom
.global stack_top
stack_bottom:
    .skip 65536
stack_top:

.section .text              # Contains executable instructions of a program.

.global boot
boot:
    # Move initial page directory address to ESI, ECX & EDX.
    mov $(initial_page_dir - base_address), %esi
    mov %esi, %ecx
    mov %esi, %edx

    or $0x00000003, %ecx    # Set the attributes: read/write & present bits.
    mov %ecx, 0xFFC(%edx)   # Initial page directory address + 4092.
    mov %esi, %cr3          # Update the page directory.

    mov %cr4, %ecx          # Get the control register 4 value.
    or $0x00000010, %ecx    # Set the PSE (Page Size Extension) bit.
    mov %ecx, %cr4          # Update CR4 to enable 4 MB pages.

    mov %cr0, %ecx          # Get the control register 0 value.
    or $0x80000000, %ecx    # Set the paging bit.
    mov %ecx, %cr0          # Update CR0 to enable paging.

    call higher_half

higher_half:
    mov %cr0, %ecx          # Get the control register 0 value.
    or $1, %cl              # Set the protection mode bit.
    mov %ecx, %cr0          # Update the control register 0.

    mov $stack_top, %esp    # Set the stack pointer.
    push %ebx               # Push multiboot info.
    push %eax               # Push magic number.
    xor %ebp, %ebp          # Reset ebp.

    .extern kmain           # From kernel/main.c.
    call kmain              # Call kernel entry point.
    cli                     # Clear interrupt flag (disables interrupts).

halt:
    hlt	                    # This instruction halts the CPU.
    jmp halt                # Infinite loop.

.section .data              # Stores initialized global and static variables.
.align 0x1000

.global initial_page_dir    # Used for enabling paging in early boot.
initial_page_dir:
# Identity map first 3 GB of virtual memory (0x00000000-0xC0000000).
.set i, 0x00000083          # 4 MB page is present & allowed to read/write.
.rept 0x300                 # 0x300 = 0xbfc00000/0x00400000 + 1.
    .long i
    .set i, i + 0x00400000  # 4 MB.
.endr

# Map first 4 MB page to (0xC0000000-0xC0400000) from (0x00000000-0x00400000).
.long 0x00000083            # 4 MB page is present & allowed to read/write.

# Identity map addresses (0xC0400000-0xFFFFFFFF).
.set i, 0xC0400083
.rept 0xFF                  # 0xFF = (0xffc00000 - 0xc0400000)/0x00400000 + 1.
    .long i
    .set i, i + 0x00400000  # 4 MB.
.endr
