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

#ifndef TOCCCLI_STRING_UTILS_H_INCLUDED
#define TOCCCLI_STRING_UTILS_H_INCLUDED

#include <string>
#include <vector>


namespace tocccli
{

  /*
   * Checks if `str' starts with `str_to_check'. (i.e. `str_to_check'
   * is at the beginning of `str'.)
   */
  bool string_starts_with(std::string& str, std::string& str_to_check);

  /*
   * Splits the specified string from the specified delimiter.
   *
   * @param string_to_split: String to split.
   * @param delimiter: Char to split the string from.
   * @param count: Stop if these many splits took place.
   *   (Zero means no limit).
   */
  std::vector<std::string> split_string(const std::string& string_to_split,
                                        char delimiter,
                                        int count=0);
}

#endif /* TOCCCLI_STRING_UTILS_H_INCLUDED */
