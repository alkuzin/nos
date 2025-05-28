// Project name: NOS (Null Operating System).
// Description: Monolithic UNIX-like operating system.
// Licence: GPL-3.0.
// Author: Alexander (@alkuzin).

//! Main kernel module. Responsible for initializing kernel components.

pub mod gfx;

use crate::{config, hal, log, multiboot::MultibootInfo, printk};
use core::str;

/// Display CPU related info.
fn display_cpu_info() {
    // Display basic CPU info.
    let cpu = hal::cpu::get_cpu_info();
    let vendor_id = str::from_utf8(&cpu.vendor_id).unwrap();
    let brand = str::from_utf8(&cpu.brand).unwrap();

    log::info!("Found CPU:");
    log::info!("CPU vendor: {}", vendor_id);
    log::info!("CPU brand: {}", brand);
    log::info!("CPU family: {}", cpu.family);
    log::info!("CPU model: {}", cpu.model);
    log::info!("CPU max CPUID: {}", cpu.max_cpuid);

    // Display virtualization extension info.
    if hal::cpu::is_support_virtualization() {
        log::info!("Virtualization is supported");
    } else {
        log::info!("Virtualization is not supported");
    }

    // Display hypervisor info.
    if let Some(hypervisor_id) = hal::cpu::get_hypervisor_id() {
        let id = str::from_utf8(&hypervisor_id).unwrap();
        log::info!("Running under hypervisor: {}", id);
    }
}

/// Display OS related info.
fn display_os_info() {
    let name = config::NAME;
    let version = config::VERSION;
    let description = config::DESCRIPTION;
    let license = config::LICENSE;
    let license_details = config::LICENSE_DETAILS;
    let repository = config::REPOSITORY;
    let authors = config::AUTHORS;

    printk!("\n{} ({}) - {}", name, version, description);
    printk!("Repository: {}", repository);
    printk!("Created by {}", authors);
    printk!("Running under {} license.\n{}", license, license_details);
}

/// Initialize kernel.
///
/// # Parameters
/// - `boot_info` - given multiboot info structure.
pub fn init(boot_info: &MultibootInfo) {
    log::init_serial_writer();
    log::success!("Initialized kernel serial logger");

    let fb = gfx::init(boot_info);
    log::success!("Initialized kernel graphics");

    log::init_terminal_writer(fb.clone());
    log::success!("Initialized kernel terminal logger");

    display_cpu_info();
    hal::init();
    log::success!("Initialized architecture-specific part of the kernel");

    log::success!("Finished setting up OS");
    display_os_info();
}
