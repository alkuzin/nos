// Project name: NOS (Null Operating System).
// Description: Monolithic UNIX-like operating system.
// Licence: GPL-3.0.
// Author: Alexander (@alkuzin).

//! Kernel graphics subsystem.

use crate::{log, multiboot::MultibootInfo, drivers::vbe::Framebuffer};
use core::ptr;

/// RGB color type.
pub type Rgb = u32;

/// Make RGB color from red, green and blue components.
///
/// # Usage
/// ```
/// let white_color: Rgb = rgb!(255, 255, 255);
/// ```
#[macro_export]
macro_rules! rgb {
    ($red:expr, $green:expr, $blue:expr) => {
        (($red as u32) << 16) | (($green as u32) << 8) | ($blue as u32)
    };
}

/// Standard color enumeration.
#[repr(u32)]
pub enum Color {
    White  = rgb!(0xFF, 0xFF, 0xFF),
    Black  = rgb!(0x00, 0x00, 0x00),
    Red    = rgb!(0xFF, 0x00, 0x00),
    Green  = rgb!(0x00, 0xFF, 0x00),
    Blue   = rgb!(0x00, 0x00, 0xFF),
    Gray   = rgb!(0xBF, 0xBF, 0xBF),
    Yellow = rgb!(0xFF, 0xFF, 0x44),
    Orange = rgb!(0xFF, 0x70, 0x00),
}

/// Extract framebuffer info from boot info.
///
/// # Parameters
/// - `boot_info` - given multiboot info structure.
///
/// # Returns
/// - Framebuffer info struct.
fn get_framebuffer(boot_info: &MultibootInfo) -> Framebuffer {
    Framebuffer {
        addr:   boot_info.framebuffer_addr as u32,
        pitch:  boot_info.framebuffer_pitch,
        width:  boot_info.framebuffer_width,
        height: boot_info.framebuffer_height,
        bpp:    boot_info.framebuffer_bpp,
    }
}

/// Put pixel on the screen.
///
/// # Parameters
/// - `fb`    - given framebuffer info struct.
/// - `x`     - given x-coordinate of pixel.
/// - `y`     - given y-coordinate of pixel.
/// - `color` - given RGB color of pixel.
///
/// # Safety
/// - This method is unsafe because of its lack of bounds check.
#[inline(always)]
pub unsafe fn put_pixel(fb: &Framebuffer, x: u32, y: u32, color: Rgb) {
    // Pixel position in framebuffer.
    let pos = (y * fb.width + x) as usize;

    unsafe {
        let addr = fb.addr();
        ptr::write(addr.wrapping_add(pos), color);
    }
}

/// Fill screen with specific color.
///
/// # Parameters
/// - `color` - given color to fill with.
pub fn fill_screen(fb: &Framebuffer, color: Rgb) {
    let total_pixels = (fb.width * fb.height) as usize;

    unsafe {
        let buffer = fb.addr();
        let mut i  = 0;

        // Filling 4 pixels at once.
        while i <= total_pixels - 4 {
            ptr::write(buffer.wrapping_add(i), color);
            ptr::write(buffer.wrapping_add(i + 1), color);
            ptr::write(buffer.wrapping_add(i + 2), color);
            ptr::write(buffer.wrapping_add(i + 3), color);
            i += 4;
        }

        // Color any remaining pixels.
        for j in i..total_pixels {
            ptr::write(buffer.wrapping_add(j), color);
        }
    }
}

/// Initialize kernel graphics.
///
/// # Parameters
/// - `boot_info` - given multiboot info structure.
pub fn init(boot_info: &MultibootInfo) {
    let fb = get_framebuffer(boot_info);

    // TODO: init terminal.

    log::debug!("Bootloader provided framebuffer:");
    log::debug!("Address: <{:#010x}>", fb.addr);
    log::debug!("Pitch: {}", fb.pitch);
    log::debug!("Resolution: {}x{}", fb.width, fb.height);
    log::debug!("Bytes per pixel: {}", fb.bpp);
}
