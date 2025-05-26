// Project name: NOS (Null Operating System).
// Description: Monolithic UNIX-like operating system.
// Licence: GPL-3.0.
// Author: Alexander (@alkuzin).

//! VBE (VESA BIOS Extensions) driver.

/// VESA framebuffer struct.
#[derive(Debug, Default, Clone)]
pub struct Framebuffer {
    /// Framebuffer physical address.
    pub addr: u32,
    /// Number of bytes in a single row of the framebuffer.
    pub pitch: u32,
    /// Y-resolution.
    pub width: u32,
    /// X-resolution.
    pub height: u32,
    /// Bytes per pixel.
    pub bpp: u8,
}

impl Framebuffer {
    /// Get framebuffer memory address pointer.
    ///
    /// # Returns
    /// - Framebuffer address as mutable raw pointer.
    #[inline(always)]
    pub fn addr(&self) -> *mut u32 {
        self.addr as *mut u32
    }
}
