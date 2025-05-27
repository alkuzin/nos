// Project name: NOS (Null Operating System).
// Description: Monolithic UNIX-like operating system.
// Licence: GPL-3.0.
// Author: Alexander (@alkuzin).

//! Global Descriptor Table module.
//!
//! # Description
//! The Global Descriptor Table (GDT) is a critical data structure used in x86
//! architecture for memory management and protection. It defines the
//! characteristics of various memory segments, allowing the CPU to manage
//! memory access and enforce protection mechanisms.

use crate::log;

/// GDT segment structure.
#[derive(Debug, Default, Clone, Copy)]
#[repr(C, packed)]
pub struct Entry {
    /// Maximum addressable unit.
    pub limit: u16,
    /// Linear address where the segment begins.
    pub base_low: u16,
    /// Linear address where the segment begins.
    pub base_mid: u8,
    /// Privileges of segment.
    pub access: u8,
    /// Segment mode.
    pub flags: u8,
    /// Linear address where the segment begins.
    pub base_high: u8,
}

impl Entry {
    /// Construct new GDT entry.
    ///
    /// # Parameters
    /// - `base`   - given linear address where the segment begins.
    /// - `limit`  - given maximum addressable unit.
    /// - `access` - given segment access byte.
    /// - `flags`  - given segment flags.
    pub fn new(base: u32, limit: u32, access: u8, flags: u8) -> Self {
        let entry_base_low = (base & 0xFFFF) as u16;
        let entry_base_mid = ((base >> 0x10) & 0xFF) as u8;
        let entry_base_high = ((base >> 0x18) & 0xFF) as u8;
        let entry_limit = (limit & 0xFFFF) as u16;
        let mut entry_flags = ((limit >> 0x10) & 0x0F) as u8;
        entry_flags |= flags & 0xF0;

        Entry {
            base_high: entry_base_high,
            base_low: entry_base_low,
            base_mid: entry_base_mid,
            limit: entry_limit,
            flags: entry_flags,
            access,
        }
    }
}

/// GDT pointer.
#[derive(Debug)]
#[repr(C, packed)]
pub struct Pointer {
    /// GDT size - 1.
    pub size: u16,
    /// Linear address of GDT.
    pub offset: u32,
}

/// GDT segment offsets enumeration.
#[derive(Debug)]
#[repr(u8)]
pub enum Segment {
    Null = 0x00,
    KernelCode = 0x08,
    KernelData = 0x10,
    KernelStack = 0x18,
    UserCode = 0x20,
    UserData = 0x28,
    UserStack = 0x30,
}

/// Access bytes enumeration.
#[derive(Debug)]
#[repr(u8)]
pub enum Access {
    KernelCode = 0x9A,
    KernelData = 0x93,
    KernelStack = 0x97,
    UserCode = 0xFA,
    UserData = 0xF2,
    UserStack = 0xF7,
}

fn access_to_str(access: u8) -> &'static str {
    match access {
        0x00 => "Null",
        0x9A => "Kernel code",
        0x93 => "Kernel data",
        0x97 => "Kernel stack",
        0xFA => "User code",
        0xF2 => "User data",
        0xF7 => "User stack",
        _ => "Unknown",
    }
}

/// GDT pointer physical address.
const GDT_BASE: u32 = 0x800;

/// Number of GDT entries.
const GDT_ENTRIES: usize = 7;

/// Empty entry.
const NULL_ENTRY: Entry = Entry {
    limit: 0,
    base_low: 0,
    base_mid: 0,
    access: 0,
    flags: 0,
    base_high: 0,
};

/// Global Descriptor Table.
static mut GDT: [Entry; GDT_ENTRIES] = [NULL_ENTRY; GDT_ENTRIES];

/// Global Descriptor Table pointer.
static mut GDT_PTR: *mut Pointer = GDT_BASE as *mut Pointer;

/// Set GDT entries.
fn set_entries() {
    // 32-bit protected mode segment.
    const FLAGS: u8 = 0xCF;
    const BASE: u32 = 0x00000000;
    const LIMIT: u32 = 0xFFFFFFFF;

    let null = Entry::default();
    let kern_code = Entry::new(BASE, LIMIT, Access::KernelCode as u8, FLAGS);
    let kern_data = Entry::new(BASE, LIMIT, Access::KernelData as u8, FLAGS);
    let kern_stack = Entry::new(BASE, LIMIT, Access::KernelStack as u8, FLAGS);
    let user_code = Entry::new(BASE, LIMIT, Access::UserCode as u8, FLAGS);
    let user_data = Entry::new(BASE, LIMIT, Access::UserData as u8, FLAGS);
    let user_stack = Entry::new(BASE, LIMIT, Access::UserStack as u8, FLAGS);

    unsafe {
        // (Null descriptor) should always contain no data.
        GDT[0] = null;

        // Kernel space segments.
        GDT[1] = kern_code;
        GDT[2] = kern_data;
        GDT[3] = kern_stack;

        // User space segments.
        GDT[4] = user_code;
        GDT[5] = user_data;
        GDT[6] = user_stack;
    }
}

// Set GDT pointer.
fn set_pointer() {
    unsafe {
        let gdt_ptr = GDT_PTR.as_mut().unwrap();
        gdt_ptr.size = (size_of::<Entry>() * GDT_ENTRIES - 1) as u16;
        gdt_ptr.offset = (&raw const GDT as *const _) as u32;
    }
}

unsafe extern "C" {
    /// Flush out the old GDT and install the new changes.
    ///
    /// # Parameters
    /// - `ptr` - given new GDT pointer to update.
    fn gdt_flush(ptr: u32);
}

/// Print GDT related info for debug.
#[doc(hidden)]
fn print_gdt() {
    let gdt_ptr = unsafe { GDT_PTR.as_ref().unwrap() };
    let size = gdt_ptr.size;
    let offset = gdt_ptr.offset;

    log::info!("Setting Global Descriptor Table (GDT):");
    log::info!("GDT pointer: <{:#?}>", unsafe { GDT_PTR });
    log::info!("GDT size: {} bytes", size);
    log::info!("GDT offset: <{:#08x}>", offset);
    log::info!("Set {} GDT entries:", GDT_ENTRIES);

    for entry in unsafe { GDT }.iter() {
        log::info!(
            "Access: {:#08X}  Flags: {:#08X}  Segment: {}",
            entry.access,
            entry.flags,
            access_to_str(entry.access),
        );
    }
}

/// Initialize Global Descriptor Table.
pub fn init() {
    set_entries();
    set_pointer();

    unsafe {
        // Update GDT.
        gdt_flush(GDT_BASE);
    }

    print_gdt();
}
