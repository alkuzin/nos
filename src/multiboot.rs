// Project name: NOS (Null Operating System).
// Description: Monolithic UNIX-like operating system.
// Licence: GPL-3.0.
// Author: Alexander (@alkuzin).

//! Contains multiboot specification related declarations.

use core::fmt;

/// Number of bytes from the start of the file
/// to search for the header.
pub const MULTIBOOT_SEARCH: u32 = 8192;
pub const MULTIBOOT_HEADER_ALIGN: u32 = 4;

/// The magic field should contain this.
pub const MULTIBOOT_HEADER_MAGIC: u32 = 0x1BADB002;

/// This should be in %eax.
pub const MULTIBOOT_BOOTLOADER_MAGIC: u32 = 0x2BADB002;

/// Alignment of multiboot modules.
pub const MULTIBOOT_MOD_ALIGN: u32 = 0x00001000;

/// Alignment of the multiboot info structure.
pub const MULTIBOOT_INFO_ALIGN: u32 = 0x00000004;

// Flags set in the ’flags’ member of the multiboot header.

/// Align all boot modules on i386 page (4KB) boundaries.
pub const MULTIBOOT_PAGE_ALIGN: u32 = 0x00000001;

/// Must pass memory information to OS.
pub const MULTIBOOT_MEMORY_INFO: u32 = 0x00000002;

/// Must pass video information to OS.
pub const MULTIBOOT_VIDEO_MODE: u32 = 0x00000004;

/// This flag indicates the use of the address fields in the header.
pub const MULTIBOOT_AOUT_KLUDGE: u32 = 0x00010000;

// Flags to be set in the ’flags’ member of the multiboot info structure.

/// Is there basic lower/upper memory information?
pub const MULTIBOOT_INFO_MEMORY: u32 = 0x00000001;

/// Is there a boot device set?
pub const MULTIBOOT_INFO_BOOTDEV: u32 = 0x00000002;

/// Is the command-line defined?
pub const MULTIBOOT_INFO_CMDLINE: u32 = 0x00000004;

/// Are there modules to do something with?
pub const MULTIBOOT_INFO_MODS: u32 = 0x00000008;

// These next two are mutually exclusive.

/// is there a symbol table loaded?
pub const MULTIBOOT_INFO_AOUT_SYMS: u32 = 0x00000010;

/// is there an ELF section header table?
pub const MULTIBOOT_INFO_ELF_SHDR: u32 = 0x00000020;

/// is there a full memory map?
pub const MULTIBOOT_INFO_MEM_MAP: u32 = 0x00000040;

/// Is there drive info?
pub const MULTIBOOT_INFO_DRIVE_INFO: u32 = 0x00000080;

/// Is there a config table?
pub const MULTIBOOT_INFO_CONFIG_TABLE: u32 = 0x00000100;

/// Is there a boot loader name?
pub const MULTIBOOT_INFO_BOOT_LOADER_NAME: u32 = 0x00000200;

/// Is there a APM table?
pub const MULTIBOOT_INFO_APM_TABLE: u32 = 0x00000400;

/// Is there video information?
pub const MULTIBOOT_INFO_VBE_INFO: u32 = 0x00000800;
pub const MULTIBOOT_INFO_FRAMEBUFFER_INFO: u32 = 0x00001000;

pub type MultibootU8 = u8;
pub type MultibootU16 = u16;
pub type MultibootU32 = u32;
pub type MultibootU64 = u64;

#[derive(Debug, Clone, Copy)]
#[repr(C)]
pub struct MultibootHeader {
    /// Must be MULTIBOOT_MAGIC - see above.
    pub magic: MultibootU32,
    /// Feature flags.
    pub flags: MultibootU32,
    /// The above fields plus this one must equal 0 mod 2^32.
    pub checksum: MultibootU32,
    /// These are only valid if MULTIBOOT_AOUT_KLUDGE is set.
    pub header_addr: MultibootU32,
    pub load_addr: MultibootU32,
    pub load_end_addr: MultibootU32,
    pub bss_end_addr: MultibootU32,
    pub entry_addr: MultibootU32,
    /// These are only valid if MULTIBOOT_VIDEO_MODE is set.
    pub mode_type: MultibootU32,
    pub width: MultibootU32,
    pub height: MultibootU32,
    pub depth: MultibootU32,
}

/// The symbol table for a.out.
#[derive(Debug, Default, Clone, Copy)]
#[repr(C)]
pub struct MultibootAOutSymbolTable {
    pub tabsize: MultibootU32,
    pub strsize: MultibootU32,
    pub addr: MultibootU32,
    pub reserved: MultibootU32,
}

/// The section header table for ELF.
#[derive(Debug, Clone, Copy)]
#[repr(C)]
pub struct MultibootELFSectionHeaderTable {
    pub num: MultibootU32,
    pub size: MultibootU32,
    pub addr: MultibootU32,
    pub shndx: MultibootU32,
}

/// Union for Multiboot symbol tables.
#[derive(Clone, Copy)]
#[repr(C)]
pub union MultibootSymbolTableUnion {
    pub aout_sym: MultibootAOutSymbolTable,
    pub elf_sec: MultibootELFSectionHeaderTable,
}

