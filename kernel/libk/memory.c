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

#include <libk/memory.h>
#include <libk/stdint.h>

void *memset(void *s, int c, size_t n)
{
    uint8_t *src;
    uint8_t cc;
    int i;

    src = (uint8_t *)s;
    cc  = (uint8_t)c;
    i = 0;

    while(n-- && src[i]) {
        src[i] = cc;
        i++;
    }

    return s;
}

void bzero(void *s, size_t n)
{
    uint8_t *src;
    int i;

    src = (uint8_t *)s;
    i = 0;

    while(src[i] && n > 0) {
        src[i] = '\0';
        i++;
        n--;
    }
}

void *memcpy(void *dest, const void *src, size_t n)
{
    const uint8_t *csrc;
    uint8_t *cdest;
    int i;

    if (n == 0)
        return dest;


    cdest = (uint8_t *)dest;
    csrc = (const uint8_t *)src;
    i = 0;

   	while(csrc[i] && n > 0) {
        cdest[i] = csrc[i];
        n--;
        i++;
    }

    return dest;
}

void *memccpy(void *dest, const void *src, int c, size_t n)
{
    uint8_t *cdest, *target;
    const uint8_t *csrc;
    size_t i;

    cdest = (uint8_t *)dest;
    csrc  = (const uint8_t *)src;

    if ((target = memchr(src, c, n)) == NULL)
        return NULL;

    i = 0;

    while(csrc[i]) {
        cdest[i] = csrc[i];

        if(&csrc[i] == target)
            return dest;

        i++;
    }

    return NULL;
}

void *memmove(void *dest, const void *src, size_t n)
{
    uint8_t *ptr_src, *ptr_dst;

	ptr_dst = (uint8_t *)dest;
	ptr_src = (uint8_t *)src;
	
	if (ptr_src > ptr_dst){
		while (n > 0){
			*ptr_dst++ = *ptr_src++;
			n--;
		}
	}
	else{
		ptr_src = ptr_src + n - 1;
		ptr_dst = ptr_dst + n - 1;
		
		while (n > 0){
			*ptr_dst-- = *ptr_src--;
			n--;
		}
	}

	return dest;
}

void *memchr(const void *s, int c, size_t n)
{
    uint8_t *src;
    uint8_t cc;
    int i;

    src = (uint8_t*)s;
    cc  = (uint8_t)c;
    i = 0;

    while(src[i] && n > 0) {
        if(src[i] == cc)
            return ((char *)(src + i));

        i++;
        n--;
    }

    return NULL;
}

int memcmp(const void *s1, const void *s2, size_t n)
{
	while(n--) {
		if(*(uint8_t *)s1++ != *(uint8_t *)s2++)
			return (*(uint8_t *)s1 - *(uint8_t *)s2);
	}

	return 0;
}
