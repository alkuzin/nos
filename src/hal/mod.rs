// Project name: NOS (Null Operating System).
// Description: Monolithic UNIX-like operating system.
// Licence: GPL-3.0.
// Author: Alexander (@alkuzin).

//! HAL (Hardware Abstraction Layer) main module.

use crate::arch;

pub mod cpu;
pub mod uart;
pub mod keyboard;

/// Initialize architecture-specific part of the kernel.
pub fn init() {
    #[cfg(target_arch = "x86")]
    arch::x86::init();
}
