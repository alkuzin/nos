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

#include <nos/printk.h>
#include <nos/string.h>
#include <nos/stdarg.h> 
#include <nos/ctype.h> 
#include <nos/panic.h>
#include <nos/math.h>

/** For null pointer in vsnprintk. */
#define __NIL__ "(nil)"

/** Print buffer info struct. */
typedef struct pinfo_s {
    char  *buf; 
    usize size; 		/** Buffer size. */
    s32   pos;  		/** Current buffer position. */
    s32   pref_flag; 	/** '#' flag */
} pinfo_t;

static pinfo_t  pinfo;

/**
 * @brief Initialize pinfo struct.
 * 
 * @param [out] buf - given buffer for containing printk output.
 * @param [in] size - given size of the buffer.
 */
static void pinfo_init(char *buf, usize size);

/**
 * @brief Append character to pinfo struct buffer.
 * 
 * @param [in] c - given character to append.
 */
static void  buf_append(char c);

/**
 * @brief %x %X options (hexadecimal).
 * 
 * @param [in] n - given number to convert.
 * @param [in] is_upper - given is uppercase/lowercase flag.
 */
static void  print_hex(u64 n, s32 is_upper);

/**
 * @brief Hexadecimal to alphanumeric lenght.
 * 
 * @param [in] n - given number.
 * @return length of hex string representation of @a n.
 */
static s32   xtoa_len(u32 n);

/**
 * @brief %i %d options (int)
 * 
 * @param [in] n - given number to convert.
 */
static void  print_int(s32 n);

/**
 * @brief Integer to alphanumeric lenght.
 * 
 * @param [in] n - given number.
 * @return length of int string representation of @a n.
 */
static usize itoa_len(s32 n);

/**
 * @brief %p option (pointer).
 * 
 * @param [in] p - given pointer to convert.
 */
static void  print_ptr(u64 p);

/**
 * @brief Digit to hex.
 * 
 * @param [in] v - given digit to convert. 
 * @return hex representation of digit.
 */
static char  dtoh(s32 v);

/**
 * @brief %u option (unsigned int).
 * 
 * @param [in] n - given number.
 */
static void  print_uint(u32 n);

/**
 * @brief Unsigned s32 to alphanumeric lenght.
 * 
 * @param [in] n - given number.
 * @return length of unsigned int string representation of @a n.
 */
static usize utoa_len(u32 n);

/**
 * @brief Print vsnprintk arguments.
 * 
 * @param [in] type - given type of argument.
 * @param [in] args - given list of arguments.
 */
static void  print_args(char type, va_list * args);

/**
 * @brief Parse printk arguments.
 * 
 * @param [in] str - given format string.
 * @param [in] args - given list of arguments.
 */
static void  parse(const char* str, va_list * args);


static void pinfo_init(char *buf, usize size)
{
    /* set pinfo struct */
	bzero(&pinfo, sizeof(pinfo));
	bzero(buf, size);
    pinfo.buf  = buf;
    pinfo.size = size;
    pinfo.pos  = 0;

    /* set pinfo struct flags */
    pinfo.pref_flag = 0;
}

/* append character to vsnprintf buffer */
static void buf_append(char c)
{
	pinfo.buf[pinfo.pos] = c;
	pinfo.pos++;
}

/* kprintf unsigned s32 */
static usize utoa_len(u32 n)
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

static void print_uint(u32 n)
{
	usize length, i;

	i      = utoa_len(n);
	length = i;

	char uint_buffer[i];

	i--;

	while (i) {
		uint_buffer[i] = (n % 10) + '0';
		n /= 10;
		i--;
	}

	uint_buffer[0]      = (n % 10) + '0';
	uint_buffer[length] = '\0';

	i = 0;

    // TODO: use width alignment flag here
	while (uint_buffer[i]) {
		buf_append(uint_buffer[i]);
		i++;
	}
}

/* kprintf pointer */
static char dtoh(s32 v) 
{
   if (v >= 0 && v < 10)
       return '0' + v;
   else
       return 'a' + v - 10;
}

static void print_ptr(u64 p)
{
	s32 count, i;
		
	if(p == 0) {
		i = 0;
		
		while(__NIL__[i]) {
			buf_append(__NIL__[i]);
			i++;
		}
		
		return;
	}
	
	buf_append('0');
	buf_append('x');
	
	i     = (sizeof(p) << 3) - 4;	
	count = 0;

	/* skip first zeros */
	while(i >= 0 && ((dtoh((p >> i) & 0xf) == '0')))
		i -= 4;
	
	while(i >= 0) {
		buf_append(dtoh((p >> i) & 0xf));
		i -= 4;
		count++;
	}
}

/* kprintf s32 */
static usize itoa_len(s32 n)
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

static void print_int(s32 n)
{
	usize length, i;

	i      = itoa_len(n);
	length = i;

	char int_buffer[length];
	i--;

	if (n < 0) {
		int_buffer[0] = '-';
		n = -n;
	}

	while (i) {
		int_buffer[i] = (n % 10) + '0';
		n /= 10;
		i--;
	}
	
	if (int_buffer[0] != '-')
		int_buffer[0] = (n % 10) + '0';

	int_buffer[length] = '\0';
	
	while (int_buffer[i]) {
		buf_append(int_buffer[i]);
		i++;
	}
}

/* kprintf hex */
static s32 xtoa_len(u32 n)
{
	if (n == 0)
	   return 1;
	
	return (s32)(log(n) / log(16)) + 1;
}

static void print_hex(u64 n, s32 is_upper)
{
	static const char digits_lower[] = "0123456789abcdef";
	static const char digits_upper[] = "0123456789ABCDEF";
	static const char *digits        = nullptr;
	s32               i;
	
	i = xtoa_len(n);
	char hex[i + 1];
	
	if(pinfo.pref_flag) {
		buf_append('0');
		buf_append('x');
        pinfo.pref_flag = 0;
	}
	
	if(n == 0) {
		buf_append('0');
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
	i      = 0;
		
	while(hex[i] == '0')
		i++;

	while(hex[i]) {
		buf_append(hex[i]);
		i++;
	}
}

static void print_args(char type, va_list *args)
{
	switch(type) {
		case '%':
			buf_append(type);
			break;

		case 'c':
			buf_append(va_arg(*args, int));
			break;

		case 's':
			char *str;
			s32 i;
			
			i = 0;
			str = va_arg(*args, char *);
			
			while(str[i]) {
				buf_append(str[i]);
				i++;
			}
			break;

		case 'p':
			print_ptr((u64)va_arg(*args, void *));
			break;

		case 'd': case 'i':
		    print_int(va_arg(*args, int));
			break;

		case 'u':
			print_uint(va_arg(*args, u32));
			break;

		case 'x': case 'X':
			print_hex(va_arg(*args, u64), isupper(type));
			break;
	};
}

static void parse(const char *str, va_list *args)
{
    s32 i;

    i = -1;

    while(str[++i]) {

        if(str[i] == '%' && str[i + 1] != '\0') {
			
            if(str[i + 1] == '#' && str[i + 1] != '\0') {
                pinfo.pref_flag = 1;
				i++;
                print_args(str[i + 1], args);
			}
			else
            	print_args(str[i + 1], args);
            i++;
        }
        else
			buf_append(str[i]);
    }
}

void vsnprintk(char *buf, usize size, const char *fmt, va_list args)
{
    va_list args_copy;

    if(!fmt || *fmt == '\0')
		panic("%s\n", "incorrect format string");
	
    pinfo_init(buf, size);

    va_copy(args_copy, args);
    parse(fmt, &args);
    va_end(args_copy);
}