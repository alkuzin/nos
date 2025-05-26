/**
* Project name: NOS (Null Operating System).
* Description: Monolithic UNIX-like operating system.
* Licence: GPL-3.0.
* Author: Alexander (@alkuzin).
*/

/* Bootloader entry point. */
ENTRY(boot)
SECTIONS
{
    /* Conventional place for kernels to be loaded at by the bootloader.*/
    base_address = 0xC0000000;
    . = 1M + base_address;

    kernel_virt_begin = .;
    kernel_phys_begin = kernel_virt_begin - base_address;

    .text ALIGN(4K) : AT(ADDR(.text) - base_address)
    {
        *(.multiboot)
        *(.text)        /* All code located in this section.*/
    }

    /* Align read-only data (such as const variables) boundary.*/
    .rodata ALIGN(4K) : AT(ADDR(.rodata) - base_address)
    {
        *(.rodata)
    }

    /* Read/write data (initialized).*/
    .data ALIGN(4K) : AT(ADDR(.data) - base_address)
    {
        *(.data)
    }

    /* Global/static variables (unitialized).*/
    .bss ALIGN(4K) : AT(ADDR(.bss) - base_address)
    {
        *(COMMON)
        *(.bss)
    }

    kernel_virt_end = .;
    kernel_phys_end = kernel_virt_end - base_address;
}