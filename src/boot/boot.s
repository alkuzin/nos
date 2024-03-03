global boot
extern kmain

MAGIC 		equ 0x1BADB002			; BIOS recognize as a kernel
FLAGS 		equ (1 << 0 | 1 << 1)
CHECKSUM 	equ -(MAGIC + FLAGS)

section .text
	align 4

multiboot_header:
	dd MAGIC
	dd FLAGS
	dd CHECKSUM

boot:
	call kmain
	cli							; (clear interrupts) disables hardware interrupts

halt:
	hlt							; this instruction halts the CPU 
	jmp halt

section .bss
	align 4
