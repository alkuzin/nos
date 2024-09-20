/**
 * The Null Operating System (NOS).
 * Copyright (C) 2024  Alexander (@alkuzin).
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <kernel/kstd/cstring.hpp>
#include <kernel/kstd/ctype.hpp>
#include <kernel/gfx/vbefont.hpp>
#include <kernel/terminal.hpp>


namespace kernel {
namespace tty {

constexpr s32 TAB_WIDTH {4};

void Terminal::init(gfx::Framebuffer& fb) noexcept
{
    m_fb     = fb;
    m_width  = m_fb.width();
    m_height = m_fb.height();
}

gfx::rgb Terminal::fg(void) noexcept
{
    return m_fg;
}

gfx::rgb Terminal::bg(void) noexcept
{
    return m_bg;
}

gfx::rgb Terminal::primary_color(void) const noexcept
{
    return m_primary_color;
}

gfx::rgb Terminal::secondary_color(void) const noexcept
{
    return m_secondary_color;
}

void Terminal::set_color(gfx::rgb fg, gfx::rgb bg, gfx::rgb pc, gfx::rgb sc) noexcept
{
    m_fg = fg;
    m_bg = bg;
    m_primary_color   = pc;
    m_secondary_color = sc;
}

void Terminal::clear(void) noexcept
{
	gfx::graphics.fill_screen(m_bg);
    m_x_pos = 0;
    m_y_pos = 0;
}

void Terminal::scroll(void) noexcept
{  
	u32 *framebuffer = m_fb.addr();
	u32 size		 = m_fb.size();
	u32 offset;

    for (u32 i = 0; i < size; i++) {
		offset         = i + static_cast<u32>(m_width) * gfx::VBE_CHAR_HEIGHT;
        framebuffer[i] = framebuffer[offset];
    }

	auto pos = size - m_width * gfx::VBE_CHAR_HEIGHT;
	kstd::bzero(&framebuffer[pos], size - pos);
}

void Terminal::put_at(char c, s32 x, s32 y, gfx::rgb fg, gfx::rgb bg) noexcept
{   
	draw_char(static_cast<u8>(c), x, y, fg, bg, true);
}

void Terminal::put_c(const s32 c, gfx::rgb fg, gfx::rgb bg) noexcept
{
	s32 rows_to_scroll;

	if(m_x_pos >= m_width) {
		m_x_pos = 0;
		m_y_pos += gfx::VBE_CHAR_HEIGHT;
	}

	switch(c) {
		case '\n':
			for (s32 i = 0; i < m_width / gfx::VBE_CHAR_WIDTH; i++) {
            	put_at(' ', m_x_pos, m_y_pos, fg, bg);
			    m_x_pos += gfx::VBE_CHAR_WIDTH;
			}

			m_y_pos += gfx::VBE_CHAR_HEIGHT;
			m_x_pos = 0;
			
			break;
		
		case '\t':
			for (s32 i = 0; i < TAB_WIDTH; i++) {
            	put_at(' ', m_x_pos, m_y_pos, fg, bg);
				m_x_pos += gfx::VBE_CHAR_WIDTH;
			}
			break;
		
		case '\v':
			m_y_pos += gfx::VBE_CHAR_HEIGHT;
			break;
		
		case '\r':
			m_x_pos = 0;
			break;
		
		case '\b':
            m_x_pos -= gfx::VBE_CHAR_WIDTH;
            
            if(!m_x_pos && m_y_pos) {
			    m_y_pos -= gfx::VBE_CHAR_HEIGHT;
                m_x_pos = m_width;
            }
			
            put_at(' ', m_x_pos, m_y_pos, fg, bg);
			break;
		
		default:
            if(kstd::isprint(c)) {
            	put_at(c, m_x_pos, m_y_pos, fg, bg);
			    m_x_pos += gfx::VBE_CHAR_WIDTH;
            }
			break;
	};

	if (m_y_pos >= m_height) {
        rows_to_scroll = (m_y_pos - m_height) / gfx::VBE_CHAR_HEIGHT + 1;
        scroll();
        m_y_pos -= rows_to_scroll * gfx::VBE_CHAR_HEIGHT;
    }
}

void Terminal::draw_char(u8 c, s32 x, s32 y, const gfx::rgb& fg, const gfx::rgb& bg, bool is_bg_on) noexcept
{
    s32 cx, cy;
    static s32 mask[8] = { 128, 64, 32, 16, 8, 4, 2, 1 };
    u8  *glyph = static_cast<u8*>(gfx::vbefont) + static_cast<s32>(c) * 16;

    for (cy = 0; cy < 16; cy++) {
        for (cx = 0; cx < 8; cx++) {
            if (glyph[cy] & mask[cx])
                gfx::graphics.set_pixel(x + cx, y + cy, fg); 
            else if (is_bg_on)
                gfx::graphics.set_pixel(x + cx, y + cy, bg);
        }
    }
}

Terminal terminal;

} // namespace tty
} // namespace kernel