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

#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdio>
#ifdef HAVE_SENDFILE // check if sendfile is available
 #include <sys/sendfile.h>
#endif

#include "libtocc/common/runtime_exceptions.h"
#include "libtocc/file_system/file_manager.h"
#include "libtocc/file_system/helpers.cpp"

namespace libtocc
{

  /*
   * Mode for creating files and directories.
   */
  const mode_t NORMAL_MODE = S_IRWXU | S_IRGRP | S_IROTH;

  FileManager::FileManager(std::string base_path)
  {
    this->base_path = base_path;
  }

  int FileManager::create(std::string id)
  {
    // Ensuring path exists. It will create it if it is not.
    ensure_path_exists(id);

    // Creating the file.
    int creat_result = creat(id_to_file_path(id).c_str(), NORMAL_MODE);
    if (creat_result < 0)
    {
      handle_errno(errno, id);
    }

    return creat_result; // Which is the file descriptor.
  }

  int FileManager::open_file(std::string id, char mode)
  {
    std::string file_path = id_to_file_path(id);

    // Making flags for system's `open' method.
    int open_flags;
    if (mode == 'r')
    {
      open_flags = O_RDONLY;
    }
    else if (mode == 'w')
    {
      open_flags = O_WRONLY | O_TRUNC;
    }
    else if (mode == 'a')
    {
      open_flags = O_WRONLY;
    }
    else
    {
      throw InvalidArgumentError("Inavlid mode for openning file.");
    }

    int fd = open(file_path.c_str(), open_flags);

    if (fd < 0)
    {
      handle_errno(errno, file_path);
    }

    return fd;
  }

  void FileManager::remove(std::string file_id)
  {
    // I used "unlink" not "remove", because I'm sure path is
    // referring to a file, not a directory or something.
    int unlink_result = unlink(id_to_file_path(file_id).c_str());

    if (unlink_result < 0)
    {
      if (errno != ENOENT)
      {
	// If error is something other than "path does not exists".
	handle_errno(errno, file_id);
      }
    }
  }

  void FileManager::copy(std::string source_path, std::string file_id)
  {

    // TODO: Maybe we should use `st_blksize' of the file attributes instead
    //   of the BUFSIZ. That's the optimal value, but we need to read the
    //   attribute from the file, before starting.

    char buf[BUFSIZ]; // BUFSIZ is defined in <cstdio>.
    size_t size;

    int dest = create(file_id);
    int source = open(source_path.c_str(), O_RDONLY);

    // `sendfile' is a lot faster. We use it if available.
    #ifndef HAVE_SENDFILE
      // we don't have sendfile, so we'll use read and write
      while ((size = read(source, buf, BUFSIZ)) > 0)
      {
          ssize_t write_result = write(dest, buf, size);

          if (write_result < 0)
          {
            // An error occurred while writing to file.
            handle_errno(errno, source_path);
          }
      }
    #else
      off_t offset = 0;
      struct stat stat_buf;
      // Stat the source file to obtain its size.
      fstat (source, &stat_buf);
      // Send the file with sendfile
      sendfile(dest, source, &offset, stat_buf.st_size);
    #endif

    close(source);
    close(dest);
  }

  std::string FileManager::get_physical_path(std::string file_id)
  {
    return id_to_file_path(file_id);
  }

  void FileManager::ensure_path_exists(std::string id)
  {
    // There's a big chance that path is already exists or
    // only the last directory should be created. So, first
    // we try that.
    std::string dir_path = id_to_dir_path(id);
    int mkdir_result = mkdir(dir_path.c_str(), NORMAL_MODE);

    if (mkdir_result >= 0)
    {
      // Path created sucessfully. No need to do anything else.
      return;
    }
    else
    {
      if (errno == EEXIST)
      {
	// Path is already exists. Nothing else to do.
	return;
      }
      if (errno != ENOENT)
      {
	// If error is something other than "path already exists"
	// or "part of the path doesn't exists", throw an exception.
	handle_errno(errno, dir_path);
      }
    }

    // Creating the path recursively.
    // Note: I know that I'm duplicating the code, but its faster than
    // splitting the path.
    std::string path_to_create(this->base_path);

    path_to_create += "/";
    path_to_create += id.substr(0, 1) + "/";
    create_dir(path_to_create);
    path_to_create += id.substr(1, 2) + "/";
    create_dir(path_to_create);
    path_to_create += id.substr(3, 2) + "/";
    create_dir(path_to_create);
  }

  void FileManager::create_dir(std::string path)
  {
    int mkdir_result = mkdir(path.c_str(), NORMAL_MODE);
    if (mkdir_result < 0)
    {
      if (errno != EEXIST && errno != ENOENT)
      {
	// If error wasn't "path already exists" or "part of the path
	// already exists", throw an exception.
	handle_errno(errno, path);
      }
    }
  }

  std::string FileManager::id_to_dir_path(std::string id)
  {
    // TODO: Raise exception if ID is not valid (e.g. its length is incorrect.)

    std::string result(this->base_path);

    if (result.at(result.length() - 1) != '/')
    {
      result += "/";
    }

    result += id.substr(0, 1);
    result += "/";
    result += id.substr(1, 2);
    result += "/";
    result += id.substr(3, 2);
    result += "/";

    return result;
  }

  std::string FileManager::id_to_file_path(std::string id)
  {
    std::string result(id_to_dir_path(id));

    result += id.substr(5, 2);

    return result;
  }

};
