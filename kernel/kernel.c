/*
MIT License

Copyright (c) 2024 Alexander (@alkuzin)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <kernel/kernel.h>
#include <kernel/tty.h>

/* kernel entry point */
extern void kmain(void)
{
	__kclear(); /* clear screen */
	
	/* display kernel info */
	kprintc("---------------------------------------------\n", VGA_COLOR_BLUE, VGA_COLOR_BLACK);	
	kprintf("%s [%s] @alkuzin - 2024\n", __OS_NAME__, __OS_VERSION__);	
	kprintc("---------------------------------------------\n", VGA_COLOR_BLUE, VGA_COLOR_BLACK);	

	kprintf("\nvideo memory address: <%p>\n", VIDEO_MEMORY);	

	for(;;); /* infinite loop for halting CPU */
}
