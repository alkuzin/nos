// Project name: NOS (Null Operating System).
// Description: Monolithic UNIX-like operating system.
// Licence: GPL-3.0.
// Author: Alexander (@alkuzin).

//! Contains UART (Universal Asynchronous Receiver-Transmitter) driver.

use crate::{
    arch::x86::io::{inb, outb},
    hal::uart::UartInterface,
};

/// Base address for COM1.
const UART_BASE: u16 = 0x3f8;

/// UART driver struct.
pub struct Uart;

impl Uart {
    /// Checks if the transmit buffer is empty.
    ///
    /// # Returns
    /// - `true`  - if the transmit buffer is empty.
    /// - `false` - otherwise.
    fn is_transmit_empty() -> bool {
        unsafe {
            // Read the Line Status Register and check
            // the transmit empty bit (bit 5).
            (inb(UART_BASE + 5) & 0x20) != 0
        }
    }
}

impl UartInterface for Uart {
    /// Initialize UART driver.
    fn init(&self) {
        unsafe {
            // Disable all interrupts.
            outb(UART_BASE + 1, 0x00);
            // Enable DLAB (set baud rate divisor).
            outb(UART_BASE + 3, 0x80);
            // Set divisor to 3 (lo byte) 38400 baud.
            outb(UART_BASE, 0x03);
            // Set divisor to 3 (hi byte) 38400 baud.
            outb(UART_BASE + 1, 0x00);
            // 8 bits, no parity, one stop bit.
            outb(UART_BASE + 3, 0x03);
            // Enable FIFO, clear them, with 14-byte threshold.
            outb(UART_BASE + 2, 0xC7);
            // IRQs enabled, RTS/DSR set.
            outb(UART_BASE + 4, 0x0B);
        }
    }

    /// Read byte from serial port.
    ///
    /// # Returns
    /// - Byte read from serial port.
    fn read(&self) -> u8 {
        while !Self::is_transmit_empty() {
            continue;
        }

        unsafe { inb(UART_BASE) }
    }

    /// Write byte to serial port.
    ///
    /// # Parameters
    /// - `b` - given byte to write.
    fn write(&self, b: u8) {
        while !Self::is_transmit_empty() {
            continue;
        }

        unsafe {
            outb(UART_BASE, b);
        }
    }
}
