# Project name: NOS (Null Operating System).
# Description: Monolithic UNIX-like operating system.
# Licence: GPL-3.0.
# Author: Alexander (@alkuzin).

.global gdt_flush

gdt_flush:
    mov 4(%esp), %eax   # Get function argument from stack.
    lgdt (%eax)         # Load Global Descriptor Table.

                        # Reload data segment registers.

    mov $0x10, %eax     # Kernel data segment selector.
    mov %ax, %ds        # Allow the CPU to access to kernel data segment.
    mov %ax, %es        # Allow the CPU to access to kernel extra segment.
    mov %ax, %fs        # Allow the CPU to access to kernel additional segment.
    mov %ax, %gs        # Allow the CPU to access to kernel global segment.
    mov $0x18, %ax      # Offset in the GDT to kernel stack.
    mov %ax, %ss        # Allow the CPU to access to kernel stack segment.

    jmp $0x08, $flush   # Return to kernel code segment.

flush:
    ret                 # Return back to Rust code.