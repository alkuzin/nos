// Project name: NOS (Null Operating System).
// Description: Monolithic UNIX-like operating system.
// Licence: GPL-3.0.
// Author: Alexander (@alkuzin).

//! CPU related architecture-independent declarations.

use crate::arch;

/// CPU vendor identifier size.
pub const VENDOR_ID_SIZE: usize = 32;

/// CPU brand size.
pub const BRAND_SIZE: usize = 64;

/// CPU information struct.
#[derive(Debug)]
pub struct CPUInfo {
    /// Vendor identifier.
    pub vendor_id: [u8; VENDOR_ID_SIZE],
    /// CPU brand.
    pub brand: [u8; BRAND_SIZE],
    /// CPU family.
    pub family: u32,
    /// CPU model.
    pub model: u32,
    /// CPU stepping.
    pub stepping: u32,
    /// CPU features (bitmask).
    pub features: u32,
    /// Maximum CPUID function supported.
    pub max_cpuid: u32,
}

impl Default for CPUInfo {
    /// Construct default `CPUInfo` object.
    ///
    /// # Returns
    /// - New default `CPUInfo` object.
    fn default() -> Self {
        Self {
            vendor_id: [0u8; VENDOR_ID_SIZE],
            brand: [0u8; BRAND_SIZE],
            family: 0,
            model: 0,
            stepping: 0,
            features: 0,
            max_cpuid: 0,
        }
    }
}

/// Check whether CPU supporting virtualization.
///
/// # Returns
/// - `true`  - if CPU supporting virtualization.
/// - `false` - otherwise.
pub fn is_support_virtualization() -> bool {
    #[cfg(target_arch = "x86")]
    arch::x86::cpu::is_support_virtualization()
}

/// Check whether OS running on top of hypervisor.
///
/// # Returns
/// - `true`  - if OS running on top of hypervisor.
/// - `false` - otherwise.
fn is_hypervisor_present() -> bool {
    #[cfg(target_arch = "x86")]
    arch::x86::cpu::is_hypervisor_present()
}

/// Get hypervisor identifier.
///
/// # Returns
/// - `Hypervisor ID` - in case of success.
/// - `None`          - otherwise.
pub fn get_hypervisor_id() -> Option<[u8; VENDOR_ID_SIZE]> {
    #[cfg(target_arch = "x86")]
    arch::x86::cpu::get_hypervisor_id()
}

/// Get information about CPU.
///
/// # Returns
/// - CPU information struct.
pub fn get_cpu_info() -> CPUInfo {
    #[cfg(target_arch = "x86")]
    arch::x86::cpu::get_cpu_info()
}
