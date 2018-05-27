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

#include "utils/string_utils.h"

#include <sstream>


namespace toccfs
{

  std::vector<std::string> split_string(const std::string& string_to_split,
                                        char delimiter)
  {
    std::vector<std::string> result;

    std::stringstream stream(string_to_split);
    std::string item;
    while (std::getline(stream, item, delimiter))
    {
      if (!item.empty())
      {
        result.push_back(item);
      }
    }

    return result;
  }

  bool string_ends_with(const std::string& str,
                          const std::string& str_to_check)
  {
    if (str.size() >= str_to_check.size())
    {
      return false;
    }

    return str.compare(str.size() - str_to_check.size(),
                       str_to_check.size(), str_to_check) == 0;
  }

}
