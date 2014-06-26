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

#include <vector>
#include <cstring>
#include <string>

#include "libtocc/front_end/file_info.h"
#include "engine/fs_handler.h"


namespace toccfs
{

  FSHandler* get_fs_handler()
  {
    return (FSHandler*)fuse_get_context()->private_data;
  }

  int getattr(const char* path, struct stat* stbuf)
  {
    // TEMPORARY CODE
    if (strcmp(path, "/") == 0)
    {
      stbuf->st_mode = S_IFDIR | 0755;
      stbuf->st_nlink = 2;
      return 0;
    }
    return -1;
  }

  int readdir(const char* path, void* buffer, fuse_fill_dir_t filler,
              off_t offset, struct fuse_file_info* fileinfo)
  {
    struct FSHandler* fs_handler = get_fs_handler();

    std::vector<libtocc::FileInfo> founded_files = fs_handler->get_by_path(path);

    if (founded_files.empty())
    {
      // There's no file. Returning OK without filling buffer.
      return 0;
    }

    std::vector<libtocc::FileInfo>::iterator files_iterator = founded_files.begin();
    for (; files_iterator != founded_files.end(); files_iterator++)
    {
      // Format of the output is something like "[0001c43]Track03"
      std::string file_name;
      file_name += "[";
      file_name += files_iterator->get_id();
      file_name += "]";
      file_name += files_iterator->get_title();
      filler(buffer, file_name.c_str(), NULL, 0);
    }

    // Returning OK.
    return 0;
  }
}
