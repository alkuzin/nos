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
 * @file  ext2.h
 * @brief ext2 file system driver.
 * 
 * @details Contains ext2 file system handeling functions and structures.
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   07.06.2024
 */

#ifndef _NOS_KERNEL_EXT2_H_
#define _NOS_KERNEL_EXT2_H_

#include <nos/types.h>

#define FS_BLOCK_SIZE 4096 /* 4KB */
#define FS_MAX_BLOCKS 1024
#define FS_MAX_INODES 128

#define FS_BLOCK_BITMAP_SIZE (FS_MAX_BLOCKS / 8)
#define FS_INODE_BITMAP_SIZE (FS_MAX_INODES / 8)

#define EXT2_SIGNATURE 0xEF53
#define MAX_NAME_SIZE  64

#define ROOT_INODE_NUMBER 2

/**
 * @brief Ext2 superblock structure. 
 * 
 * The Superblock contains all information about the layout of the file system 
 * and possibly contains other important information like what optional features 
 * were used to create the file system.
 */
struct __superblock_s {
    u32 inodes;              ///< Total number of inodes in file system.
    u32 blocks;              ///< Total number of blocks in file system.
    u32 reserved_for_root;   ///< Number of blocks reserved for superuser.
    u32 unallocated_blocks;  ///< Total number of unallocated blocks.
    u32 unallocated_inodes;  ///< Total number of unallocated inodes.
    u32 superblock_id;       ///< Number of the block containing the superblock.
    u32 blocksize_hint;      ///< Number to shift 1024 to the left by to obtain the block size.
	u32 fragmentsize_hint;   ///< Number to shift 1024 to the left by to obtain the fragment size.
    u32 blocks_per_group;    ///< Number of blocks in each block group.
    u32 fragments_per_group; ///< Number of fragments in each block group.
    u32 inodes_per_group;    ///< Number of inodes in each block group.
    u32 last_mount;          ///< Last mount time (POSIX time).
    u32 last_write;          ///< Last written time (POSIX time).
    u16 mounts_since_last_check;     ///< Number of times the volume has been mounted.
	u16 max_mounts_since_last_check; ///< Number of mounts allowed before a check must be done.
    u16 signature;       ///< Ext2 signature used to help confirm the presence of Ext2 on a volume.
    u16 state;           ///< File system state.
    u16 on_error;        ///< What to do when an error is detected.
    u16 minor_version;   ///< Minor portion of version.
    u32 last_check;      ///< POSIX time of last consistency check.
    u32 checks_interval; ///< Interval (in POSIX time) between forced consistency checks.
    u32 os_id;           ///< Operating system ID from which the filesystem on this volume was created.
    u32 major_version;   ///< Major portion of version.
    u16 uid;             ///< User ID that can use reserved blocks.
    u16 gid;             ///< Group ID that can use reserved blocks.
    
    /* Extended superblock fields (set as unused).
     * These fields are only present if Major version, is greater than or equal to 1. */
    u8  unused[940];     ///< Unused memory.
} __attribute__((packed)); /* prevent the compiler from optimizing */
typedef struct __superblock_s superblock_t;

/** @brief File system states. */
#define FS_IS_CLEAN   1
#define FS_HAS_ERRORS 2

/** @brief Error handeling methods. */
#define FS_ERR_IGNORE  1 ///< Ignore the error (continue on).
#define FS_ERR_REMOUNT 2 ///< Remount file system as read-only.
#define FS_ERR_PANIC   3 ///< Kernel panic.

/** @brief Creator operating system IDs.
 * 0 - Linux;
 * 1 - GNU HURD;
 * 2 - MASIX (an operating system developed by Rémy Card, one of the developers of ext2);
 * 3 - FreeBSD;
 * 4 - Other "Lites" (BSD4.4-Lite derivatives such as NetBSD, OpenBSD, XNU/Darwin, etc.);
 * ...
 * 9999 - NOS. 
 */
#define NOS_ID 9999

/**
 * @brief Block Group Descriptor table structure.
 * 
 * A Block Group Descriptor contains information regarding where 
 * important data structures for that block group are located.
 */
struct __block_group_descr_s {
    u32 block_of_block_usage_bitmap; ///< Block address of block usage bitmap.
	u32 block_of_inode_usage_bitmap; ///< Block address of inode usage bitmap.
    u32 block_of_inode_table;        ///< Starting block address of inode table.
	u16 num_of_unalloc_blocks;              ///< Number of unallocated blocks in group.
	u16 num_of_unalloc_inodes;              ///< Number of unallocated inodes in group.
	u16 num_of_dirs;                 ///< Number of directories in group.
    
