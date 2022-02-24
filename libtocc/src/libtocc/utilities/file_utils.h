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

#ifndef LIBTOCC_FILE_FILE_UTILS_H_INCLUDED
#define LIBTOCC_FILE_FILE_UTILS_H_INCLUDED

#include<string>
#ifdef _MSC_VER
#else
#include<dirent.h>
#endif
namespace libtocc
{
  /*
   * Extract file name from the specified path, and returns it.
   * It returns file name with its extension.
   */
  std::string get_filename_from_path(std::string path);

  /*
   * Checks if the parent directory of specified path exists.
   */
  bool is_path_parent_exists(std::string path);
}

#endif
