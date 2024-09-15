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

#include <nos/shell/ls.hpp>
#include <nos/string.hpp>
#include <nos/initrd.hpp>
#include <nos/printk.hpp>
#include <nos/login.hpp>


namespace kernel {
namespace shell {

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

    lib::strncpy(ls.dirname, ".", 1); /* current directory by default */
    ls.count = fs::initrd_get_count();

    for (u32 i = 0; i < ls.count; i++) {
        file = &ls.files[i];
        ret  = initrd_opendir(".", &file->stat);

        ls_get_mode(file->mode, file->stat.mode);

        if (ret == -1) {
            lib::printk("ls: %s\n", "get initrd stat error");
            return;
        }
    }

    ls_printdir();
    
    lib::printk(" \ntotal files: %u/%u\n", ls.count, INITRD_MAX_FILES);
}

static void ls_printdir(void)
{
    char user[MAX_USERNAME_SIZE];
    ls_file_t *file;

    lib::strncpy(user, USERNAME, MAX_USERNAME_SIZE);

    for (u32 i = 0; i < ls.count; i++) {
        file = &ls.files[i];

        lib::printk("%s  %u %s %s %u bytes   %s\n", file->mode, file->stat.fd, user, user,
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

} // namespace shell
} // namespace kernel