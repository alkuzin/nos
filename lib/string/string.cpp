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

#include <nos/types.hpp>
#include <nos/errno.hpp>


namespace kernel {
namespace lib {

// Memory Handeling Functions ----------------------------------------

void bzero(void *s, usize n)
{
    u8 *src = static_cast<u8*>(s);
    
    for (usize i = 0; i < n; i++)
        src[i] = '\0';
}


void *memchr(const void *s, s32 c, usize n)
{
    u8 *src = reinterpret_cast<u8*>(const_cast<void*>(s));
    u8 cc   = static_cast<u8>(c);
    s32 i   = 0;

    while(src[i] && n > 0) {
        if(src[i] == cc)
            return (reinterpret_cast<char*>(src + i));
        i++;
        n--;
    }

    return nullptr;
}

s32 memcmp(const void *s1, const void *s2, usize n)
{
    const u8 *p1 = static_cast<const u8*>(s1);
    const u8 *p2 = static_cast<const u8*>(s2);

    while (n--) {
        if (*p1 != *p2)
            return (*p1 - *p2);

        p1++;
        p2++;
    }

    return 0;
}

void *memcpy(void *dest, const void *src, usize n)
{
    const u8 *csrc;
    u8  *cdest;
    s32 i;

    if (n == 0)
        return dest;

    cdest = reinterpret_cast<u8*>(dest);
    csrc  = reinterpret_cast<const u8*>(src);
    i     = 0;

   	while(csrc[i] && n > 0) {
        cdest[i] = csrc[i];
        n--;
        i++;
    }

    return dest;
}

void *memmove(void *dest, const void *src, usize n)
{
	u8 *ptr_dst = static_cast<u8*>(dest);
	u8 *ptr_src = reinterpret_cast<u8*>(const_cast<void*>(src));

	if (ptr_src > ptr_dst) {
        while (n > 0) {
			*ptr_dst++ = *ptr_src++;
			n--;
		}
	}
	else {
		ptr_src = ptr_src + n - 1;
		ptr_dst = ptr_dst + n - 1;

		while (n > 0) {
			*ptr_dst-- = *ptr_src--;
			n--;
		}
	}
    
	return dest;
}

void *memset(void *s, s32 c, usize n)
{
    u8 *src = static_cast<u8*>(s);
    u8 cc   = static_cast<u8>(c);

    while (n--)
        *src++ = cc;

    return s;
}

// String Handeling Functions ----------------------------------------

char *strchr(const char *s, s32 c)
{
    s32 i = 0;
    
    while(s[i]) {
        if(s[i] == c)
            return (const_cast<char*>(s + i));
        i++;
    }

    if(s[i] == c)
        return (const_cast<char*>(s + i));
    
    return nullptr;
}

const char *strerror(error::ERRNO errnum)
{
    switch (errnum) {
        case error::ERRNO::E2BIG:
            return "Arg list too long";
        case error::ERRNO::EACCES:
            return "Permission denied";
        case error::ERRNO::EAGAIN:
            return "Try again";
        case error::ERRNO::EBADF:
            return "Bad file number";
        case error::ERRNO::EBUSY:
            return "Device or resource busy";
        case error::ERRNO::ECHILD:
            return "No child processes";
        case error::ERRNO::EDEADLK:
            return "Resource deadlock would occur";
        case error::ERRNO::EDOM:
            return "Math argument out of domain of func";
        case error::ERRNO::EEXIST:
            return "File exists";
        case error::ERRNO::EFAULT:
            return "Bad address";
        case error::ERRNO::EFBIG:
            return "File too large";
        case error::ERRNO::EINTR:
            return "Interrupted system call";
        case error::ERRNO::EINVAL:
            return "Invalid argument";
        case error::ERRNO::EIO:
            return "I/O error";
        case error::ERRNO::EISDIR:
            return "Is a directory";
        case error::ERRNO::EMFILE:
            return "Too many open files";
        case error::ERRNO::EMLINK:
            return "Too many links";
        case error::ERRNO::ENAMETOOLONG:
            return "File name too long";
        case error::ERRNO::ENFILE:
            return "File table overflow";
        case error::ERRNO::ENODEV:
            return "No such device";
        case error::ERRNO::ENOENT:
            return "No such file or directory";
        case error::ERRNO::ENOEXEC:
            return "Exec format error";
        case error::ERRNO::ENOLCK:
            return "No record locks available";
        case error::ERRNO::ENOMEM:
            return "Out of memory";
        case error::ERRNO::ENOSPC:
            return "No space left on device";
        case error::ERRNO::ENOSYS:
            return "Function not implemented";
        case error::ERRNO::ENOTDIR:
            return "Not a directory";
        case error::ERRNO::ENOTEMPTY:
            return "Directory not empty";
        case error::ERRNO::ENOTTY:
            return "Not a typewriter";
        case error::ERRNO::ENXIO:
            return "No such device or address";
        case error::ERRNO::EPERM:
            return "Operation not permitted";
        case error::ERRNO::EPIPE:
            return "Broken pipe";
        case error::ERRNO::ERANGE:
            return "Math result not representable";
        case error::ERRNO::EROFS:
            return "Read-only file system";
        case error::ERRNO::ESPIPE:
            return "Illegal seek";
        case error::ERRNO::ESRCH:
            return "No such process";
        case error::ERRNO::EXDEV:
            return "Cross-device link";
        default:
            return "Unknown error";
    }
}

s32 strlen(const char *str)
{
    s32 i = 0;

    while(str[i])
        i++;

    return i;
}

usize strncat(char *dest, const char *src, usize size)
{
    if (!dest || !src)
        return 0;

    usize i      = 0;
    s32 dest_len = strlen(dest);
    s32 src_len  = strlen(src);

    if(size <= static_cast<usize>(src_len))
        return (size + src_len);

    while(src[i] && (i < size - dest_len)) {
        dest[dest_len + i] = src[i];
        i++;
    }
    dest[i + dest_len] = '\0';

    return (dest_len + src_len);
}

s32 strncmp(const char *s1, const char *s2, usize n)
{
    usize i = 0;
    
    while((i < n) && (s1[i] || s2[i])) {
        if(s1[i] != s2[i])
            return (s1[i] - s2[i]);
        i++;
    }

    return 0;
}

usize strncpy(char *dest, const char *src, usize size)
{
    usize i = 0;

    while(src[i] && i < size) {
        dest[i] = src[i];
        i++;
    }

    dest[i] = '\0';
    return i;
}

char *strnstr(const char *big, const char *little, usize len)
{
    s32   little_len;
    usize i, j;

    if(!big || len == 0)
        return nullptr;
    
    if(!little)
       return ((char *)(big));

    i = 0;
    little_len = strlen(little);
    
    while(big[i] && i < len) {
        
        if(big[i] == little[0]) {
            j = 0;

            while(little[j]) {
                if(big[i + j] != little[j])
                    break;
                j++;
            }

            if(j == static_cast<usize>(little_len))
                return (const_cast<char*>(big + i));
        }
        i++;
    }
    
    return nullptr; 
}

char *strpbrk(const char *str, const char *accept)
{
    const char *s, *a;

    for (s = str; *s != '\0'; s++) {
        for (a = accept; *a != '\0'; a++) {
            if (*s == *a)
                return const_cast<char*>(s);
        }
    }

    return nullptr;
}

char *strrchr(const char *s, s32 c)
{
    int i = strlen(s);
    
    if(s[i] == c)
        return (const_cast<char*>(s + i));

    while(i >= 0) {
        if(s[i] == c)
            return (const_cast<char*>(s + i));
        i--;
    }
    
    return nullptr;
}

char *strtok(char *str, const char *delim)
{
    static char *token = nullptr;

    if (str)
        token = str;
    else if (!token)
        return nullptr;
    
    char *start = token;
    char *end   = strpbrk(token, delim);

    if (end) {
        *end  = '\0';
        token = end + 1;
    } 
    else
        token = nullptr;

    return start;
}

} // namespace lib
} // namespace kernel