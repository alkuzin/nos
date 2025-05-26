// Project name: NOS (Null Operating System).
// Description: Monolithic UNIX-like operating system.
// Licence: GPL-3.0.
// Author: Alexander (@alkuzin).

//! Contains functions for input/output operations on ports.

use core::arch::asm;

/// Receive a byte of data from a specified port.
///
/// # Parameters
/// - `port` - given port from which the data will be read.
///
/// # Safety:
/// - Port `port` must be a valid I/O port for reading data.
/// - Accessing an invalid port may lead to undefined behavior.
///
/// # Returns
///  The byte of data read from the port.
#[inline(always)]
pub unsafe fn inb(port: u16) -> u8 {
    let mut ret: u8;
    unsafe {
        asm!("in al, dx", out("al") ret, in("dx") port);
    }
    ret
}

/// Output a byte to a specified port.
///
/// # Parameters
/// - `port` - given port to which the data will be written.
/// - `data` - given data byte to be written to the port.
///
/// # Safety:
/// - Port `port` must be a valid I/O port for reading data.
/// - Accessing an invalid port may lead to undefined behavior.
#[inline(always)]
pub unsafe fn outb(port: u16, data: u8) {
    unsafe {
        asm!("out dx, al", in("dx") port, in("al") data);
    }
}
