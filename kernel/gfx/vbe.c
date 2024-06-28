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

#include <nos/ports.h>
#include <nos/vbe.h>
#include <nos/gfx.h>

/**
 * @brief Set VBE params.
 * 
 * @param [in] index - given index to set. 
 * @param [in] data - given data to set. 
 */
static void vbe_write(u16 index, u16 data);


void vbe_init(multiboot_info_t *boot_info)
{
    vbe_mode_info_t* vbe_mode;
    
    vbe_mode = (vbe_mode_info_t*)boot_info->vbe_mode_info;

    vbe_set_video_mode(1024, 768, 32, vbe_mode->pitch, (u32*)vbe_mode->framebuffer);
}

void vbe_set_video_mode(u16 width, u16 height, u16 depth, u16 pitch, u32 *fb_addr)
{
    gfx_set_pitch(pitch);
    gfx_set_width(width);
    gfx_set_height(height);

    gfx_set_framebuffer(fb_addr);
    gfx_back_frambuffer_init();

    vbe_write(0x00, 0x4F02);  /* set VBE mode */ 
    vbe_write(0x01, width);   /* set width */ 
    vbe_write(0x02, height);  /* set height */ 
    vbe_write(0x03, depth);   /* Set bits per pixel */ 
    vbe_write(0x04, VBE_DISPI_ENABLED | VBE_DISPI_LFB_ENABLED); /* enable LFB mode */
}

static void vbe_write(u16 index, u16 data)
{
    outw(VBE_DISPI_IOPORT_INDEX, index);
    outw(VBE_DISPI_IOPORT_DATA, data);
}