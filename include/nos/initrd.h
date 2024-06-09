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
 * @file  initrd.h
 * @brief Initial ramdisk file system driver.
 * 
 * @details Initial ramdisk is a temporary file system used by the kernel during the boot process 
 * before the actual root file system is mounted.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   08.06.2024
 */

#ifndef _NOS_KERNEL_INITRD_H_
#define _NOS_KERNEL_INITRD_H_

#include <nos/types.h>
#include <nos/fcntl.h>
#include <nos/vfs.h>


#define INITRD_MAX_NAME_SIZE 64
#define INITRD_MAX_FILES     3
#define INITRD_FILE_SIZE     1024 /* 1KB */

/* file states */
#define INITRD_FILE_OPENED 1
#define INITRD_FILE_CLOSED 2

/** @brief Initrd file structure. */
typedef struct {
    char    name[INITRD_MAX_NAME_SIZE]; ///< Name of the file.
    u8      data[INITRD_FILE_SIZE];     ///< File content.
    u32     size;                       ///< Size of the file in bytes.
    mode_t  mode;                       ///< File permissions.
    s32     fd;                         ///< File descriptor.
    u32     state;                      ///< File state (e.g. opened/closed/etc.).
    u32     type;                       ///< File type.
    s32     flags;                      ///< File handeling flags.
} initrd_file_t;

/** @brief Initrd main structure. */
typedef struct {
    initrd_file_t *files;   ///< All files.
    u32 count;              ///< Total number of files.
} initrd_t;

/**
 * @brief Initialize initial ramdisk.
 * 
 * @param [in] begin_paddr - given begin physical address.
 * @param [in] end_paddr - given end physical address.
 */
void initrd_init(void);

/** @brief Display list of files. */
void initrd_ls(void);

/** @brief Free all allocated memory for initrd. */
void initrd_free(void);

/**
 * @brief Initrd create file.
 * 
 * @param [in] pathname - given path to the file to be created.
 * @param [in] mode - given file permissions.
 * @return file descriptor of created file.
 * @return -1 in case of error.
 */
s32 initrd_creat(const char* pathname, mode_t mode);

/**
 * @brief Deletes a specified file from the file system.
 * 
 * @param [in] pathname - given path to the file to be unlinked.
 * @return 0 - in case of success.
 * @return -1 - in case of error.
 */
s32 initrd_unlink(const char* pathname);

/**
 * @brief Write bytes to file.
 * 
 * @param [in] fd - given file descriptor.
 * @param [in] buf - given buffer containing the data to be written.
 * @param [in] count - given number of bytes to write.
 * @return number of written bytes.
 * @return -1 in case of error.
 */
s32 initrd_write(s32 fd, void *buf, usize count);

/**
 * @brief Read bytes from file.
 * 
 * @param [in] fd - given file descriptor.
 * @param [out] buf - given buffer for read bytes.
 * @param [in] count - given number of bytes to read. 
 * @return number of read bytes.
 * @return -1 in case of error.
 */
s32 initrd_read(s32 fd, void *buf, usize count);

/**
 * @brief Get initial ramdisk adapter for VFS.
 * 
 * @return VFS adapter structure pointer. 
 */
vfs_adapter_t *initrd_get_adapter(void);

/**
 * @brief Open file.
 * 
 * @param [in] pathname - given path to the file to open. 
 * @param [in] flags - given flags that control how the file is opened.
 * @return file descriptor.
 * @return -1 in case of error.
 */
s32 initrd_open(const char *pathname, s32 flags);

/**
 * @brief Close file. 
 * 
 * @param [in] fd - given file descriptor to close.
 * @return 0 - on success.
 * @return -1 - in case of error.
 */
s32 initrd_close(s32 fd);

/**
 * @brief Get file index in files structure. 
 * 
 * @param [in] pathname - given path to the file to find.
 * @return file index.
 * @return -1 - in case of error.
 */
s32 initrd_get_index(const char *pathname);

/**
 * @brief Get file index in files structure by file descriptor. 
 * 
 * @param [in] fd - given file descriptor.
 * @return file index.
 * @return -1 - in case of error.
 */
s32 initrd_get_index_by_fd(s32 fd);

/**
 * @brief Set new file descriptor. 
 * 
 * @return new file descriptor.
 */
s32 initrd_set_fd(void);

#endif /* _NOS_KERNEL_INITRD_H_ */