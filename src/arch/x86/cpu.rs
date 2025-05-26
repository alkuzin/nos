// Project name: NOS (Null Operating System).
// Description: Monolithic UNIX-like operating system.
// Licence: GPL-3.0.
// Author: Alexander (@alkuzin).

//! CPU data extraction declarations.

use crate::hal::cpu::{CPUInfo, VENDOR_ID_SIZE};
use core::{arch::asm, ptr};

/// CPUID instruction result struct.
#[derive(Default, Debug)]
pub struct CpuidResult {
    /// EAX register.
    pub eax: u32,
    /// EBX register.
    pub ebx: u32,
    /// ECX register.
    pub ecx: u32,
    /// EDX register.
    pub edx: u32,
}

/// CPUID instruction wrapper.
///
/// # Parameters
/// - `leaf` - given category of CPU information to gather.
///
/// # Returns
/// - Set of registers with CPU information.
pub fn cpuid(leaf: u32) -> CpuidResult {
    let mut result = CpuidResult::default();

    unsafe {
        asm!(
            "cpuid",
            inout("eax") leaf => result.eax,
            lateout("ebx") result.ebx,
            lateout("ecx") result.ecx,
            lateout("edx") result.edx,
        );
    }

    result
}

/// Set basic CPU info.
///
/// # Parameters
/// - `info` - given struct to store CPU gathered info.
fn set_cpuid_basic_info(info: &mut CPUInfo) {
    // Get specific CPU info.
    let cpu_info = cpuid(0);

    // Extracting vendor ID assuming that byte order is little endian.
    info.vendor_id[0..4].copy_from_slice(&cpu_info.ebx.to_le_bytes());
    info.vendor_id[4..8].copy_from_slice(&cpu_info.edx.to_le_bytes());
    info.vendor_id[8..12].copy_from_slice(&cpu_info.ecx.to_le_bytes());

    // Extracting max CPUID leaf count.
    info.max_cpuid = cpu_info.eax;
}

/// Set additional processor info.
///
/// # Parameters
/// - `info` - given struct to store CPU gathered info.
fn set_cpuid_processor_info(info: &mut CPUInfo) {
    // Get specific CPU info.
    let cpu_info = cpuid(1);

    let model = (cpu_info.eax >> 4) & 0x0F;
    let family = (cpu_info.eax >> 8) & 0x0F;
    let ext_model  = (cpu_info.eax >> 16) & 0x0F;
    let ext_family = (cpu_info.eax >> 20) & 0xFF;

    info.stepping = cpu_info.eax & 0x0F;
    info.features = cpu_info.edx;

    // Set actual CPU model.
    info.model = if family == 6 || family == 15 {
        (ext_model << 4) + model
    }
    else {
        model
    };

    // Set actual CPU family.
    info.family = family;

    if family == 15 {
        info.family += ext_family;
    }
}

/// Set CPU brand.
///
/// # Parameters
/// - `info` - given struct to store CPU gathered info.
fn set_cpuid_brand(info: &mut CPUInfo) {
    let mut brand = [0u8; 64];

    // Retrieve the three parts of the CPU brand.
    for leaf in 0x80000002..=0x80000004 {
        let cpu_info = cpuid(leaf);
        let part = [cpu_info.eax, cpu_info.ebx, cpu_info.ecx, cpu_info.edx];

        // Copy the data into the brand array.
        let start_index = (leaf - 0x80000002) * 16;

        for (i, &value) in part.iter().enumerate() {
            let offset = start_index as usize + i * 4;
            let value = &value as *const u32 as *const u8;

            unsafe {
                ptr::copy_nonoverlapping(value, &mut brand[offset], 4);
            }
        }
    }

    info.brand = brand;
}

/// Check whether CPU supporting virtualization.
///
/// # Returns
/// - `true`  - if CPU supporting virtualization.
/// - `false` - otherwise.
pub fn is_support_virtualization() -> bool {
    // Get specific CPU info.
    let cpu_info = cpuid(1);
    (cpu_info.ecx & (1 << 5)) != 0x0
}

/// Check whether OS running on top of hypervisor.
///
/// # Returns
/// - `true`  - if OS running on top of hypervisor.
/// - `false` - otherwise.
pub fn is_hypervisor_present() -> bool {
    // Get specific CPU info.
    let cpu_info = cpuid(1);
    (cpu_info.ecx & (1 << 31)) != 0x0
}

/// Get hypervisor identifier.
///
/// # Returns
/// - `Hypervisor ID` - in case of success.
/// - `None`          - otherwise.
pub fn get_hypervisor_id() -> Option<[u8; VENDOR_ID_SIZE]> {
    // Check whether OS running on real hardware.
    if !is_hypervisor_present() {
        return None
    }

    // Get specific CPU info.
    let cpu_info = cpuid(0x40000000);
    let mut hypervisor_id = [0u8; VENDOR_ID_SIZE];

    // Extracting vendor ID assuming that byte order is little endian.
    hypervisor_id[0..4].copy_from_slice(&cpu_info.ebx.to_le_bytes());
    hypervisor_id[4..8].copy_from_slice(&cpu_info.ecx.to_le_bytes());
    hypervisor_id[8..12].copy_from_slice(&cpu_info.edx.to_le_bytes());

    Some(hypervisor_id)
}

/// Get information about CPU.
///
/// # Returns
/// - CPU information struct.
pub fn get_cpu_info() -> CPUInfo {
    let mut info = CPUInfo::default();

    set_cpuid_basic_info(&mut info);
    set_cpuid_processor_info(&mut info);
    set_cpuid_brand(&mut info);

    info
}
