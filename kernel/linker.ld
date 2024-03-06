/* boot - boot loader entry point */
ENTRY (boot) 
SECTIONS{
        . =0x00100000; /* setting memory address to 0x00100000 */
        .text : {
              *(.text) /* place all the code in this sevtion */
        }
		/* align read-only data (such as const variables) boundary */
        .rodata ALIGN (0x1000) : { 
              *(.data)
        }
		/* global/static variables */
		/* linker puts all unitialized data in this section */
        .bss : {
              sbss = .;
              *(COMMON) /* for shared data across multiple files */
              *(.bss)
              ebss = .;
        }
}
