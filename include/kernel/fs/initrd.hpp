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
 * @file  initrd.hpp
 * @brief Initial ramdisk file system driver.
 * 
 * @details Initial ramdisk is a temporary file system used by the kernel during the boot process 
 * before the actual root file system is mounted.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   08.06.2024
 */

#ifndef _KERNEL_FS_INITRD_HPP_
#define _KERNEL_FS_INITRD_HPP_

#include <kernel/fs/fcntl.hpp>
#include <kernel/fs/stat.hpp>
#include <kernel/fs/vfs.hpp>


namespace kernel {
namespace fs {
namespace initrd {

constexpr u32 INITRD_MAX_NAME_SIZE {MAX_FILENAME_SIZE};
constexpr u32 INITRD_MAX_FILES     {16};
constexpr u32 INITRD_FILE_SIZE     {1024}; // 1KB

// file states
constexpr u32 INITRD_FILE_OPENED {1};
constexpr u32 INITRD_FILE_CLOSED {2};

/** @brief Initrd file structure.*/
struct file {
    char    name[INITRD_MAX_NAME_SIZE]; // Name of the file.
    u8      data[INITRD_FILE_SIZE];     // File content.
    u32     size;                       // Size of the file in bytes.
    mode_t  mode;                       // File permissions.
    s32     fd;                         // File descriptor.
    u32     state;                      // File state (e.g. opened/closed/etc.).
    u32     type;                       // File type.
    s32     flags;                      // File handeling flags.
};

/** @brief Initrd main structure.*/
struct initrd_t {
    file *files;   // All files.
    u32  count;    // Total number of files.
};

/** @brief Initialize initial ramdisk.*/
void init(void);

/** @brief Free all allocated memory for initrd. */
void free(void);

/**
 * @brief Initrd create file.
 * 
 * @param [in] pathname - given path to the file to be created.
 * @param [in] mode - given file permissions.
 * @return file descriptor of created file.
 * @return -1 in case of error.
 */
s32 creat(const char* pathname, mode_t mode);

/**
 * @brief Deletes a specified file from the file system.
 * 
 * @param [in] pathname - given path to the file to be unlinked.
 * @return 0 - in case of success.
 * @return -1 - in case of error.
 */
s32 unlink(const char* pathname);

/**
 * @brief Write bytes to file.
 * 
 * @param [in] fd - given file descriptor.
 * @param [in] buf - given buffer containing the data to be written.
 * @param [in] count - given number of bytes to write.
 * @return number of written bytes.
 * @return -1 in case of error.
 */
s32 write(s32 fd, void *buf, usize count);

/**
 * @brief Read bytes from file.
 * 
 * @param [in] fd - given file descriptor.
 * @param [out] buf - given buffer for read bytes.
 * @param [in] count - given number of bytes to read. 
 * @return number of read bytes.
 * @return -1 in case of error.
 */
s32 read(s32 fd, void *buf, usize count);

/**
 * @brief Open file.
 * 
 * @param [in] pathname - given path to the file to open. 
 * @param [in] flags - given flags that control how the file is opened.
 * @return file descriptor.
 * @return -1 in case of error.
 */
s32 open(const char *pathname, s32 flags);

/**
 * @brief Close file. 
 * 
 * @param [in] fd - given file descriptor to close.
 * @return 0 - on success.
 * @return -1 - in case of error.
 */
s32 close(s32 fd);

/**
 * @brief Get file index in files structure. 
 * 
 * @param [in] pathname - given path to the file to find.
 * @return file index.
 * @return -1 - in case of error.
 */
s32 get_index(const char *pathname);

/**
 * @brief Get file index in files structure by file descriptor. 
 * 
 * @param [in] fd - given file descriptor.
 * @return file index.
 * @return -1 - in case of error.
 */
s32 get_index_by_fd(s32 fd);

/**
 * @brief Set new file descriptor. 
 * 
 * @return new file descriptor.
 */
s32 set_fd(void);

/**
 * @brief Get initial ramdisk adapter for VFS.
 * 
 * @return VFS adapter structure pointer. 
 */
vfs::fs_adapter *get_adapter(void);

/**
 * @brief Get file information. 
 * 
 * @param [in] pathname - given path name.
 * @param [in] sb - given file information structure to fill. 
 * @return 0 - in case of success.
 * @return -1 - in case of error.
 */
s32 stat(const char *pathname, stat_t *sb);

/**
 * @brief Get total number of files. 
 * 
 * @return total number of initrd files.
 */
u32 get_count(void);

/**
 * @brief Get file information.
 * 
 * @param [in] pathname - given directory name.
 * @param [in] sb - given file information structure to fill. 
 * @return 0 - in case of success.
 * @return -1 - in case of error.
 */
s32 opendir(const char *pathname, stat_t *sb);

} // namespace initrd
} // namespace fs
} // namespace kernel

#endif // _KERNEL_FS_INITRD_HPP_