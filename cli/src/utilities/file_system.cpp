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


#include "utilities/file_system.h"
#include <sys/stat.h>
#include <dirent.h>
#include <cstdio>
#include <cstring>


namespace tocccli
{
  bool is_directory(std::string dir_path)
  {
    struct stat dir_info;
    if(stat(dir_path.c_str(), &dir_info) == 0 && S_ISDIR(dir_info.st_mode))
    {
      return true;
    }
    return false;
  }

  bool is_file(std::string file_path)
  {
    struct stat file_info;
    if(stat(file_path.c_str(), &file_info) == 0 && S_ISREG(file_info.st_mode))
    {
      return true;
    }
    return false;
  }
  
  bool is_valid_path(std::string path)
  {
    struct stat path_info;
    if(stat(path.c_str(), &path_info) == 0)
    {
      return true;
    }

    return false;
  }

  std::vector<std::string> get_all_files(std::string dir_path)
  {
    std::vector<std::string> files;
    if(is_valid_path(dir_path))
    {
      DIR* opened_directory = opendir(dir_path.c_str());
      if( opened_directory != 0)
      {
        struct dirent* file = 0;
        while( (file = readdir(opened_directory)) != 0)
        {
          if( file->d_name[0] != '.' && file->d_name[strlen(file->d_name) - 1 ] != '~')
          {
            std::string file_full_path = dir_path + "/";
            file_full_path += file->d_name;
            if(is_file(file_full_path))
            {
              files.push_back(file_full_path);
            }
          }
        }
        closedir(opened_directory);
      } 
    }
    return files;
  }

  std::string get_dir(std::string path)
  {
    int last_slash_occurence = path.find_last_of("/");
    if(last_slash_occurence >= 0)
    {
      return path.substr(0, last_slash_occurence);
    }

    return path;
  }

  std::string get_file(std::string file_path)
  {
    int last_slash_occurence = file_path.find_last_of("/");
    if(last_slash_occurence >= 0)
    {
      return file_path.substr(last_slash_occurence + 1);
    }

    return file_path;
  }
}