impl fmt::Debug for MultibootSymbolTableUnion {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        unsafe {
            write!(
                f,
                "MultibootSymbolTableUnion {{ aout_sym: {:?} }}",
                self.aout_sym
            )?;
        }
        Ok(())
    }
}

impl Default for MultibootSymbolTableUnion {
    fn default() -> Self {
        MultibootSymbolTableUnion {
            aout_sym: MultibootAOutSymbolTable::default(),
        }
    }
}

#[derive(Debug, Default, Clone, Copy)]
#[repr(u8)]
pub enum MultibootFramebufferType {
    Indexed = 0,
    #[default]
    Rgb = 1,
    EgaText = 2,
}

/// Struct for framebuffer palette information.
#[derive(Debug, Default, Clone, Copy)]
#[repr(C)]
pub struct FramebufferPalette {
    pub addr: MultibootU32,
    pub num_colors: MultibootU16,
}

/// Struct for framebuffer RGB information.
#[derive(Debug, Default, Clone, Copy)]
#[repr(C)]
pub struct FramebufferRGB {
    pub red_field_position: MultibootU8,
    pub red_mask_size: MultibootU8,
    pub green_field_position: MultibootU8,
    pub green_mask_size: MultibootU8,
    pub blue_field_position: MultibootU8,
    pub blue_mask_size: MultibootU8,
}

#[derive(Clone, Copy)]
#[repr(C)]
pub union FramebufferUnion {
    pub palette: FramebufferPalette,
    pub rgb: FramebufferRGB,
}

impl fmt::Debug for FramebufferUnion {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        unsafe {
            write!(f, "FramebufferUnion {{ rgb: {:?} }}", self.rgb)?;
        }
        Ok(())
    }
}

impl Default for FramebufferUnion {
    fn default() -> Self {
        FramebufferUnion {
            rgb: FramebufferRGB::default(),
        }
    }
}

#[derive(Debug, Default, Clone, Copy)]
#[repr(C)]
pub struct MultibootInfo {
    /// Multiboot info version number.
    pub flags: MultibootU32,
    /// Available memory from BIOS.
    pub mem_lower: MultibootU32,
    pub mem_upper: MultibootU32,
    /// "Root" partition.
    pub boot_device: MultibootU32,
    /// Kernel command line.
    pub cmdline: MultibootU32,
    /// Boot-Module list.
    pub mods_count: MultibootU32,
    pub mods_addr: MultibootU32,
    pub u: MultibootSymbolTableUnion,
    /// Memory Mapping buffer.
    pub mmap_length: MultibootU32,
    pub mmap_addr: MultibootU32,
    /// Drive Info buffer.
    pub drives_length: MultibootU32,
    pub drives_addr: MultibootU32,
    // ROM configuration table.
    pub config_table: MultibootU32,
    // Boot Loader Name.
    pub boot_loader_name: MultibootU32,
    // APM table.
    pub apm_table: MultibootU32,
    /// Video.
    pub vbe_control_info: MultibootU32,
    pub vbe_mode_info: MultibootU32,
    pub vbe_mode: MultibootU16,
    pub vbe_interface_seg: MultibootU16,
    pub vbe_interface_off: MultibootU16,
    pub vbe_interface_len: MultibootU16,
    pub framebuffer_addr: MultibootU64,
    pub framebuffer_pitch: MultibootU32,
    pub framebuffer_width: MultibootU32,
    pub framebuffer_height: MultibootU32,
    pub framebuffer_bpp: MultibootU8,
    pub framebuffer_type: MultibootFramebufferType,
    pub framebuffer_union: FramebufferUnion,
}

#[derive(Debug, Clone, Copy)]
#[repr(C)]
pub struct MultibootColor {
    pub red: MultibootU8,
    pub green: MultibootU8,
    pub blue: MultibootU8,
}

/// Multiboot memory map entry type.
#[derive(Debug, Clone, Copy)]
#[repr(u32)]
pub enum MultibootMemoryType {
    Available = 1,
    Reserved = 2,
    AcpiReclaimable = 3,
    Nvs = 4,
    BadRam = 5,
}

/// Multiboot memory map info.
#[derive(Debug, Clone, Copy)]
#[repr(C, packed)]
pub struct MultibootMmapEntry {
    pub size: MultibootU32,
    pub addr: MultibootU64,
    pub len: MultibootU64,
    pub mtype: MultibootMemoryType,
}

/// Multiboot module info.
#[derive(Debug, Clone, Copy)]
#[repr(C)]
pub struct MultibootModList {
    /// The memory used goes from bytes ’mod_start’ to ’mod_end-1’ inclusive.
    pub mod_start: MultibootU32,
    pub mod_end: MultibootU32,
    /// Module command line.
    pub cmdline: MultibootU32,
    /// Padding to take it to 16 bytes (must be zero).
    pub pad: MultibootU32,
}

/// APM BIOS info.
#[derive(Debug, Clone, Copy)]
#[repr(C)]
pub struct MultibootApmInfo {
    pub version: MultibootU16,
    pub cseg: MultibootU16,
    pub offset: MultibootU32,
    pub cseg_16: MultibootU16,
    pub dseg: MultibootU16,
    pub flags: MultibootU16,
    pub cseg_len: MultibootU16,
    pub cseg_16_len: MultibootU16,
    pub dseg_len: MultibootU16,
}
