;MIT License

;Copyright (c) 2024 Alexander (@alkuzin)

;Permission is hereby granted, free of charge, to any person obtaining a copy
;of this software and associated documentation files (the "Software"), to deal
;in the Software without restriction, including without limitation the rights
;to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
;copies of the Software, and to permit persons to whom the Software is
;furnished to do so, subject to the following conditions:

;The above copyright notice and this permission notice shall be included in all
;copies or substantial portions of the Software.

;THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
;IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
;FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
;AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
;LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
;OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
;SOFTWARE.

global boot  ; make extern boot loader entry point
extern kmain ; declaring `kmain` label as an external function

; Magic number is a value that BIOS recognize as a kernel
MAGIC equ 0x1BADB002 

; flags can control various functions of the BIOS such as:
; enabling/disabling specific hardware components
; setting up boot options
; adjusting power management settings
FLAGS equ (1 << 0 | 1 << 1) ; indicates a bootable device

; the purpose of checksum is to ensure OS stability & security
; by detecting any unauthorised changes to the BIOS firmware
CHECKSUM equ -(MAGIC + FLAGS)

; define the multiboot header structure, including 4 double-word (4-byte) values
section .text ; .text section contains executable instructions of a program
	align 4 ; aligns next data element/instruction that is multiple of 4 bytes

multiboot_header:
	dd MAGIC	 ; declare double word (32-bit) of Magic number
	dd FLAGS     ; declare double word (32-bit) of Magic number flags
	dd CHECKSUM  ; declare double word (32-bit) of Magic number checksum

; boot loader entry point
boot:
	call kmain ; call kernel entry point 'kmain' from kernel/lernel.c
	cli ; (clear interrupts) disables hardware interrupts

; infinite loop
halt:
	hlt	; this instruction halts the CPU 
	jmp halt

; .bss section is used for declaring statically allocated variables
; that are not initialized with a value
section .bss
	align 4 ; aligns next data element/instruction that is multiple of 4 bytes
