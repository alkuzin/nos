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

#include <string.h>
#include <stddef.h> 
#include <stdarg.h> 
#include <ctype.h> 
#include <math.h>

#include <nos/kernel.h>
#include <nos/tty.h>

#define K_PRINTF_BUFFER_SIZE 1024

static char kprintf_buffer[K_PRINTF_BUFFER_SIZE] = {0};
static i32  kprintf_pos = 0;
static i32  prefix_flag = 0; /* '#' prefix flag */

/* append character to kprintf buffer */
static void kprintf_append(char c);

/* %x %X options (hexadecimal) */
static void   __kprintf_hex(u64 n, i32 is_upper);

/* hexadecimal to alphanumeric lenght */
static i32    __kxtoa_len(u32 n);

/* %i %d options (int) */
static void   __kprintf_int(i32 n);

/* i32 to alphanumeric lenght */
static usize __kitoa_len(i32 n);

/* %p option (pointer) */
static void   __kprintf_pointer(u64 p);

/* digit to hex */
static char   __kdtoh(i32 v);

/* %u option (unsigned int) */
static void   __kprintf_uint(u32 n);

/* unsigned i32 to alphanumeric lenght */
static usize __kutoa_len(u32 n);

/* pri32 kprintf arguments */
static void   __kprint_args(char type, va_list * args);

/* parse kprintf arguments */
static void   __kparse(const char* str, va_list * args);


/* append character to kprintf buffer */
static void kprintf_append(char c)
{
	kprintf_buffer[kprintf_pos] = c;
	kprintf_pos++;
}

/* kprintf unsigned i32 */
static usize __kutoa_len(u32 n)
{
	usize len;

	len = 0;

	if (n == 0)
		return 1;

	while (n >= 1) {
		len++;
		n /= 10;
	}

	return len;
}

static void __kprintf_uint(u32 n)
{
	usize length, i;

	i = __kutoa_len(n);
	length   = i;

	char buffer[i];

	i--;
	while (i) {
		buffer[i] = (n % 10) + '0';
		n /= 10;
		i--;
	}

	buffer[0] = (n % 10) + '0';
	buffer[length] = '\0';

	i = 0;

	while (buffer[i]) {
		kprintf_append(buffer[i]);
		i++;
	}
}

/* kprintf pointer */
static char __kdtoh(i32 v) 
{
   if (v >= 0 && v < 10)
       return '0' + v;
   else
       return 'a' + v - 10;
}

static void __kprintf_pointer(u64 p)
{
	i32 count, i;
		
	if(p == 0) {
		i = 0;
		
		while(__NIL__[i]) {
			kprintf_append(__NIL__[i]);
			i++;
		}
		
		return;
	}
	
	kprintf_append('0');
	kprintf_append('x');
	
	count = 0;
	i = (sizeof(p) << 3) - 4;	

	/* skip first zeros */
	while(i >= 0 && ((__kdtoh((p >> i) & 0xf) == '0')))
		i -= 4;
	
	while(i >= 0) {
		kprintf_append(__kdtoh((p >> i) & 0xf));
		i -= 4;
		count++;
	}
}

/* kprintf i32 */
static usize __kitoa_len(i32 n)
{
	usize len;

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

static void __kprintf_int(i32 n)
{
	usize length, i;

	i = __kitoa_len(n);
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
		kprintf_append(buffer[i]);
		i++;
	}
}

/* kprintf hex */
static i32 __kxtoa_len(u32 n)
{
	if (n == 0)
	   return 1;
	
	return (int)(log(n) / log(16)) + 1;
}

static void __kprintf_hex(u64 n, i32 is_upper)
{
	static const char digits_lower[] = "0123456789abcdef";
	static const char digits_upper[] = "0123456789ABCDEF";
	static const char *digits = NULL;
	i32 i;
	
	i = __kxtoa_len(n);
	char hex[i + 1];
	
	if(prefix_flag) {
		kprintf_append('0');
		kprintf_append('x');
		prefix_flag = 0;
	}
	
	if(n == 0) {
		kprintf_append('0');
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

	hex[8] = '\0';
	i = 0;
		
	while(hex[i] == '0')
		i++;

	while(hex[i]) {
		kprintf_append(hex[i]);
		i++;
	}
}

static void __kprint_args(char type, va_list *args)
{
	switch(type) {
		case '%':
			kprintf_append(type);
			break;

		case 'c':
			kprintf_append(va_arg(*args, int));
			break;

		case 's':
			char *str;
			i32 i;
			
			i = 0;
			str = va_arg(*args, char *);
			
			while(str[i]) {
				kprintf_append(str[i]);
				i++;
			}
			break;

		case 'p':
			__kprintf_pointer((u64)va_arg(*args, void *));
			break;

		case 'd': case 'i':
			__kprintf_int(va_arg(*args, int));
			break;

		case 'u':
			__kprintf_uint(va_arg(*args, u32));
			break;

		case 'x': case 'X':
			__kprintf_hex(va_arg(*args, u64), isupper(type));
			break;
	};
}

static void __kparse(const char* str, va_list *args)
{
    i32 i;

    i = -1;
    while(str[++i]) {
		
        if(str[i] == '%' && str[i + 1] != '\0') {
			if(str[i + 1] == '#' && str[i + 1] != '\0') {
				prefix_flag = 1;
				i++;
            	__kprint_args(str[i + 1], args);
			}
			else
            	__kprint_args(str[i + 1], args);
            i++;
        }
        else
			kprintf_append(str[i]);
    }
}

void kprintf(const char *fmt, ...)
{
    va_list args;

    if(!fmt || *fmt == '\0')
		panic("%s\n", "incorrect format in kprintf()");
	
    va_start(args, fmt);
    kvprintf(fmt, args);
    va_end(args);
}

void kvprintf(const char *fmt, va_list args)
{
    va_list args_copy;

    if(!fmt || *fmt == '\0')
		panic("%s\n", "incorrect format in kvprintf()");
	
	kprintf_pos = 0;
	prefix_flag = 0;
	bzero(kprintf_buffer, K_PRINTF_BUFFER_SIZE);

    va_copy(args_copy, args);
    __kparse(fmt, &args);
    va_end(args_copy);

	kprint(kprintf_buffer);
}
