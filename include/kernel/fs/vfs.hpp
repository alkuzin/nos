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
 * @file  vfs.hpp
 * @brief Contains declarations for kernel VFS (Virtual File System).
 * 
 * @details This header file includes functions, structs for
 * managing virtual file system.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   30.05.2024
 */

#ifndef _KERNEL_FS_HPP_
#define _KERNEL_FS_HPP_

#include <kernel/fs/fcntl.hpp>
#include <kernel/fs/stat.hpp>


namespace kernel {
namespace fs {
namespace vfs {

// Supported file systems type.
enum class fs_type {
    INITRD,
    EXT2
};

/** @brief VFS adapter for specific file system. */
struct fs_adapter {
    s32 (*open)(const char *pathname, s32 flags);
    s32 (*close)(s32 fd);
    s32 (*read)(s32 fd, void *buf, usize count);
    s32 (*write)(s32 fd, void *buf, usize count);
    s32 (*creat)(const char* pathname, mode_t mode);
    s32 (*unlink)(const char* pathname);
};

struct file {
    char name[MAX_PATH_SIZE]; // Absolute file name.
    char *data;               // File content.
    u32  size;                // Size of the file in bytes.
};

/**
 * @brief Register current active file system.
 * 
 * @param [in] type - given type of file system to register. 
 * @param [in] fs_adapter - given file system adapter. 
 */
void set(fs_type type, fs_adapter *fs_adapter);

/**
 * @brief Initialize virtual file system.
 * 
 * @param [in] type - given type of file system to register. 
 * @param [in] fs_adapter - given file system adapter. 
 */
void init(fs_type type, fs_adapter *fs_adapter);

/**
 * @brief Open file.
 * 
 * @param [in] pathname - given path to the file to open. 
 * @param [in] flags - given flags that control how the file is opened.
 * @return file descriptor.
 * @return -1 - in case of error.
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
 * @brief Create file.
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

} // namespace vfs
} // namespace fs
} // namespace kernel

#endif // _KERNEL_FS_HPP_