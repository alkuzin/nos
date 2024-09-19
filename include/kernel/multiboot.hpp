/**
 * The Null Operating System (NOS).
 * Copyright (C) 2024  Alexander (@alkuzin).
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

/**
 * @file  multiboot.hpp
 * @brief Contains multiboot information structures decalarations.
 * 
 * @details This header file includes functions related to the
 * physical and virtual memory managing.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   17.05.2024 
 */

#ifndef _NOS_KERNEL_MULTIBOOT_HPP_
#define _NOS_KERNEL_MULTIBOOT_HPP_


/* How many bytes from the start of the file we search for the header. */

#define MULTIBOOT_SEARCH                8192
#define MULTIBOOT_HEADER_ALIGN          4

#define MULTIBOOT_HEADER_MAGIC          0x1BADB002 /* The magic field should contain this. */
#define MULTIBOOT_BOOTLOADER_MAGIC      0x2BADB002 /* This should be in %eax. */
#define MULTIBOOT_MOD_ALIGN             0x00001000 /* Alignment of multiboot modules. */
#define MULTIBOOT_INFO_ALIGN            0x00000004 /* Alignment of the multiboot info structure. */

/* Flags set in the ’flags’ member of the multiboot header. */

#define MULTIBOOT_PAGE_ALIGN            0x00000001 /* Align all boot modules on i386 page (4KB) boundaries. */
#define MULTIBOOT_MEMORY_INFO           0x00000002 /* Must pass memory information to OS. */
#define MULTIBOOT_VIDEO_MODE            0x00000004 /* Must pass video information to OS. */
#define MULTIBOOT_AOUT_KLUDGE           0x00010000 /* This flag indicates the use of the address fields in the header. */

/* Flags to be set in the ’flags’ member of the multiboot info structure. */

#define MULTIBOOT_INFO_MEMORY           0x00000001 /* is there basic lower/upper memory information? */
#define MULTIBOOT_INFO_BOOTDEV          0x00000002 /* is there a boot device set? */
#define MULTIBOOT_INFO_CMDLINE          0x00000004 /* is the command-line defined? */
#define MULTIBOOT_INFO_MODS             0x00000008 /* are there modules to do something with? */

/* These next two are mutually exclusive */

#define MULTIBOOT_INFO_AOUT_SYMS        0x00000010 /* is there a symbol table loaded? */
#define MULTIBOOT_INFO_ELF_SHDR         0X00000020 /* is there an ELF section header table? */
#define MULTIBOOT_INFO_MEM_MAP          0x00000040 /* is there a full memory map? */
#define MULTIBOOT_INFO_DRIVE_INFO       0x00000080 /* Is there drive info? */
#define MULTIBOOT_INFO_CONFIG_TABLE     0x00000100 /* Is there a config table? */
#define MULTIBOOT_INFO_BOOT_LOADER_NAME 0x00000200 /* Is there a boot loader name? */
#define MULTIBOOT_INFO_APM_TABLE        0x00000400 /* Is there a APM table? */
#define MULTIBOOT_INFO_VBE_INFO         0x00000800 /* Is there video information? */
#define MULTIBOOT_INFO_FRAMEBUFFER_INFO 0x00001000

#ifndef ASM_FILE

typedef unsigned char      multiboot_uint8_t;
typedef unsigned short     multiboot_uint16_t;
typedef unsigned int       multiboot_uint32_t;
typedef unsigned long long multiboot_uint64_t;

struct multiboot_header {
  
  multiboot_uint32_t magic;     /* Must be MULTIBOOT_MAGIC - see above. */
  multiboot_uint32_t flags;     /* Feature flags. */
  multiboot_uint32_t checksum;  /* The above fields plus this one must equal 0 mod 2^32. */

  /* These are only valid if MULTIBOOT_AOUT_KLUDGE is set. */
  multiboot_uint32_t header_addr;
  multiboot_uint32_t load_addr;
  multiboot_uint32_t load_end_addr;
  multiboot_uint32_t bss_end_addr;
  multiboot_uint32_t entry_addr;

  /* These are only valid if MULTIBOOT_VIDEO_MODE is set. */
  multiboot_uint32_t mode_type;
  multiboot_uint32_t width;
  multiboot_uint32_t height;
  multiboot_uint32_t depth;
};

/* The symbol table for a.out. */
struct multiboot_aout_symbol_table
{
  multiboot_uint32_t tabsize;
  multiboot_uint32_t strsize;
  multiboot_uint32_t addr;
  multiboot_uint32_t reserved;
};
typedef struct multiboot_aout_symbol_table multiboot_aout_symbol_table_t;

