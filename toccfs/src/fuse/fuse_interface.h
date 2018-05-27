/*
 * This file is part of Tocc. (see <https://tocc.aidinhut.com>)
 * Copyright (C) 2013, 2014, Aidin Gharibnavaz <tocc@aidinhut.com>
 *
 * Tocc is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Tocc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 *  along with Tocc.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TOCCFS_FUSE_INTERFACE_H_INCLUDED
#define TOCCFS_FUSE_INTERFACE_H_INCLUDED

// Using latest FUSE API version.
#define FUSE_USE_VERSION 26

#include <fuse.h>


namespace toccfs
{

  int toccfs_fuse_getattr(const char* path, struct stat* stbuf);

  int toccfs_fuse_readdir(const char* path, void* buffer, fuse_fill_dir_t filler,
                          off_t offset, struct fuse_file_info* fileinfo);

  int toccfs_fuse_read(const char* path, char* buffer, size_t size, off_t offset,
                       struct fuse_file_info* file_info);

  int toccfs_fuse_access(const char* path, int mask);

  int toccfs_fuse_statfs(const char* path, struct statvfs* stbuf);

  int toccfs_fuse_mkdir(const char* path, mode_t mode);

  int toccfs_fuse_rmdir(const char* path);

  int toccfs_fuse_unlink(const char* path);

  int toccfs_fuse_mknod(const char* path, mode_t mode, dev_t rdev);

  int toccfs_fuse_symlink(const char* from, const char* to);

  int toccfs_fuse_rename(const char* from, const char* to);

  int toccfs_fuse_link(const char* from, const char* to);

  int toccfs_fuse_chmod(const char* path, mode_t mode);

  int toccfs_fuse_chown(const char* path, uid_t uid, gid_t gid);

  int toccfs_fuse_truncate(const char* path, off_t size);

  int toccfs_fuse_write(const char* path, const char* buf, size_t size,
                        off_t offset, struct fuse_file_info* fi);

}

#endif /* TOCCFS_FUSE_INTERFACE_H_INCLUDED */
