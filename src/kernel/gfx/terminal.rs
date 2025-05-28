// Project name: NOS (Null Operating System).
// Description: Monolithic UNIX-like operating system.
// Licence: GPL-3.0.
// Author: Alexander (@alkuzin).

//! Contains kernel terminal declaration.

use super::{Color, Rgb, draw_char, fill_screen, font};
use crate::drivers::vbe::Framebuffer;
use core::ptr;

/// Default tabulation width.
const TAB_WIDTH: u32 = 4;

/// Kernel terminal struct.
#[derive(Default)]
pub struct Terminal {
    /// Graphics handler.
    fb: Option<Framebuffer>,
    /// Screen height.
    height: i32,
    /// Screen width.
    width: i32,
    /// X position of the cursor.
    x_pos: i32,
    /// Y position of the cursor.
    y_pos: i32,
    /// Foreground color.
    pub fg: Rgb,
    /// Background color.
    pub bg: Rgb,
}

impl Terminal {
    /// Scroll screen.
    fn scroll(&self) {
        if let Some(fb) = &self.fb {
            let size = (fb.height * fb.pitch) as usize;
            let addr = fb.addr();

            // Calculate the number of bytes to scroll.
            let scroll_amount = fb.width as usize * font::CHAR_HEIGHT;
            let new_size = size - scroll_amount;

            unsafe {
                ptr::copy(addr.wrapping_add(scroll_amount), addr, new_size);
                ptr::write_bytes(addr.wrapping_add(new_size), 0, scroll_amount);
            }
        }
    }

    /// Initialize Terminal.
    ///
    /// # Parameters
    /// - `fb` - given framebuffer info struct.
    pub fn init(&mut self, fb: Framebuffer) {
        self.height = fb.height as i32;
        self.width = fb.width as i32;
        self.fb = Some(fb);
        self.x_pos = 0;
        self.y_pos = 0;
        self.fg = Color::White as Rgb;
        self.bg = Color::Black as Rgb;
    }

    /// Clear screen.
    pub fn clear(&self) {
        if let Some(fb) = &self.fb {
            fill_screen(fb, self.bg);
        }
    }

    /// Print colored character on screen.
    ///
    /// # Parameters
    /// `c`  - given character to print.
    /// `fg` - given foreground color.
    /// `bg` - given background color.
    pub fn put_char(&mut self, c: char, fg: Rgb, bg: Rgb) {
        if let Some(fb) = &self.fb {
            if self.x_pos >= self.width {
                self.x_pos = 0;
                self.y_pos += font::CHAR_HEIGHT as i32;
            }

            match c {
                // Handle new line character.
                '\n' => {
                    self.y_pos += font::CHAR_HEIGHT as i32;
                    self.x_pos = 0;
                }
                // Handle tab character.
                '\t' => {
                    for _ in 0..TAB_WIDTH {
                        draw_char(
                            fb,
                            ' ',
                            self.x_pos as usize,
                            self.y_pos as usize,
                            fg,
                            bg,
                            true,
                        );

                        self.x_pos += font::CHAR_WIDTH as i32;
                    }
                }
                // Handle backspace character.
                '\x08' => {
                    self.x_pos -= font::CHAR_WIDTH as i32;

                    if !(self.x_pos != 0 && self.y_pos != 0) {
                        self.y_pos -= font::CHAR_HEIGHT as i32;
                        self.x_pos = self.width;
                    }

                    draw_char(
                        fb,
                        ' ',
                        self.x_pos as usize,
                        self.y_pos as usize,
                        fg,
                        bg,
                        true,
                    );
                }

                // Handle other characters.
                _ => {
                    if c == ' ' || c.is_ascii_graphic() {
                        draw_char(
                            fb,
                            c,
                            self.x_pos as usize,
                            self.y_pos as usize,
                            fg,
                            bg,
                            true,
                        );

                        self.x_pos += font::CHAR_WIDTH as i32;
                    }
                }
            }

            // Scroll screen.
            if self.y_pos >= self.height {
                let tmp = self.y_pos - self.height;
                let rows = tmp / font::CHAR_HEIGHT as i32 + 1;
                self.scroll();
                self.y_pos -= rows * font::CHAR_HEIGHT as i32;
            }
        }
    }
}
