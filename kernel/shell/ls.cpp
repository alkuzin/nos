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

#include <kernel/kstd/cstring.hpp>
#include <kernel/kstd/cstdio.hpp>
#include <kernel/fs/initrd.hpp>
#include <kernel/shell/ls.hpp>
#include <kernel/login.hpp>


namespace kernel {
namespace shell {


static ls_t _ls;

/** @brief Print directory content.*/
static void printdir(void);

/**
 * @brief Get file type in char format.
 * 
 * @param [in] mode - given file mode.
 * @return character representation of type of the file.
 */
static char get_type(mode_t mode);

/**
 * @brief Get file mode in string format.
 * 
 * @param [out] buffer - given buffer to store mode.
 * @param [in] mode - given file mode.
 */
static void get_mode(char *buffer, mode_t mode);


void ls(void)
{
    ls_file *file;
    s32     ret;

    kstd::strncpy(_ls.dirname, ".", 1); /* current directory by default */
    _ls.count = fs::initrd::get_count();

    for (u32 i = 0; i < _ls.count; i++) {
        file = &_ls.files[i];
        ret  = fs::initrd::opendir(".", &file->stat);

        get_mode(file->mode, file->stat.mode);

        if (ret == -1) {
            kstd::printk("ls: %s\n", "get initrd stat error");
            return;
        }
    }

    printdir();
    
    kstd::printk(" \ntotal files: %u/%u\n", _ls.count, fs::initrd::INITRD_MAX_FILES);
}

static void printdir(void)
{
    char user[MAX_USERNAME_SIZE];
    ls_file *file;

    kstd::strncpy(user, USERNAME, MAX_USERNAME_SIZE);

    for (u32 i = 0; i < _ls.count; i++) {
        file = &_ls.files[i];

        kstd::printk("%s  %u %s %s %u bytes   %s\n", file->mode, file->stat.fd, user, user,
        file->stat.size, file->stat.name);
    }
}

static char get_type(mode_t mode)
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

static void get_mode(char *buffer, mode_t mode)
{
    buffer[0] = get_type(mode);
    buffer[1] = ((S_IRUSR) & mode) ? 'r' : '-';
    buffer[2] = ((S_IWUSR) & mode) ? 'w' : '-';
    buffer[3] = ((S_IXUSR) & mode) ? 'x' : '-';
    buffer[4] = ((S_IRGRP) & mode) ? 'r' : '-';
    buffer[5] = ((S_IWGRP) & mode) ? 'w' : '-';
    buffer[6] = ((S_IXGRP) & mode) ? 'x' : '-';
    buffer[7] = ((S_IROTH) & mode) ? 'r' : '-';
    buffer[8] = ((S_IWOTH) & mode) ? 'w' : '-';
    buffer[9] = ((S_IXOTH) & mode) ? 'x' : '-';
}

} // namespace shell
} // namespace kernel