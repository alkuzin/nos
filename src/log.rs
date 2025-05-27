// Project name: NOS (Null Operating System).
// Description: Monolithic UNIX-like operating system.
// Licence: GPL-3.0.
// Author: Alexander (@alkuzin).

//! Kernel logging related declarations.

use crate::{
    drivers::vbe::Framebuffer,
    hal::uart::{Uart, UartInterface},
    kernel::gfx::{Color, Rgb, terminal::Terminal},
};
use core::fmt;
use core::fmt::{Arguments, Write};
use lazy_static::lazy_static;
use spin::Mutex;

/// Global text output foreground color.
pub static mut FOREGROUND_COLOR: Rgb = Color::White as Rgb;

/// Global text output background color.
pub static mut BACKGROUND_COLOR: Rgb = Color::Black as Rgb;

/// Set current color of text output to the screen.
///
/// # Parameters
/// - `fg` - given foreground color to set.
/// - `bg` - given background color to set.
pub fn set_color(fg: Rgb, bg: Rgb) {
    unsafe {
        FOREGROUND_COLOR = fg;
        BACKGROUND_COLOR = bg;
    }
}

/// This method should be implemented for Terminal in order to
/// create println!() like macro rules for kernel needs.
impl Write for Terminal {
    fn write_str(&mut self, s: &str) -> fmt::Result {
        unsafe {
            for c in s.chars() {
                self.put_char(c, FOREGROUND_COLOR, BACKGROUND_COLOR);
            }
        }
        Ok(())
    }
}

lazy_static! {
    /// Global serial port writer.
    pub static ref SERIAL_WRITER: Mutex<Uart> = Mutex::new(Uart {});

    /// Global mutable terminal writer.
    pub static ref TERMINAL_WRITER: Mutex<Terminal> = Mutex::new(
        Terminal::default()
    );
}

/// Initialize global serial port writer.
pub fn init_serial_writer() {
    SERIAL_WRITER.lock().init();
}

/// Initialize global terminal port writer.
///
/// # Parameters
/// - `fb`- given framebuffer info struct.
pub fn init_terminal_writer(fb: Framebuffer) {
    TERMINAL_WRITER.lock().init(fb);
}

/// Prints format string and it's arguments.
///
/// # Parameters
/// - `args` - given precompiled version of a format string and it`s arguments.
pub fn __print(args: Arguments) {
    let _ = SERIAL_WRITER.lock().write_fmt(args);
    let _ = TERMINAL_WRITER.lock().write_fmt(args);
}

/// Formats and prints colored data.
#[macro_export]
macro_rules! cprint {
    ($fg:expr, $bg:expr, $($arg:tt)*) => (
        let cur_fg = unsafe { $crate::log::FOREGROUND_COLOR };
        let cur_bg = unsafe { $crate::log::BACKGROUND_COLOR };

        $crate::log::set_color($fg, $bg);
        $crate::log::__print(format_args!($($arg)*));
        $crate::log::set_color(cur_fg, cur_bg);
    );
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

/// Informational log title color.
pub const LOG_INFO_COLOR: Rgb = Color::White as Rgb;

/// Debug log title.
pub const LOG_DEBUG: &str = " DEBUG  ";

/// Debug log title color.
pub const LOG_DEBUG_COLOR: Rgb = Color::DarkGray as Rgb;

/// Success log title.
pub const LOG_SUCCESS: &str = "   OK   ";

/// Success log title color.
pub const LOG_SUCCESS_COLOR: Rgb = Color::Green as Rgb;

/// Fail log title.
pub const LOG_FAIL: &str = " FAILED ";

/// Fail log title color.
pub const LOG_FAIL_COLOR: Rgb = Color::Red as Rgb;

/// Panic log title.
pub const LOG_PANIC: &str = " PANIC  ";

/// Panic log title color.
pub const LOG_PANIC_COLOR: Rgb = Color::Yellow as Rgb;

/// Test log title.
pub const LOG_TEST: &str = "  TEST  ";

/// Test log title color.
pub const LOG_TEST_COLOR: Rgb = Color::Blue as Rgb;

/// Log timestamp color.
pub const TIMESTAMP_COLOR: Rgb = Color::DarkGray as Rgb;

/// Custom log output.
///
/// # Parameters
/// - `title` - given custom log title.
/// - `fb`    - given log title foreground color.
/// - `bg`    - given log title background color.
#[macro_export]
macro_rules! custom {
    // TODO: replace zeros in format string with timestamp:
    // [<seconds since boot>.<milliseconds since the last full second>].
    ($title:expr, $fg:expr, $bg:expr, $($arg:tt)*) => {{
        let timestamp_fg = $crate::log::TIMESTAMP_COLOR;
        let timestamp_bg = unsafe { $crate::log::BACKGROUND_COLOR };

        $crate::cprint!(timestamp_fg, timestamp_bg, "|{:0>5}.{:0>3}|", 0, 0);
        $crate::print!(" [");
        $crate::cprint!($fg, $bg, "{}", $title);
        $crate::print!("]: {}\n", format_args!($($arg)*));
    }};
}

/// Informational log output.
#[macro_export]
macro_rules! info {
    ($($arg:tt)*) => {{
        $crate::log::custom!(
            $crate::log::LOG_INFO,
            $crate::log::LOG_INFO_COLOR,
            unsafe { $crate::log::BACKGROUND_COLOR },
            $($arg)*
        )
    }};
}

/// Debug log output.
#[macro_export]
macro_rules! debug {
    ($($arg:tt)*) => {{
        #[cfg(debug_assertions)]
        $crate::log::custom!(
            $crate::log::LOG_DEBUG,
            $crate::log::LOG_DEBUG_COLOR,
            unsafe { $crate::log::BACKGROUND_COLOR },
            $($arg)*
        )
    }};
}

/// Success log output.
#[macro_export]
macro_rules! success {
    ($($arg:tt)*) => {{
        $crate::log::custom!(
            $crate::log::LOG_SUCCESS,
            $crate::log::LOG_SUCCESS_COLOR,
            unsafe { $crate::log::BACKGROUND_COLOR },
            $($arg)*
        )
    }};
}

/// Failed log output.
#[macro_export]
macro_rules! fail {
    ($($arg:tt)*) => {{
        $crate::log::custom!(
            $crate::log::LOG_FAIL,
            $crate::log::LOG_FAIL_COLOR,
            unsafe { $crate::log::BACKGROUND_COLOR },
            $($arg)*
        )
    }};
}

/// Panic log output.
#[macro_export]
macro_rules! panic {
    ($($arg:tt)*) => {{
        $crate::log::custom!(
            $crate::log::LOG_PANIC,
            $crate::log::LOG_PANIC_COLOR,
            unsafe { $crate::log::BACKGROUND_COLOR },
            $($arg)*
        )
    }};
}

/// Log output for tests.
#[macro_export]
macro_rules! test {
    ($($arg:tt)*) => {{
        $crate::log::custom!(
            $crate::log::LOG_TEST,
            $crate::log::LOG_TEST_COLOR,
            unsafe { $crate::log::BACKGROUND_COLOR },
            $($arg)*
        )
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
