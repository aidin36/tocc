/*
 * This file is part of TOCC. (see <http://www.github.com/aidin36/tocc>)
 * Copyright (C) 2013, Aidin Gharibnavaz <tocc@aidihut.com>
 *
 * TOCC is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * TOCC is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 *  along with TOCC.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "common/int_file_info.h"

namespace libtocc
{

  IntFileInfo::IntFileInfo(std::string file_id)
  {
    this->id = file_id;
  }

  void IntFileInfo::set_tags(std::vector<std::string> new_tags)
  {
    this->tags = new_tags;
  }

  void IntFileInfo::add_tag(std::string new_tag)
  {
    this->tags.push_back(new_tag);
  }

  std::vector<std::string> IntFileInfo::get_tags()
  {
    return this->tags;
  }

  void IntFileInfo::set_title(std::string file_title)
  {
    this->title = file_title;
  }

  std::string IntFileInfo::get_title()
  {
    return this->title;
  }

  void IntFileInfo::set_traditional_path(std::string path)
  {
    this->traditional_path = path;
  }

  std::string IntFileInfo::get_traditional_path()
  {
    return this->traditional_path;
  }

}
