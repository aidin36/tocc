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


#include "wild_cards/asterisk_wild_card.h"
#include "utilities/file_system.h"
#include <cstring>

namespace tocccli
{
   std::vector<std::string> AsteriskWildCard::match(std::string dir_path, std::string file_expression)
  {
    std::vector<std::string> files;
    // case : path/folder/*
    if(strcmp(file_expression.c_str(), expr) == 0)
    {
      files = get_all_files(dir_path);
    }
    return files;
  }
  
  std::vector<std::string> AsteriskWildCard::match(std::string dir_path)
  {
    std::vector<std::string> files;

    return files;
  }
}
