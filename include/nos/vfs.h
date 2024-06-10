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

/**
 * @file  vfs.h
 * @brief Contains declarations for kernel VFS (Virtual File System).
 * 
 * @details This header file includes functions, structs for
 * managing virtual file system.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   30.05.2024
 */

#ifndef _NOS_KERNEL_VFS_H_
#define _NOS_KERNEL_VFS_H_

#include <nos/types.h>
#include <nos/fcntl.h>
#include <nos/stat.h>

#define MAX_PATH_SIZE 64


/** @brief VFS interface for different types of file systems. */
struct vfs_s {
    s32 (*open)(const char *pathname, s32 flags);
    s32 (*close)(s32 fd);
    s32 (*read)(s32 fd, void *buf, usize count);
    s32 (*write)(s32 fd, void *buf, usize count);
    s32 (*creat)(const char* pathname, mode_t mode);
    s32 (*unlink)(const char* pathname);
};

typedef struct vfs_s vfs_t;

/** @brief VFS adapter for specific file system. */
struct vfs_adapter_s {
    s32 (*open)(const char *pathname, s32 flags);
    s32 (*close)(s32 fd);
    s32 (*read)(s32 fd, void *buf, usize count);
    s32 (*write)(s32 fd, void *buf, usize count);
    s32 (*creat)(const char* pathname, mode_t mode);
    s32 (*unlink)(const char* pathname);
};

typedef struct vfs_adapter_s vfs_adapter_t;

struct file_s {
    char name[MAX_PATH_SIZE]; ///< Absolute file name.
    char *data; ///< File content.
    u32  size;  ///< Size of the file in bytes.
};

typedef struct file_s file_t;

/**
 * @brief Register current active file system.
 * 
 * @param [in] type - given type of file system to register. 
 * @param [in] fs_adapter - given file system adapter. 
 */
void vfs_register(fs_type_t type, vfs_adapter_t *fs_adapter);

/**
 * @brief Initialize virtual file system.
 * 
 * @param [in] type - given type of file system to register. 
 * @param [in] fs_adapter - given file system adapter. 
 */
void vfs_init(fs_type_t type, vfs_adapter_t *fs_adapter);

/**
 * @brief Open file.
 * 
 * @param [in] pathname - given path to the file to open. 
 * @param [in] flags - given flags that control how the file is opened.
 * @return file descriptor.
 * @return -1 - in case of error.
 */
s32 vfs_open(const char *pathname, s32 flags);

/**
 * @brief Close file. 
 * 
 * @param [in] fd - given file descriptor to close.
 * @return 0 - on success.
 * @return -1 - in case of error.
 */
s32 vfs_close(s32 fd);

/**
 * @brief Read bytes from file.
 * 
 * @param [in] fd - given file descriptor.
 * @param [out] buf - given buffer for read bytes.
 * @param [in] count - given number of bytes to read. 
 * @return number of read bytes.
 * @return -1 in case of error.
 */
s32 vfs_read(s32 fd, void *buf, usize count);

/**
 * @brief Write bytes to file.
 * 
 * @param [in] fd - given file descriptor.
 * @param [in] buf - given buffer containing the data to be written.
 * @param [in] count - given number of bytes to write.
 * @return number of written bytes.
 * @return -1 in case of error.
 */
s32 vfs_write(s32 fd, void *buf, usize count);

/**
 * @brief Create file.
 * 
 * @param [in] pathname - given path to the file to be created.
 * @param [in] mode - given file permissions.
 * @return file descriptor of created file.
 * @return -1 in case of error.
 */
s32 vfs_creat(const char* pathname, mode_t mode);

/**
 * @brief Deletes a specified file from the file system.
 * 
 * @param [in] pathname - given path to the file to be unlinked.
 * @return 0 - in case of success.
 * @return -1 - in case of error.
 */
s32 vfs_unlink(const char* pathname);

#endif /* _NOS_KERNEL_VFS_H_ */