/* The section header table for ELF. */
struct multiboot_elf_section_header_table {
    multiboot_uint32_t num;
    multiboot_uint32_t size;
    multiboot_uint32_t addr;
    multiboot_uint32_t shndx;
};
typedef struct multiboot_elf_section_header_table multiboot_elf_section_header_table_t;

struct multiboot_info {
    multiboot_uint32_t flags;       /* Multiboot info version number */
    multiboot_uint32_t mem_lower;   /* Available memory from BIOS */
    multiboot_uint32_t mem_upper;
    multiboot_uint32_t boot_device; /* "root" partition */
    multiboot_uint32_t cmdline;     /* Kernel command line */
    multiboot_uint32_t mods_count;  /* Boot-Module list */
    multiboot_uint32_t mods_addr;
    union {
        multiboot_aout_symbol_table_t aout_sym;
        multiboot_elf_section_header_table_t elf_sec;
    } u;

    multiboot_uint32_t mmap_length; /* Memory Mapping buffer */
    multiboot_uint32_t mmap_addr;
    
    multiboot_uint32_t drives_length; /* Drive Info buffer */
    multiboot_uint32_t drives_addr;

    multiboot_uint32_t config_table;      /* ROM configuration table */
    multiboot_uint32_t boot_loader_name;  /* Boot Loader Name */
    multiboot_uint32_t apm_table;         /* APM table */

    /* Video */
    multiboot_uint32_t vbe_control_info;
    multiboot_uint32_t vbe_mode_info;
    multiboot_uint16_t vbe_mode;
    multiboot_uint16_t vbe_interface_seg;
    multiboot_uint16_t vbe_interface_off;
    multiboot_uint16_t vbe_interface_len;

    multiboot_uint64_t framebuffer_addr;
    multiboot_uint32_t framebuffer_pitch;
    multiboot_uint32_t framebuffer_width;
    multiboot_uint32_t framebuffer_height;
    multiboot_uint8_t framebuffer_bpp;
#define MULTIBOOT_FRAMEBUFFER_TYPE_INDEXED 0
#define MULTIBOOT_FRAMEBUFFER_TYPE_RGB     1
#define MULTIBOOT_FRAMEBUFFER_TYPE_EGA_TEXT     2
    multiboot_uint8_t framebuffer_type;
    union {
        struct {
            multiboot_uint32_t framebuffer_palette_addr;
            multiboot_uint16_t framebuffer_palette_num_colors;
        };
        
        struct {
            multiboot_uint8_t framebuffer_red_field_position;
            multiboot_uint8_t framebuffer_red_mask_size;
            multiboot_uint8_t framebuffer_green_field_position;
            multiboot_uint8_t framebuffer_green_mask_size;
            multiboot_uint8_t framebuffer_blue_field_position;
            multiboot_uint8_t framebuffer_blue_mask_size;
        };
    };
};
typedef struct multiboot_info multiboot_info_t;

struct multiboot_color {
    multiboot_uint8_t red;
    multiboot_uint8_t green;
    multiboot_uint8_t blue;
};

struct multiboot_mmap_entry {
    multiboot_uint32_t size;
    multiboot_uint64_t addr;
    multiboot_uint64_t len;
#define MULTIBOOT_MEMORY_AVAILABLE        1
#define MULTIBOOT_MEMORY_RESERVED         2
#define MULTIBOOT_MEMORY_ACPI_RECLAIMABLE 3
#define MULTIBOOT_MEMORY_NVS              4
#define MULTIBOOT_MEMORY_BADRAM           5
    multiboot_uint32_t type;
} __attribute__((packed));

typedef struct multiboot_mmap_entry multiboot_memory_map_t;

struct multiboot_mod_list {
    /* the memory used goes from bytes ’mod_start’ to ’mod_end-1’ inclusive */   
    multiboot_uint32_t mod_start;   
    multiboot_uint32_t mod_end;
    multiboot_uint32_t cmdline; /* Module command line */    
    multiboot_uint32_t pad; /* padding to take it to 16 bytes (must be zero) */   
};

typedef struct multiboot_mod_list multiboot_module_t;

/* APM BIOS info. */
struct multiboot_apm_info {
    multiboot_uint16_t version;
    multiboot_uint16_t cseg;
    multiboot_uint32_t offset;
    multiboot_uint16_t cseg_16;
    multiboot_uint16_t dseg;
    multiboot_uint16_t flags;
    multiboot_uint16_t cseg_len;
    multiboot_uint16_t cseg_16_len;
    multiboot_uint16_t dseg_len;
};

#endif /* ! ASM_FILE */

typedef multiboot_info_t multiboot_t;

#endif /* _NOS_KERNEL_MULTIBOOT_HPP_ */