// Project name: NOS (Null Operating System).
// Description: Monolithic UNIX-like operating system.
// Licence: GPL-3.0.
// Author: Alexander (@alkuzin).

//! Architecture-specific code main module.

#[cfg(target_arch = "x86")]
pub mod x86;
