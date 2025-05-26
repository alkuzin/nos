// Project name: NOS (Null Operating System).
// Description: Monolithic UNIX-like operating system.
// Licence: GPL-3.0.
// Author: Alexander (@alkuzin).

//! Main kernel module. Responsible for initializing kernel components.

pub mod gfx;

use crate::{log, multiboot::MultibootInfo};

/// Initialize kernel.
///
/// # Parameters
/// - `boot_info` - given multiboot info structure.
pub fn init(boot_info: &MultibootInfo) {
    // Initialize kernel logger.
    log::init_serial_writer();
    log::success!("Initialized kernel serial logger");

    let fb = gfx::init(boot_info);
    log::success!("Initialized kernel graphics");

    log::init_terminal_writer(fb.clone());
    log::success!("Initialized kernel terminal logger");

    // TODO: implement CPU info struct.
    // TODO: display CPU info + check whether OS running under hypervisor.
}
