/*
MIT License

Copyright (c) 2024 Alexander (@alkuzin)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

the above copyright notice and this permission notice shall be included in all
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

int strlen(const char *str)
{
    int i;

    i = 0;
    while(str[i])
        i++;

    return i;
}

int strncmp(char *s1, char *s2, size_t n)
{
    size_t i;

    i = 0;
    while(i < n && (s1[i] || s2[i])) {
        if(s1[i] != s2[i])
            return (s1[i] - s2[i]);
        i++;
    }
    return 0;
}

size_t strlcpy(char *dest, const char *src, size_t size)
{
    size_t i;

    i = 0;
    while(src[i] && i < size - 1) {
        dest[i] = src[i];
        i++;
    }

    dest[i] = '\0';
    return i;
}

size_t strlcat(char *dest, const char *src, size_t size)
{
    int dest_len, src_len;
    size_t i;

    if (!dest || !src)
        return 0;

    dest_len = ft_strlen(dest);
    src_len = ft_strlen(src);
    i = 0;

    if(size <= (size_t)src_len)
        return (size + src_len);

    while(src[i] && i < size - dest_len) {
        dest[dest_len + i] = src[i];
        i++;
    }
    dest[i + dest_len] = '\0';

    return (dest_len + src_len);
}

char *strchr(const char *s, int c)
{
    int i;

    i = 0;
    while(s[i]) {
        if(s[i] == c)
            return ((char *)(s + i));
        i++;
    }

    if(s[i] == c)
        return ((char *)(s + i));

    return NULL;
}

char *strrchr(const char *s, int c)
{
    int i;
    
    i = strlen(s);
    
    if(s[i] == c)
        return ((char *)(s + i));

    while(i >= 0) {
        if(s[i] == c)
            return ((char *)(s + i));
        i--;
    }
    
    return NULL;
}

char *strnstr(const char *big, const char *little, size_t len)
{
    size_t i, j;
    int little_len;

    if(!big || len == 0)
        return NULL;

    if(!little)
       return ((char *)(big));

    i = 0;
    little_len = ft_strlen(little);

    while(big[i] && i < len) {
        if(big[i] == little[0]) {
            j = 0;
            while(little[j]) {
                if(big[i + j] != little[j])
                    break;
                j++;
			}

            if(j == (size_t)little_len)
                return ((char *)big + i);
        }
        i++;
    }
    return NULL;
}
