// Project name: NOS (Null Operating System).
// Description: Monolithic UNIX-like operating system.
// Licence: GPL-3.0.
// Author: Alexander (@alkuzin).

//! x86 architecture-specific code main module.

use crate::log;

pub mod cpu;
pub mod drivers;
pub mod gdt;
pub mod io;

/// Initialize x86 architecture-specific part of the kernel.
pub fn init() {
    gdt::init();
    log::success!("Initialized Global Descriptor Table (GDT)");

    drivers::keyboard::init();
    log::success!("Initialized PS/2 keyboard driver");
}
