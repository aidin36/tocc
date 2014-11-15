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

#ifndef TOCCFS_STRING_UTILS_H_INCLUDED
#define TOCCFS_STRING_UTILS_H_INCLUDED

#include <string>
#include <vector>


namespace toccfs
{

  /*
   * Splits a string, by the specified delimiter.
   */
  std::vector<std::string> split_string(const std::string& string_to_split,
                                        char delimiter);

  /*
   * Checks if the specified string is ends with the other one.
   * (i.e. `str_to_check' is at the end of `str'.
   */
  bool string_ends_with(const std::string& str,
                        const std::string& str_to_check);
}

#endif /* TOCCFS_STRING_UTILS_H_INCLUDED */
