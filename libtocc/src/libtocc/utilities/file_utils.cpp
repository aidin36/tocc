/*
 * This file is part of Tocc. (see <https://tocc.aidinhut.com>)
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

#include"libtocc/utilities/file_utils.h"

namespace libtocc
{
  std::string get_filename_from_path(std::string path)
  {
    std::string filename;

    //extract the file from path
    int last_slash_index = path.rfind("/");

    if(last_slash_index != std::string::npos)
    {
      filename = path.substr(last_slash_index + 1, path.length());
    }
    else
    {
      if(path.length()!=0)
      {
        filename = path;
      }
    }

    return filename;
  }

  bool is_path_parent_exists(std::string database_path)
  {
    DIR* directory_ptr = NULL;
    int pos = 0;

    pos = database_path.rfind('/');
    std::string base_path = database_path.substr(0, pos);
    directory_ptr = opendir(base_path.c_str());
    if(directory_ptr == NULL)
    {
      return false;
    }

    closedir(directory_ptr);
    return true;
  }

}
