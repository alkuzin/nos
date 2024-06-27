/* MIT License
 *
 * Copyright (c) 2024 Alexander (@alkuzin)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. */

/**
 * @file  tty.h
 * @brief TTY (teletype terminal). Contains definitions related
 * to screen input/output.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   17.05.2024 
 */

#ifndef _NOS_KERNEL_TTY_H_
#define _NOS_KERNEL_TTY_H_ 

#include <stdarg.h>

#include <nos/types.h>
#include <nos/vga.h>
#include <nos/gfx.h>

///< Default kernel TTY foreground & background color.
#define TTY_FG_COLOR  RGB(255, 255, 255)
#define TTY_BG_COLOR  RGB(0, 0, 204)
#define TTY_TAB_WIDTH 4

///< For NULL pointer in kprintf.
#define __NIL__ "(nil)"

///< TTY management structure.
typedef struct tty_s {
    s32   x_pos;            ///< X position of the cursor.
    s32   y_pos;            ///< Y position of the cursor.
    rgb_t fg;               ///< Foreground color.
    rgb_t bg;               ///< Background color.
    s32   height;           ///< Screen height.
    s32   width;            ///< Screen width.
    rgb_t primary_color;
    rgb_t secondary_color;
    rgb_t prev_fg;          ///< Previous foreground color.
    rgb_t prev_bg;          ///< Previous background color.
    rgb_t prev_prim_color;  ///< Previous primary color.
    rgb_t prev_sec_color;   ///< Previous secondary color.
} tty_t;

/* Initialize kernel TTY structure. */ 
void tty_init(void);

/* Initialize kernel TTY cursor structure. */ 
void tty_cursor_init(void);

/**
 * @brief Get cursor x position.
 * 
 * @return x position.
 */
s32  tty_get_x(void);

/**
 * @brief Get cursor y position.
 * 
 * @return y position.
 */
s32  tty_get_y(void);

/**
 * @brief Set cursor x position.
 * 
 * @param [in] x - new given cursor x position.
 */
void tty_set_x(s32 x);

/**
 * @brief Set cursor y position.
 * 
 * @param [in] y - new given cursor y position.
 */
void tty_set_y(s32 y);

/**
 * @brief Get kernel TTY structure foreground color.
 * 
 * @return current foreground color.
 */
rgb_t tty_get_fg(void);

/**
 * @brief Get kernel TTY structure background color.
 * 
 * @return current background color.
 */
rgb_t tty_get_bg(void);

/**
 * @brief Get TTY primary color. 
 * 
 * @return primary color. 
 */
rgb_t tty_get_primary_color(void);

/**
 * @brief Get TTY secondary color. 
 * 
 * @return secondary color. 
 */
rgb_t tty_get_secondary_color(void);

/**
 * @brief Set TTY primary color.
 * 
 * @param [in] color - given new primary color.
 */
void tty_set_primary_color(rgb_t color);

/**
 * @brief Set TTY secondary color. 
 * 
 * @param [in] color - given new secondary color.
 */
void tty_set_secondary_color(rgb_t color);

/**
 * @brief Set foreground & background color.
 * 
 * @param [in] fg - given foreground color.
 * @param [in] bg - given background color.
 */
void tty_set_color(rgb_t fg, rgb_t bg);

/**
 * @brief Get screen height.
 * 
 * @return current screen height.
 */
s32  tty_get_height(void);

/**
 * @brief Get screen width.
 * 
 * @return current screen width.
 */
s32  tty_get_width(void);

/** @brief Clear screen. */ 
void tty_clear(void);

/** @brief Rewrite TTY buffer. */ 
void tty_rewrite(void);

/**
 * @brief Print char with custom color in a specific place.
 * 
 * @param [in] c - given character to print.
 * @param [in] x - given cursor x position to print.
 * @param [in] y - given cursor y position to print.
 * @param [in] fg - given foreground color. 
 * @param [in] bg - given background color. 
 */
void tty_kputchar_at(char c, s32 x, s32 y, rgb_t fg, rgb_t bg);

/**
 * @brief Print character to screen.
 * 
 * @param [in] c - given character to print.
 */
void kputchar(const s32 c);

/**
 * @brief Print colored string to the screen.
 * 
 * @param [in] str - given string to print.
 * @param [in] fg - given foreground color.
 * @param [in] bg - given background color.
 */
void tty_printc(const char *str, rgb_t fg, rgb_t bg);

/**
 * @brief Print colored character on screen.
 * 
 * @param [in] c - given character to print.
 * @param [in] fg - given foreground color.
 * @param [in] bg - given background color.
 */
void kputchar_c(const s32 c, rgb_t fg, rgb_t bg);

#endif /* _NOS_KERNEL_TTY_H_ */