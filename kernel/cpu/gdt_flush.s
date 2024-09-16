; The Null Operating System (NOS).
; Copyright (C) 2024  Alexander (@alkuzin).
; 
; This program is free software: you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation, either version 3 of the License, or
; (at your option) any later version.
; 
; This program is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.
; 
; You should have received a copy of the GNU General Public License
; along with this program.  If not, see <https://www.gnu.org/licenses/>.

global gdt_flush
global tss_flush

gdt_flush:
    mov eax, [esp + 4] ; get argument
    lgdt [eax]

    mov eax, 0x10
    mov ds, ax ; ds - data segment
    mov es, ax ; es - extra segment
    mov fs, ax ; fs - additional segment
    mov gs, ax ; gs - global segment
    mov ss, ax ; ss - stack segment

    jmp 0x08:.flush ; setting code segment

.flush:
    ret

tss_flush:
    mov ax, 0x2b
    ltr ax
    ret
