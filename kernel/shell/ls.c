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


#include <nos/shell/ls.h>
#include <nos/string.h>
#include <nos/initrd.h>
#include <nos/printk.h>
#include <nos/types.h>
#include <nos/login.h>

static ls_t ls;

/** @brief Print directory content. */
static void ls_printdir(void);

/**
 * @brief Get file type in char format.
 * 
 * @param [in] mode - given file mode.
 * @return character representation of type of the file.
 */
static char ls_get_type(mode_t mode);

/**
 * @brief Get file mode in string format.
 * 
 * @param [out] buffer - given buffer to store mode.
 * @param [in] mode - given file mode.
 */
static void ls_get_mode(char *buffer, mode_t mode);


void ksh_ls(void)
{
    ls_file_t *file;
    s32       ret;

    strncpy(ls.dirname, ".", 1); /* current directory by default */
    ls.count = initrd_get_count();

    for (u32 i = 0; i < ls.count; i++) {
        file = &ls.files[i];
        ret  = initrd_opendir(".", &file->stat);

        ls_get_mode(file->mode, file->stat.mode);

        if (ret == -1) {
            printk("ls: %s\n", "get initrd stat error");
            return;
        }
    }

    ls_printdir();
    
    printk(" \ntotal files: %u/%u\n", ls.count, INITRD_MAX_FILES);
}

static void ls_printdir(void)
{
    char user[MAX_USERNAME_SIZE];
    ls_file_t *file;

    strncpy(user, USERNAME, MAX_USERNAME_SIZE);

    for (u32 i = 0; i < ls.count; i++) {
        file = &ls.files[i];

        printk("%s  %u %s %s %u bytes   %s\n", file->mode, file->stat.fd, user, user,
        file->stat.size, file->stat.name);
    }
}

static char ls_get_type(mode_t mode)
{
    switch (S_IFMT & mode) {
        case S_IFREG:
            return '-';
        case S_IFDIR:
            return 'd';
        case S_IFCHR:
            return 'c';
        case S_IFBLK:
            return 'b';
        case S_IFIFO:
            return 'p';
        case S_IFSOCK:
            return 's';
        case S_IFLNK:
            return 'l';
        default:
            return '?';
    }
}

static void ls_get_mode(char *buffer, mode_t mode)
{
    buffer[0] = ls_get_type(mode);
    buffer[1] = (S_IRUSR & mode) ? 'r' : '-';
    buffer[2] = (S_IWUSR & mode) ? 'w' : '-';
    buffer[3] = (S_IXUSR & mode) ? 'x' : '-';
    buffer[4] = (S_IRGRP & mode) ? 'r' : '-';
    buffer[5] = (S_IWGRP & mode) ? 'w' : '-';
    buffer[6] = (S_IXGRP & mode) ? 'x' : '-';
    buffer[7] = (S_IROTH & mode) ? 'r' : '-';
    buffer[8] = (S_IWOTH & mode) ? 'w' : '-';
    buffer[9] = (S_IXOTH & mode) ? 'x' : '-';
}