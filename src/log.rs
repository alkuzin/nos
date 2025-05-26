// Project name: NOS (Null Operating System).
// Description: Monolithic UNIX-like operating system.
// Licence: GPL-3.0.
// Author: Alexander (@alkuzin).

//! Kernel logging related declarations.

use crate::hal::uart::{Uart, UartInterface};
use core::fmt::{Arguments, Write};
use lazy_static::lazy_static;
use spin::Mutex;

lazy_static! {
    /// Global serial port writer.
    pub static ref SERIAL_WRITER: Mutex<Uart> = Mutex::new(Uart {});
}

/// Initialize global serial port writer.
pub fn init() {
    SERIAL_WRITER.lock().init();
}

/// Prints format string and it's arguments.
///
/// # Parameters
/// - `args` - given precompiled version of a format string and it`s arguments.
pub fn __print(args: Arguments) {
    let _ = SERIAL_WRITER.lock().write_fmt(args);
}

/// Formats and prints data.
#[macro_export]
macro_rules! print {
    ($($arg:tt)*) => (
        $crate::log::__print(format_args!($($arg)*))
    );
}

/// Formats and prints data with '\n' in the end.
#[macro_export]
macro_rules! printk {
    // Empty message.
    () => ($crate::print!("\n"));
    // Default case for any other arguments.
    ($($arg:tt)*) => ($crate::print!("{}\n", format_args!($($arg)*)));
}
