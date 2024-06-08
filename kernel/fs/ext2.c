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

#include <string.h>

#include <nos/types.h>
#include <nos/ext2.h>

static block_bitmap_t block_bitmap;
static inode_bitmap_t inode_bitmap;

static superblock_t   superblock;

static inode_t        root_inode;
static ext2_dir_t     root_dir;


void ext2_block_bm_init(block_bitmap_t *bb) 
{
    for (int i = 0; i < FS_BLOCK_BITMAP_SIZE; i++)
        bb->blocks[i] = 0xFF;
}

void ext2_inode_bm_init(inode_bitmap_t *ib)
{
    for (int i = 0; i < FS_INODE_BITMAP_SIZE; i++)
        ib->inodes[i] = 0xFF;
}

void ext2_root_inode_init(inode_t *root)
{
    root->inode_number = ROOT_INODE_NUMBER;
    root->type         = S_IFREG;
    root->uid          = 0;
    root->size         = 0;
    root->last_access  = 0;
    root->create_time  = 0;
    root->last_modif   = 0;
    root->delete_time  = 0;
    root->gid          = 0;
    root->hardlinks    = 2;
    root->disk_sectors = 0;
    root->flags        = 0;
    root->ossv1        = 0;
    bzero(root->direct_blocks, sizeof(u32) * 12);
    root->singly_block    = 0;
    root->doubly_block    = 0;
    root->triply_block    = 0;
    root->gen_number      = 0;
    root->reserved1       = 0;
    root->reserved2       = 0;
    root->fragment_block  = 0;
    memset(root->ossv2, 0, 12);
}

void ext2_root_dir_init(ext2_dir_t* root_dir, u32 inode_number, const char* pathname)
{
    root_dir->inode     = inode_number;
    root_dir->size      = sizeof(ext2_dir_t) - MAX_NAME_SIZE + strlen(pathname);
    root_dir->namelen   = strlen(pathname);
    root_dir->reserved  = 0;
    strncpy(root_dir->name, pathname, MAX_NAME_SIZE);
}

void ext2_superblock_init(void)
{
    superblock.inodes                      = FS_MAX_INODES;
    superblock.blocks                      = FS_MAX_BLOCKS;
    superblock.reserved_for_root           = 10;
    superblock.unallocated_blocks          = FS_MAX_BLOCKS - 10;
    superblock.unallocated_inodes          = FS_MAX_INODES - 1;
    superblock.superblock_id               = 1;
    superblock.blocksize_hint              = FS_BLOCK_SIZE >> 10;
    superblock.fragmentsize_hint           = FS_BLOCK_SIZE >> 11;
    superblock.blocks_per_group            = 100;
    superblock.fragments_per_group         = FS_BLOCK_SIZE / FS_MAX_BLOCKS;
    superblock.inodes_per_group            = FS_MAX_BLOCKS / FS_MAX_INODES;
    superblock.last_mount                  = 0;
    superblock.last_write                  = 0;
    superblock.mounts_since_last_check     = 0;
    superblock.max_mounts_since_last_check = 0;
    superblock.signature                   = EXT2_SIGNATURE;
    superblock.state                       = FS_IS_CLEAN;
    superblock.on_error                    = FS_ERR_PANIC;
    superblock.minor_version               = 1;
    superblock.last_check                  = 0;
    superblock.checks_interval             = 86400;
    superblock.os_id                       = NOS_ID;
    superblock.major_version               = 0;
    superblock.uid                         = 0;
    superblock.gid                         = 0;
}

void ext2_init(void)
{
    /* bitmaps initialization */
    ext2_block_bm_init(&block_bitmap);
    ext2_inode_bm_init(&inode_bitmap);

    /* root inode & directory entry initialization */
    ext2_root_inode_init(&root_inode);
    ext2_root_dir_init(&root_dir, root_inode.inode_number, "/root");
}