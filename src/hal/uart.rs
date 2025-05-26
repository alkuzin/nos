// Project name: NOS (Null Operating System).
// Description: Monolithic UNIX-like operating system.
// Licence: GPL-3.0.
// Author: Alexander (@alkuzin).

//! Contains UART (Universal Asynchronous Receiver-Transmitter)
//! architecture-independent interface.

use crate::arch;
use core::fmt;

/// UART architecture-independent interface.
pub trait UartInterface {
    /// Initialize UART driver.
    fn init(&self);

    /// Read byte from serial port.
    ///
    /// # Returns
    /// - Byte read from serial port.
    fn read(&self) -> u8;

    /// Write byte to serial port.
    ///
    /// # Parameters
    /// - `b` - given byte to write.
    fn write(&self, b: u8);
}

/// Alias for architecture-specific UART driver struct.
#[cfg(target_arch = "x86")]
pub type Uart = arch::x86::drivers::uart::Uart;

/// Format write trait implementation.
impl fmt::Write for Uart {
    /// Write string.
    ///
    /// # Parameters
    /// - `s` - given string slice to write.
    ///
    /// # Returns
    /// - `Ok`  - in case of success.
    /// - `Err` - otherwise.
    fn write_str(&mut self, s: &str) -> fmt::Result {
        for c in s.bytes() {
            Self::write(self, c);
        }

        Ok(())
    }
}
