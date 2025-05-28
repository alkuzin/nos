// Project name: NOS (Null Operating System).
// Description: Monolithic UNIX-like operating system.
// Licence: GPL-3.0.
// Author: Alexander (@alkuzin).

//! Contains PS/2 keyboard driver.

use crate::{hal::keyboard::Key, arch::x86::io::inb, print};

impl From<u8> for Key {
    /// Convert byte to keyboard key.
    ///
    /// # Parameters
    /// - `value` - given value to convert.
    ///
    /// # Returns
    /// - `Key` enumeration member associated with `value`.
    fn from(value: u8) -> Self {
        match value {
            0x01 => Key::Esc,
            0x0E => Key::Backspace,
            0x0F => Key::Tab,
            0x1C => Key::Enter,
            0x1D => Key::LCtrl,
            0x2A => Key::LShift,
            0x2B => Key::Backslash,
            0x38 => Key::LAlt,
            0x39 => Key::Space,
            0x3A => Key::CapsLock,
            0x4B => Key::LeftArrow,
            0x60 => Key::RightArrow,
            0x48 => Key::UpArrow,
            0x50 => Key::DownArrow,
            _ => Key::Unknown,
        }
    }
}

/// Unknown or undefined character placeholder.
const UNKNOWN: char = '\0';

/// Array of lowercase characters to print.
const LOWERCASE_KEYS: [char; 128] = [
    UNKNOWN, UNKNOWN, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-',
    '=', UNKNOWN, '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[',
    ']', '\n', UNKNOWN, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'',
    '`', UNKNOWN, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',
    UNKNOWN, '*', UNKNOWN, ' ', UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN,
    UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN,
    UNKNOWN, UNKNOWN, UNKNOWN, '-', UNKNOWN, UNKNOWN, UNKNOWN, '+', UNKNOWN,
    UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN,
    UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN,
    UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN,
    UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN,
    UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN,
    UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN,
];

/// Array of uppercase characters to print.
const UPPERCASE_KEYS: [char; 128] = [
    UNKNOWN, UNKNOWN, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_',
    '+', UNKNOWN, '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{',
    '}', '\n', UNKNOWN, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"',
    '~', UNKNOWN, '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?',
    UNKNOWN, '*', UNKNOWN, ' ', UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN,
    UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN,
    UNKNOWN, UNKNOWN, UNKNOWN, '-', UNKNOWN, UNKNOWN, UNKNOWN, '+', UNKNOWN,
    UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN,
    UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN,
    UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN,
    UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN,
    UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN,
    UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN,
];

/// Current keyboard key scan code.
static mut SCAN_CODE: u8 = 0;

/// Checks whether current keyboard key is pressed or released.
static mut IS_PRESSED: bool = false;

/// Checks whether `Left Shift` key is pressed.
static mut IS_SHIFT: bool = false;

/// Read keyboard key.
///
/// # Returns
/// - Pressed keyboard key info.
pub fn read_key() -> Key {
    unsafe {
        // Wait until key is pressed.
        while (inb(0x64) & 0x01) == 0 {
            continue;
        }

        SCAN_CODE = inb(0x60) & 0x7F;
        IS_PRESSED = (inb(0x60) & 0x80) != 0;
    }

    let scan_code = unsafe { SCAN_CODE };
    let is_pressed = unsafe { IS_PRESSED };
    let is_shift_pressed = unsafe { IS_SHIFT };

    let key = Key::from(scan_code);

    match key {
        Key::LShift => {
            unsafe {
                IS_SHIFT = !is_pressed;
            }
        }
        Key::Unknown => {
            if !is_pressed {
                let pos = scan_code as usize;

                // Check whether to return uppercase or lowercase character.
                let ch = if is_shift_pressed {
                    UPPERCASE_KEYS[pos]
                }
                else {
                    LOWERCASE_KEYS[pos]
                };

                return Key::Char(ch);
            }
        }
        _ => {
            // Just return other keys.
            if is_pressed {
                return key
            }
        },
    }

    Key::Unknown
}

/// Read line from keyboard till '\n' character.
///
/// # Parameters
/// - `buffer` - given buffer to store read characters.
pub fn get_line(buffer: &mut [char]) {
    let mut pos: usize = 0;
    let size = buffer.len();

    loop {
        let key = read_key();

        match key {
            Key::Backspace => {
                if pos == 0 {
                    continue;
                }
                else {
                    pos -= 1;
                    buffer[pos] = UNKNOWN;
                    print!("\x08");
                }
            }
            Key::Enter => {
                print!("\n");
                break;
            }
            Key::Space => {
                print!(" ");
                
                if pos < size {
                    buffer[pos] = ' ';
                    pos += 1;
                }
            }
            Key::Tab => {
                let mut i = 0;

                while pos < size && i < 4 {
                    buffer[pos] = ' ';
                    pos += 1;
                    i += 1;
                    print!(" ");
                }
            },
            Key::Char(ch) => {
                if ch == UNKNOWN {
                    break;
                }

                print!("{}", ch);

                if pos < size && ch.is_ascii_graphic() {
                    buffer[pos] = ch;
                    pos += 1;
                }
            }
            _ => {},
        }
    }
}

/// Initialize keyboard driver.
pub fn init() {
    // Do nothing.
    // TODO: use interrupts for keyboard driver.
}
