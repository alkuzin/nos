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
 * @file  vbe.h
 * @brief Contains declarations for VBE (VESA BIOS Extensions).
 * 
 * @details This header file includes functions and structs related to the standard
 * interface for accessing advanced video modes and features on graphics hardware.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   24.06.2024
 */

#ifndef _NOS_KERNEL_VBE_H_
#define _NOS_KERNEL_VBE_H_

#include <nos/multiboot.h>
#include <nos/types.h>


// VBE ports
#define VBE_DISPI_IOPORT_INDEX 0x01CE
#define VBE_DISPI_IOPORT_DATA  0x01CF

// VBE control bits
#define VBE_DISPI_ENABLED      0x01
#define VBE_DISPI_LFB_ENABLED  0x40
#define VBE_DISPI_GETCAPS      0x02
#define VBE_DISPI_8BIT_DAC     0x20

#define VBE_DISPI_LFB_ENABLED  0x40
#define VBE_DISPI_NOCLEARMEM   0x80

#define VBE_DISPI_LFB_PHYSICAL_ADDRESS 0xB8000


struct __vbe_mode_info_s {
    u16 mode_attributes;        ///< Mode attributes.
    u8  win_a_attributes;       ///< Window A attributes.
    u8  win_b_attributes;       ///< Window B attributes.
    u16 win_granularity;        ///< Window granularity.
    u16 win_size;               ///< Window size.
    u16 win_a_segment;          ///< Window A segment.
    u16 win_b_segment;          ///< Window B segment.
    u32 win_func_ptr;           ///< Pointer to window function.
    u16 pitch;                  ///< Bytes per scanline.
    u16 x_resolution;           ///< Horizontal resolution.
    u16 y_resolution;           ///< Vertical resolution.
    u8  x_char_size;            ///< Character cell width.
    u8  y_char_size;            ///< Character cell height.
    u8  number_of_planes;       ///< Number of memory planes.
    u8  bits_per_pixel;         ///< Bits per pixel.
    u8  number_of_banks;        ///< Number of CGA style banks.
    u8  memory_model;           ///< Memory model type.
    u8  bank_size;              ///< Size of CGA style banks.
    u8  number_of_image_pages;  ///< Number of images pages.
    u8  reserved0;              ///< Reserved 0.

    u8  red_mask_size;          ///< Size of direct color red mask.
    u8  red_field_position;     ///< Bit position of lsb of red mask.
    u8  green_mask_size;        ///< Size of direct color green mask.
    u8  green_field_position;   ///< Bit position of lsb of green mask.
    u8  blue_mask_size;         ///< Size of direct color blue mask.
    u8  blue_field_position;    ///< Bit position of lsb of blue mask.
    u8  rsvd_mask_size;         ///< Size of direct color res mask.
    u8  rsvd_field_position;    ///< Bit position of lsb of res mask.
    u8  direct_color_mode_info; ///< Direct color mode attributes.

	u32 framebuffer;		    ///< Physical address of the linear frame buffer.
	u32 off_screen_mem_off;     ///< Offset in memory where the off-screen memory starts.
	u16 off_screen_mem_size;	///< Size of memory in the framebuffer but not being displayed on the screen.
	u8  reserved1[206];
} __attribute__((packed)); /* prevent the compiler from optimizing */

typedef struct __vbe_mode_info_s vbe_mode_info_t;


/**
 * @brief Initialize VBE mode. 
 * 
 * @param [in] boot_info - given multiboot information structure.
 */
void vbe_init(multiboot_info_t *boot_info);

/**
 * @brief Set VBE video mode.
 * 
 * @param [in] width - given screen width.
 * @param [in] height - given screen height.
 * @param [in] depth - given number of bits per pixel.
 * @param [in] fb_addr - given framebuffer pointer.
 */
void vbe_set_video_mode(u16 width, u16 height, u16 depth, u32 *fb_addr);

#endif /* _NOS_KERNEL_VBE_H_ */ 