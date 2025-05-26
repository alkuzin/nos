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

/// Informational log title.
pub const LOG_INFO: &str = "  INFO  ";

/// Debug log title.
pub const LOG_DEBUG: &str = " DEBUG  ";

/// Success log title.
pub const LOG_SUCCESS: &str = "   OK   ";

/// Fail log title.
pub const LOG_FAIL: &str = " FAILED ";

/// Panic log title.
pub const LOG_PANIC: &str = " PANIC  ";

/// Test log title.
pub const LOG_TEST: &str = "  TEST  ";

/// Custom log output.
///
/// # Parameters
/// - `title` - given custom log title.
#[macro_export]
macro_rules! custom {
    // TODO: replace zeros in format string with timestamp:
    // [<seconds since boot>.<milliseconds since the last full second>].
    ($title:expr, $($arg:tt)*) => {{
        $crate::print!("[{:0>5}.{:0>3}] [{}]: ", 0, 0, $title);
        $crate::print!("{}\n", format_args!($($arg)*));
    }};
}

/// Informational log output.
#[macro_export]
macro_rules! info {
    ($($arg:tt)*) => {{
        $crate::log::custom!($crate::log::LOG_INFO, $($arg)*)
    }};
}

/// Debug log output.
#[macro_export]
macro_rules! debug {
    ($($arg:tt)*) => {{
        #[cfg(debug_assertions)]
        $crate::log::custom!($crate::log::LOG_DEBUG, $($arg)*)
    }};
}

/// Success log output.
#[macro_export]
macro_rules! success {
    ($($arg:tt)*) => {{
        $crate::log::custom!($crate::log::LOG_SUCCESS, $($arg)*)
    }};
}

/// Failed log output.
#[macro_export]
macro_rules! fail {
    ($($arg:tt)*) => {{
        $crate::log::custom!($crate::log::LOG_FAIL, $($arg)*)
    }};
}

/// Panic log output.
#[macro_export]
macro_rules! panic {
    ($($arg:tt)*) => {{
        $crate::log::custom!($crate::log::LOG_PANIC, $($arg)*)
    }};
}

/// Log output for tests.
#[macro_export]
macro_rules! test {
    ($($arg:tt)*) => {{
        $crate::log::custom!($crate::log::LOG_TEST, $($arg)*)
    }};
}

// Re-export log macro rules.

#[allow(unused_imports)]
pub(crate) use custom;
#[allow(unused_imports)]
pub(crate) use debug;
#[allow(unused_imports)]
pub(crate) use fail;
#[allow(unused_imports)]
pub(crate) use info;
#[allow(unused_imports)]
pub(crate) use panic;
#[allow(unused_imports)]
pub(crate) use success;
#[allow(unused_imports)]
pub(crate) use test;
