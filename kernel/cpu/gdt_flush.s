;MIT License

;Copyright (c) 2024 Alexander (@alkuzin)

;Permission is hereby granted, free of charge, to any person obtaining a copy
;of this software and associated documentation files (the "Software"), to deal
;in the Software without restriction, including without limitation the rights
;to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
;copies of the Software, and to permit persons to whom the Software is
;furnished to do so, subject to the following conditions:

;The above copyright notice and this permission notice shall be included in all
;copies or substantial portions of the Software.

;THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
;IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
;FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
;AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
;LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
;OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
;SOFTWARE.


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
