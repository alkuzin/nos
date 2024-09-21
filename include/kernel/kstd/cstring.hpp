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

/**
 * @file  cstring.hpp
 * @brief Defines several strings and memory management functions.
 *
 * @details This header file provides functions for manipulating strings,
 * such as copying, concatenating and comparing.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   15.05.2024 
 */

#ifndef _KERNEL_KSTD_CSTRING_HPP_
#define _KERNEL_KSTD_CSTRING_HPP_

#include <kernel/kstd/types.hpp>
#include <kernel/kstd/errno.hpp>


namespace kernel {
namespace kstd {

// Memory Handeling Functions ----------------------------------------

/**
 * @brief Erases the data in the n bytes 
 * of the memory of the area pointed to by s, 
 * by writing '\0' bytes to that area.
 * 
 * @param [out] s - given buffer pointer.
 * @param [in] n - given number of buffer bytes to erase.
 */
constexpr inline void bzero(void *s, usize n) noexcept
{
    u8 *src = static_cast<u8*>(s);
    
    for (usize i = 0; i < n; i++)
        src[i] = '\0';
}

/**
 * @brief Copies n bytes from memory area src to memory area dest.
 * 
 * @param [out] dest - given destination buffer.
 * @param [in] src - given source buffer.
 * @param [in] n - given number of bytes to copy.
 * @return destination buffer pointer.
 */
constexpr void *memcpy(void *dest, const void *src, usize n) noexcept
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

/**
 * @brief Copies @a n bytes from memory area @a src to memory area @a dest.
 * 
 * @param [out] dest - given destination buffer.
 * @param [in] src - given source buffer.
 * @param [in] n - given number of bytes to copy.
 * @return destination buffer pointer.
 */
constexpr void *memmove(void *dest, const void *src, usize n) noexcept
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

/**
 * @brief Compares the first n bytes (each interpreted as unsigned char) 
 * of the memory areas s1 and s2.
 * 
 * @param [in] s1 - first given memory area pointer.
 * @param [in] s2 - second given memory area pointer.
 * @param [in] n - given number of bytes to compare.
 * @return 0, if s1 and s2 are equal;
 * @return a negative value if s1 is less than s2;
 * @return a positive value if s1 is greater than s2.
 */
constexpr s32 memcmp(const void *s1, const void *s2, usize n) noexcept
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

/**
 * @brief Fills the first n bytes of the memory of the area pointed to by s 
 * with the constant byte c.
 * 
 * @param [out] s - given buffer pointer.
 * @param [in] c - given byte for filling buffer.
 * @param [in] n - given number of buffer bytes to fill.
 * @return filled buffer pointer.
 */
constexpr void *memset(void *s, s32 c, usize n) noexcept
{
    u8 *src = static_cast<u8*>(s);
    u8 cc   = static_cast<u8>(c);

    while (n--)
        *src++ = cc;

    return s;
}

/**
 * @brief Scans the initial @a n bytes of the memory area 
 * pointed to by @a s for the first instance of @a c.
 * 
 * @param [in] s - given pointer to the memory block to be searched.
 * @param [in] c - given character to be located.
 * @param [in] n - given number of bytes to be searched.
 * @return pointer to the located character in case of success.
 * @return nullptr - otherwise.
 */
constexpr void *memchr(const void *s, s32 c, usize n) noexcept
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

/**
 * @brief Get string length.
 * 
 * @param [in] str - given null terminated string.
 * @return str length.
 */
constexpr inline s32 strlen(const char *str) noexcept
{
    s32 i = 0;

    while(str[i])
        i++;

    return i;
}

/**
 * @brief Compares the two strings s1 and s2.
 * 
 * @param [in] s1 - first given null terminated string.
 * @param [in] s2 - second given null terminated string.
 * @param [in] n - given number of symbols for comparison.
 * @return 0, if s1 and s2 are equal;
 * @return a negative value if s1 is less than s2;
 * @return a positive value if s1 is greater than s2.
 */
constexpr s32 strncmp(const char *s1, const char *s2, usize n) noexcept
{
    usize i = 0;
    
    while((i < n) && (s1[i] || s2[i])) {
        if(s1[i] != s2[i])
            return (s1[i] - s2[i]);
        i++;
    }

    return 0;
}

/**
 * @brief Copy a string with truncation.
 * 
 * @param [out] dest - given buffer for copied string.
 * @param [in] src - given source null terminated string.
 * @param [in] size - given size to copy.
 * @return number of copied string characters.
 */
constexpr usize strncpy(char *dest, const char *src, usize size) noexcept
{
    usize i = 0;

    while(src[i] && i < size) {
        dest[i] = src[i];
        i++;
    }

    dest[i] = '\0';
    return i;
}

/**
 * @brief Catenate a string with truncation.
 * 
 * @param [out] dest - given buffer for concatenated string.
 * @param [in] src - given source null terminated string.
 * @param [in] size - given size to concatenate.
 * @return length of new concatenated string.
 */
constexpr usize strncat(char *dest, const char *src, usize size) noexcept
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

/**
 * @brief Search a string for any of a set of bytes.
 * 
 * @param [in] str - given string.
 * @param [in] accept - given string to find.
 * @return pointer to the byte in s that matches one of the bytes in accept.
 * @return nullptr if no such byte is found.
 */
constexpr char *strpbrk(const char *str, const char *accept) noexcept
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

/**
 * @brief Breaks a string into a sequence of zero or more nonempty tokens.
 * 
 * On the first call to strtok(), the string to be parsed should be specified in str.
 * In each subsequent call that should parse the same string, str must be nullptr.
 * 
 * @param [in] str - given string to parse. 
 * @param [in] delim - given set of bytes that delimit the tokens in the parsed string.
 * @return pointer to the next token.
 * @return nullptr if there are no more tokens.
 */
constexpr char *strtok(char *str, const char *delim) noexcept
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

/**
 * @brief Returns a pointer to the first occurrence of the character @a c in the string @a s.
 * 
 * @param [in] s - given source string.
 * @param [in] c - given character to find.
 * @return pointer to the first occurrence of @a c in @a s - in case of success.
 * @return nullptr - otherwise.
 */
constexpr char *strchr(const char *s, s32 c) noexcept
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

/**
 * @brief Returns a pointer to the last occurrence of the character @a c in the string @a s.
 * 
 * @param [in] s - given source string.
 * @param [in] c - given character to find.
 * @return pointer to the last occurrence of @a c in @a s - in case of success.
 * @return nullptr - otherwise.
 */
constexpr char *strrchr(const char *s, s32 c) noexcept
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

/**
 * @brief Locates the first occurrence of the null-terminated string @a little
 * in the string @a big, where not more than @a len characters are searched.
 * 
 * @param [in] big - given string to find.
 * @param [in] little - given source string.
 * @param [in] len - given number of characters of @a little to search.
 * @return pointer to the first occurrence of the string @a little in string @a big.
 */
constexpr char *strnstr(const char *big, const char *little, usize len) noexcept
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

/**
 * @brief Retrieve a string describing the error code.
 * 
 * @param [in] errnum - given error code. 
 * @return pointer to a string describing the error code.
 */
constexpr const char *strerror(ERRNO errnum) noexcept
{
    switch (errnum) {
        case ERRNO::E2BIG:
            return "Arg list too long";
        case ERRNO::EACCES:
            return "Permission denied";
        case ERRNO::EAGAIN:
            return "Try again";
        case ERRNO::EBADF:
            return "Bad file number";
        case ERRNO::EBUSY:
            return "Device or resource busy";
        case ERRNO::ECHILD:
            return "No child processes";
        case ERRNO::EDEADLK:
            return "Resource deadlock would occur";
        case ERRNO::EDOM:
            return "Math argument out of domain of func";
        case ERRNO::EEXIST:
            return "File exists";
        case ERRNO::EFAULT:
            return "Bad address";
        case ERRNO::EFBIG:
            return "File too large";
        case ERRNO::EINTR:
            return "Interrupted system call";
        case ERRNO::EINVAL:
            return "Invalid argument";
        case ERRNO::EIO:
            return "I/O error";
        case ERRNO::EISDIR:
            return "Is a directory";
        case ERRNO::EMFILE:
            return "Too many open files";
        case ERRNO::EMLINK:
            return "Too many links";
        case ERRNO::ENAMETOOLONG:
            return "File name too long";
        case ERRNO::ENFILE:
            return "File table overflow";
        case ERRNO::ENODEV:
            return "No such device";
        case ERRNO::ENOENT:
            return "No such file or directory";
        case ERRNO::ENOEXEC:
            return "Exec format error";
        case ERRNO::ENOLCK:
            return "No record locks available";
        case ERRNO::ENOMEM:
            return "Out of memory";
        case ERRNO::ENOSPC:
            return "No space left on device";
        case ERRNO::ENOSYS:
            return "Function not implemented";
        case ERRNO::ENOTDIR:
            return "Not a directory";
        case ERRNO::ENOTEMPTY:
            return "Directory not empty";
        case ERRNO::ENOTTY:
            return "Not a typewriter";
        case ERRNO::ENXIO:
            return "No such device or address";
        case ERRNO::EPERM:
            return "Operation not permitted";
        case ERRNO::EPIPE:
            return "Broken pipe";
        case ERRNO::ERANGE:
            return "Math result not representable";
        case ERRNO::EROFS:
            return "Read-only file system";
        case ERRNO::ESPIPE:
            return "Illegal seek";
        case ERRNO::ESRCH:
            return "No such process";
        case ERRNO::EXDEV:
            return "Cross-device link";
        default:
            return "Unknown error";
    }
}

} // namespace kstd
} // namespace kernel

#endif // _KERNEL_KSTD_CSTRING_HPP_