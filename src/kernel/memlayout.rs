// Project name: NOS (Null Operating System).
// Description: Monolithic UNIX-like operating system.
// Licence: GPL-3.0.
// Author: Alexander (@alkuzin).

//! Declares kernel memory layout.

// Kernel memory layout variables (declared in linker file).
unsafe extern "C" {
    static kernel_phys_begin: u32;
    static kernel_phys_end: u32;
    static kernel_virt_begin: u32;
    static kernel_virt_end: u32;
    static base_address: u32;
    static stack_bottom: u32;
    static stack_top: u32;
}

/// Physical address of memory begin.
pub const MEM_START_PADDR: u32 = 0x00000000;

/// Get kernel begin.
///
/// # Returns
/// - Kernel begin physical address.
#[inline(always)]
pub fn kernel_begin_paddr() -> u32 {
    unsafe { (&kernel_phys_begin as *const _) as u32 }
}

/// Get kernel end.
///
/// # Returns
/// - Kernel end physical address.
#[inline(always)]
pub fn kernel_end_paddr() -> u32 {
    unsafe { (&kernel_phys_end as *const _) as u32 }
}

/// Get kernel begin.
///
/// # Returns
/// - Kernel begin virtual address.
#[inline(always)]
pub fn kernel_begin_vaddr() -> u32 {
    unsafe { (&kernel_virt_begin as *const _) as u32 }
}

/// Get kernel end.
///
/// # Returns
/// - Kernel end virtual address.
#[inline(always)]
pub fn kernel_end_vaddr() -> u32 {
    unsafe { (&kernel_virt_end as *const _) as u32 }
}

/// Get kernel base address.
///
/// # Returns
/// - Kernel virtual base address.
#[inline(always)]
pub fn base_vaddr() -> u32 {
    unsafe { (&base_address as *const _) as u32 }
}

/// Get kernel size.
///
/// # Returns
/// - Kernel size in bytes.
#[inline(always)]
pub fn kernel_size() -> u32 {
    kernel_end_paddr() - kernel_begin_paddr()
}

/// Get stack bottom.
///
/// # Returns
/// - Virtual address of the bottom of the stack.
#[inline(always)]
pub fn stack_bottom_vaddr() -> usize {
    unsafe { &stack_bottom as *const _ as usize }
}

/// Get stack top.
///
/// # Returns
/// - Virtual address of the top of the stack.
#[inline(always)]
pub fn stack_top_vaddr() -> usize {
    unsafe { &stack_top as *const _ as usize }
}

/// Get kernel stack size.
///
/// # Returns
/// - Kernel stack size in bytes.
#[inline(always)]
pub fn stack_size() -> usize {
    stack_top_vaddr() - stack_bottom_vaddr()
}
