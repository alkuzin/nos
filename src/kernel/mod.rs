// Project name: NOS (Null Operating System).
// Description: Monolithic UNIX-like operating system.
// Licence: GPL-3.0.
// Author: Alexander (@alkuzin).

//! Main kernel module. Responsible for initializing kernel components.

use crate::{log, multiboot::MultibootInfo};

/// Initialize kernel.
///
/// # Parameters
/// - `boot_info` - given multiboot info structure.
pub fn init(_boot_info: &MultibootInfo) {
    // Initialize kernel logger.
    log::init();
    log::success!("Initialized kernel logger.");

    // TODO: implement CPU info struct.
    // TODO: display CPU info + check whether OS running under hypervisor.
}