	u8  unused[14];                  ///< Unused memory.
} __attribute__((packed)); /* prevent the compiler from optimizing */
typedef struct __block_group_descr_s block_group_descr_t;

/**
 * @brief Inode structure.
 * 
 * An inode is a structure on the disk that represents a file, directory, 
 * symbolic link, etc. Inodes do not contain the data of the 
 * file / directory / etc. that they represent.
 * Instead, they link to the blocks that actually contain the data. 
 */
struct __inode_s {
    u32 inode_number;       ///< Inode ID.
    u16 type;               ///< Type and permissions.
    u16 uid;                ///< User ID.
    u32 size;               ///< Lower 32 bits of size in bytes.
    u32 last_access;        ///< Last Access Time (in POSIX time).
    u32 create_time;        ///< Creation Time (in POSIX time).
    u32 last_modif;         ///< Last Modification time (in POSIX time).
    u32 delete_time;        ///< Deletion time (in POSIX time).
    u16 gid;                ///< Group ID.
    u16 hardlinks;          ///< Count of hard links (directory entries) to this inode.
    u32 disk_sectors;       ///< Count of disk sectors in use by this inode.
    u32 flags;              ///< Inode flags.
    u32 ossv1;              ///< Operating System Specific value #1.
    u32 direct_blocks[12];  ///< Direct block pointers
    u32 singly_block;       ///< Singly Indirect Block pointer (points to a block that is a list of block pointers to data).
    u32 doubly_block;       ///< Doubly Indirect Block pointer (points to a block that is a list of block pointers to Singly Indirect Blocks).
    u32 triply_block;       ///< Triply Indirect Block pointer (points to a block that is a list of block pointers to Doubly Indirect Blocks).
    u32 gen_number;         ///< Generation number (primarily used for NFS).
    u32 reserved1;          ///< In version >= 1, Extended attribute block (File ACL).
    u32 reserved2;          ///< In version >= 1, Upper 32 bits of file size if it's a file, Directory ACL if it's a directory.
    u32 fragment_block;     ///< Block address of fragment.
    u8  ossv2[12];          ///< Operating System Specific Value #2.
} __attribute__((packed)); /* prevent the compiler from optimizing */
typedef struct __inode_s inode_t;

/**
 * @brief Ext2 directory entry.
 * 
 * Directories are inodes which contain some number of "entries" 
 * as their contents. These entries are nothing more than a name/inode pair.
 */
struct __ext2_dir_s {
    u32  inode;
	u16  size;      ///< Total size of this entry (including all subfields).
	u8   namelen;   ///< Name length least-significant 8 bits.
	u8   reserved;
    char name[MAX_NAME_SIZE];
} __attribute__((packed)); /* prevent the compiler from optimizing */
typedef struct __ext2_dir_s ext2_dir_t;

/** @brief Block bitmap structure. */
struct __block_bitmap_s {
    u8 blocks[FS_BLOCK_BITMAP_SIZE];
} __attribute__((packed)); /* prevent the compiler from optimizing */
typedef struct __block_bitmap_s block_bitmap_t;

/** @brief Inode bitmap structure. */
struct __inode_bitmap_s {
    u8 inodes[FS_INODE_BITMAP_SIZE];
} __attribute__((packed)); /* prevent the compiler from optimizing */
typedef struct __inode_bitmap_s inode_bitmap_t;

/**
 * @brief Initialize the block bitmap with all blocks marked as free.
 * 
 * @param [in] bb - given block bitmap structure.
 */
void ext2_block_bm_init(block_bitmap_t *bb);

/**
 * @brief Initialize the inode bitmap with all inodes marked as free.
 * 
 * @param [in] ib - given inode bitmap structure.
 */
void ext2_inode_bm_init(inode_bitmap_t *ib);

/** @brief Initialize ext2 driver. */
void ext2_init(void);

/** @brief Initialize superblock. */
void ext2_superblock_init(void);

/**
 * @brief Initialize root inode. 
 * 
 * @param [in] root - given root inode.
 */
void ext2_root_inode_init(inode_t *root);

/**
 * @brief Initialize root directory. 
 * 
 * @param [in] root_dir - given root directory entry structure.
 * @param [in] inode_number - given root inode number. 
 * @param [in] pathname - given root directory path name.
 */
void ext2_root_dir_init(ext2_dir_t* root_dir, u32 inode_number, const char* pathname);

#endif /* _NOS_KERNEL_EXT2_H_ */