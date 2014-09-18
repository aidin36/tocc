/*
 * This file is part of Tocc. (see <http://t-o-c-c.com>)
 * Copyright (C) 2013, 2014, Aidin Gharibnavaz <aidin@t-o-c-c.com>
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

#include "fuse/fuse_interface.h"

#include <errno.h>
#include <unistd.h> // pread, open
#include <sys/statvfs.h> // statvfs
#include <vector>
#include <cstring>
#include <string>

#include "libtocc/front_end/file_info.h"
#include "engine/fs_handler.h"


namespace toccfs
{

  /*
   * Fills the specified stat buffer with the information of a read-only
   * directory.
   *
   * @param stbuf: Buffer to fill.
   * @param files_inside: Number of files inside this directory.
   */
  void fill_directory_stat(struct stat* stbuf, int files_inside)
  {
    memset(stbuf, 0, sizeof(struct stat));
    stbuf->st_mode = S_IFDIR | 0444;
    stbuf->st_nlink = files_inside;
  }

  /*
   * Fills the specified stat buffer with the stat of the specified file.
   * It returns zero on success, and errno on fail.
   */
  int fill_file_stat(struct stat* stbuf, const char* physical_path)
  {
    // Getting stat of the file, from the OS.
    int stat_result = lstat(physical_path,
                            stbuf);
    if (stat_result < 0)
    {
      // Returning happened error.
      return -errno;
    }

    // Returning OK.
    return 0;
  }

  FSHandler* get_fs_handler()
  {
    return (FSHandler*)fuse_get_context()->private_data;
  }

  int toccfs_fuse_getattr(const char* path, struct stat* stbuf)
  {
    if (strcmp(path, "/") == 0)
    {
      // Returning a directory with read-only permission.
      // TODO: Return number of tags plus two.
      fill_directory_stat(stbuf, 2);
      return 0;
    }

    struct FSHandler* fs_handler = get_fs_handler();

    // Checking if the path matches a single file.
    libtocc::FileInfo founded_file = fs_handler->get_by_path(path);
    if (strcmp(founded_file.get_id(), "-1") != 0)
    {
      int stat_result = fill_file_stat(stbuf, founded_file.get_physical_path());

      if (stat_result < 0)
      {
        // Returning happened error.
        return -errno;
      }

      // Returning OK.
      return 0;
    }

    // Assuming that it's a directory.
    // Finding files that should be inside this directory.

    std::vector<libtocc::FileInfo> founded_files = fs_handler->query_by_path(path);

    if (founded_files.empty())
    {
      // Nothing found. Returning "No such file or directory".
      return -ENOENT;
    }

    // A directory, with read-only permissions.
    // Number of files inside this directory is added by two,
    // because of '.' and '..'.
    fill_directory_stat(stbuf, founded_files.size() + 2);

    return 0;
  }

  int toccfs_fuse_readdir(const char* path, void* buffer, fuse_fill_dir_t filler,
                          off_t offset, struct fuse_file_info* fileinfo)
  {

    if (strcmp(path, "/") == 0)
    {
      // Pretending there's no file.
      // TODO: Return all tags.
      return 0;
    }

    struct FSHandler* fs_handler = get_fs_handler();

    std::vector<libtocc::FileInfo> founded_files = fs_handler->query_by_path(path);

    if (founded_files.empty())
    {
      // There's no file. Returning OK without filling buffer.
      return 0;
    }

    // Filling buffer with founded files.
    std::vector<libtocc::FileInfo>::iterator files_iterator = founded_files.begin();
    for (; files_iterator != founded_files.end(); files_iterator++)
    {
      // Reading stat of the file.
      struct stat stbuf;
      fill_file_stat(&stbuf, files_iterator->get_physical_path());
      // Add this file to buffer.
      filler(buffer, files_iterator->get_title(), &stbuf, 0);
    }

    // Finding tags that are related to these files.
    // We assume that these are directories inside the current directory.
    std::vector<std::string> tags = fs_handler->get_related_tags(founded_files);

    struct stat stbuf;

    std::vector<std::string>::iterator tags_iterator = tags.begin();
    for (; tags_iterator != tags.end(); tags_iterator++)
    {
//      if (tags_iterator->empty())
//      {
//        continue;
//      }

      // Finding files that should be inside this directory.
      std::vector<libtocc::FileInfo> founded_files = fs_handler->query_by_path(path);
      // Filling stat buffer as a read-only directory.
      // Two added to number of files, because of `.' and `..'.
      fill_directory_stat(&stbuf, founded_files.size() + 2);

      // Adding founded tags to buffer.
      filler(buffer, tags_iterator->c_str(), &stbuf, 0);
    }

    // Returning OK.
    return 0;
  }

  int toccfs_fuse_read(const char* path, char* buffer, size_t size, off_t offset,
                       struct fuse_file_info* file_info)
  {
    int file_descriptor;
    int result;

    struct FSHandler* fs_handler = get_fs_handler();

    // Getting the file that matches this path.
    libtocc::FileInfo founded_file = fs_handler->get_by_path(path);

    // If no file found, return an error.
    if (strcmp(founded_file.get_id(), "-1") == 0)
    {
      return -ENOENT;
    }

    // Opening founded file.
    file_descriptor = open(founded_file.get_physical_path(),
                           O_RDONLY);
    if (file_descriptor == -1)
    {
      return -errno;
    }

    result = pread(file_descriptor, buffer, size, offset);
    if (result == -1)
    {
      result = -errno;
    }

    close(file_descriptor);
    return result;
  }

  int toccfs_fuse_access(const char* path, int mask)
  {
    // Returning a read-only mask, since this is a read-only file system.
    mask = 0444;

    return 0;
  }

  int toccfs_fuse_statfs(const char* path, struct statvfs* stbuf)
  {
    // Getting true stats of file system.
    int result = statvfs(path, stbuf);

    if (result < 0)
    {
      // Returning the error.
      return -errno;
    }

    // Changing mount flags to read-only.
    stbuf->f_flag = ST_RDONLY;

    // Returning OK.
    return 0;
  }

  int toccfs_fuse_mkdir(const char* path, mode_t mode)
  {
    // Returning `Read-only File System' error.
    return -EROFS;
  }

  int toccfs_fuse_rmdir(const char* path)
  {
    // Returning `Read-only File System' error.
    return -EROFS;
  }

  int toccfs_fuse_unlink(const char* path)
  {
    // Returning `Read-only File System' error.
    return -EROFS;
  }

  int toccfs_fuse_mknod(const char* path, mode_t mode, dev_t rdev)
  {
    // Returning `Read-only File System' error.
    return -EROFS;
  }

  int toccfs_fuse_symlink(const char* from, const char* to)
  {
    // Returning `Read-only File System' error.
    return -EROFS;
  }

  int toccfs_fuse_rename(const char* from, const char* to)
  {
    // Returning `Read-only File System' error.
    return -EROFS;
  }

  int toccfs_fuse_link(const char* from, const char* to)
  {
    // Returning `Read-only File System' error.
    return -EROFS;
  }

  int toccfs_fuse_chmod(const char* path, mode_t mode)
  {
    // Returning `Read-only File System' error.
    return -EROFS;
  }

  int toccfs_fuse_chown(const char* path, uid_t uid, gid_t gid)
  {
    // Returning `Read-only File System' error.
    return -EROFS;
  }

  int toccfs_fuse_truncate(const char* path, off_t size)
  {
    // Returning `Read-only File System' error.
    return -EROFS;
  }

  int toccfs_fuse_write(const char* path, const char* buf, size_t size,
                        off_t offset, struct fuse_file_info* fi)
  {
    // Returning `Read-only File System' error.
    return -EROFS;
  }

}
