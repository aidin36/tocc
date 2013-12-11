/*
 * This file is part of TOCC. (see <http://www.github.com/aidin36/tocc>)
 * Copyright (C) 2013, Aidin Gharibnavaz <tocc@aidihut.com>
 *
 * TOCC is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Foobar is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 *  along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "file_system/file_manager.h"

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
      // TODO: Raise exception
    }

    return creat_result; // Which is the file descriptor.
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
	// Path is already exists. It's ok.
	return;
      }
      if (errno != ENOENT)
      {
	// If error is something other than "path already exists"
	// or "part of the path doesn't exists", throw an exception.
	// TODO: Throw an exception.
      }
    }

    // Creating the path recursively.
    // Note: I know that I'm duplicating the code, but its faster than
    // splitting the path.
    std::string path_to_create(this->base_path);
    path_to_create += "/";
    path_to_create += id.substr(0, 2) + "/";
    create_dir(path_to_create);
    path_to_create += id.substr(2, 2) + "/";
    create_dir(path_to_create);
    path_to_create += id.substr(4, 2) + "/";
    create_dir(path_to_create);
  }

  void FileManager::create_dir(std::string path)
  {
    int mkdir_result = mkdir(path.c_str(), NORMAL_MODE);
    if (mkdir_result < 0)
    {
      if (mkdir_result != EEXIST)
      {
	// TODO: Throw exception.
      }
    }
  }

  std::string FileManager::id_to_dir_path(std::string id)
  {
    // TODO: Raise exception if ID is not valid (e.g. its length is incorrect.)
    
    std::string result(this->base_path);
    
    result += "/";
    result += id.substr(0, 2);
    result += "/";
    result += id.substr(2, 2);
    result += "/";
    result += id.substr(4, 2);
    result += "/";
    
    return result;
  }
  
  std::string FileManager::id_to_file_path(std::string id)
  {
    std::string result(id_to_dir_path(id));
    
    result += id.substr(6, 2);
    
    return result;
  }

};
