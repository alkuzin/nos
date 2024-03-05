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

#include <libk/string.h>
#include <libk/stddef.h> 
#include <libk/stdarg.h> 
#include <libk/memory.h>
#include <libk/ctype.h> 
#include <kernel/tty.h>
#include <libk/math.h>

static int prefix_flag = 0;

#define TTY_PRINTF_BUFFER_SIZE 1024

static char tty_printf_buffer[TTY_PRINTF_BUFFER_SIZE] = {0};
static int  tty_printf_pos = 0;

static void tty_printf_append(char c);

/* %x %X options (hexadecimal) */
static void   __tty_printf_hex(uint64_t n, int is_upper);

/* hexadecimal to alphanumeric lenght */
static int    __tty_xtoa_len(uint32_t n);

/* %i %d options (int) */
static void   __tty_printf_int(int n);

/* int to alphanumeric lenght */
static size_t __tty_itoa_len(int n);

/* %p option (pointer) */
static void   __tty_printf_pointer(uint64_t p);

/* digit to hex */
static char   __tty_dtoh(int v);

/* %u option (unsigned int) */
static void   __tty_printf_uint(uint32_t n);

/* unsigned int to alphanumeric lenght */
static size_t __tty_utoa_len(uint32_t n);

/* print tty_printf arguments */
static void   __tty_print_args(char type, va_list args);

/* parse tty_printf arguments */
static void   __tty_parse(const char* str, va_list args);

static void tty_printf_append(char c)
{
	tty_printf_buffer[tty_printf_pos] = c;
	tty_printf_pos++;
}

/* tty_printf unsigned int */
static size_t __tty_utoa_len(uint32_t n)
{
	size_t len;

	len = 0;

	if (n == 0)
		return 1;

	while (n >= 1) {
		len++;
		n /= 10;
	}

	return len;
}

static void __tty_printf_uint(uint32_t n)
{
	size_t length, temp_len;

	temp_len = __tty_utoa_len(n);
	length   = temp_len;

	char buffer[temp_len];

	temp_len--;
	while (temp_len) {
		buffer[temp_len] = (n % 10) + '0';
		n /= 10;
		temp_len--;
	}

	buffer[0] = (n % 10) + '0';
	buffer[length] = '\0';

	tty_print(buffer);
}

/* tty_printf pointer */
static char __tty_dtoh(int v) 
{
   if (v >= 0 && v < 10)
       return '0' + v;
   else
       return 'a' + v - 10;
}

static void __tty_printf_pointer(uint64_t p)
{
	int count, i;
		
	if(p == 0) {
		tty_print(__NIL__);
		return;
	}
	
	tty_putchar('0');
	tty_putchar('x');
	
	count = 0;
	i = (sizeof(p) << 3) - 4;	

	/* skip first zeros */
	while(i >= 0 && ((__tty_dtoh((p >> i) & 0xf) == '0')))
		i -= 4;
	
	while(i >= 0) {
		tty_putchar(__tty_dtoh((p >> i) & 0xf));
		i -= 4;
		count++;
	}
}

/* tty_printf int */
static size_t __tty_itoa_len(int n)
{
	size_t len;

	len = 0;

	if (n == 0)
		return 1;
	
	if (n < 0) {
		n = -n;
		len++;
	}

	while (n >= 1) {
		len++;
		n /= 10;
	}

	return len;
}

static void __tty_printf_int(int n)
{
	size_t length, i;

	i = __tty_itoa_len(n);
	length = i;

	char buffer[length];
	i--;

	if (n < 0) {
		buffer[0] = '-';
		n = -n;
	}

	while (i) {
		buffer[i] = (n % 10) + '0';
		n /= 10;
		i--;
	}
	
	if (buffer[0] != '-')
		buffer[0] = (n % 10) + '0';

	buffer[length] = '\0';
	
	while (buffer[i]) {
		tty_printf_append(buffer[i]);
		i++;
	}
}

/* tty_printf hex */
static int __tty_xtoa_len(uint32_t n)
{
	if (n == 0)
	   return 1;
	
	return (int)(log(n) / log(16)) + 1;
}

static void __tty_printf_hex(uint64_t n, int is_upper)
{
	static const char digits_lower[] = "0123456789abcdef";
	static const char digits_upper[] = "0123456789ABCDEF";
	static const char *digits = NULL;
	int i;
	
	i = __tty_xtoa_len(n);
	char hex[i + 1];
	
	if(prefix_flag) {
		tty_printf_append('0');
		tty_printf_append('x');
		prefix_flag = 0;
	}
	
	if(n == 0) {
		tty_printf_append('0');
		return;
	}

	if(is_upper) 
		digits = digits_upper;
	else
		digits = digits_lower;
	
	i = 7;
	while(i >= 0) {
		hex[i] = digits[(n & 0x0F)];
		n >>= 4;
		--i;
	}

	hex[i] = '\0';
	i = 0;
		
	while(hex[i] && hex[i] == '0')
		i++;

	while(hex[i]) {
		tty_printf_append(hex[i]);
		i++;
	}
}

static void __tty_print_args(char type, va_list args)
{
	switch(type) {
		case '%':
			tty_printf_append(type);
			break;

		case 'c':
			tty_printf_append(va_arg(args, int));
			break;

		case 's':
			char *str;
			int i;
			
			i = 0;
			str = va_arg(args, char *);
			
			while(str[i]) {
				tty_printf_append(str[i]);
				i++;
			}
			break;

		case 'p':
			__tty_printf_pointer((uint64_t)va_arg(args, void *));
			break;

		case 'd': case 'i':
			__tty_printf_int(va_arg(args, int));
			break;

		case 'u':
			__tty_printf_uint(va_arg(args, uint32_t));
			break;

		case 'x': case 'X':
			__tty_printf_hex(va_arg(args, uint64_t), isupper(type));
			break;
	};
}

static void __tty_parse(const char* str, va_list args)
{
    int i;

    i = -1;
    while(str[++i]) {
		
        if(str[i] == '%' && str[i + 1] != '\0') {
			if(str[i + 1] == '#' && str[i + 1] != '\0') {
				prefix_flag = 1;
				i++;
            	__tty_print_args(str[i + 1], args);
			}
			else
            	__tty_print_args(str[i + 1], args);
            i++;
        }
        else
			tty_printf_append(str[i]);
    }
}

void tty_printf(const char *fmt, ...)
{
    va_list args;

    if(!fmt || *fmt == '\0')
		tty_print("tty_printf: incorrect format\n");
	
	prefix_flag = 0;
	
	bzero(tty_printf_buffer, TTY_PRINTF_BUFFER_SIZE);
	tty_printf_pos = 0;

    va_start(args, fmt);
    __tty_parse(fmt, args);
    va_end(args);

	tty_print(tty_printf_buffer);
}
