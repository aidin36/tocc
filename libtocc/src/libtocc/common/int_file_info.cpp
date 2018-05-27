/*
 * This file is part of Tocc. (see <https://tocc.aidinhut.com>)
 * Copyright (C) 2013, Aidin Gharibnavaz <aidin@t-o-c-c.com>
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

#include "libtocc/common/int_file_info.h"

#include <sstream>


namespace libtocc
{

  IntFileInfo::IntFileInfo(std::string file_id)
  {
    this->id = file_id;
  }

  IntFileInfo::IntFileInfo(std::string file_id,
                           std::string title,
                           std::string traditional_path,
                           std::vector<std::string> tags)
  {
    this->id = file_id;
    this->title = title;
    this->traditional_path = traditional_path;
    this->tags = tags;
  }

  IntFileInfo::IntFileInfo(const IntFileInfo& source)
  {
    this->id = source.id;
    this->title = source.title;
    this->traditional_path = source.traditional_path;
    this->tags = source.tags;
  }

  std::string IntFileInfo::get_id() const
  {
    return this->id;
  }

  void IntFileInfo::set_tags(std::vector<std::string> new_tags)
  {
    this->tags = new_tags;
  }

  void IntFileInfo::add_tag(std::string new_tag)
  {
    this->tags.push_back(new_tag);
  }

  std::vector<std::string> IntFileInfo::get_tags() const
  {
    return this->tags;
  }

  void IntFileInfo::set_title(std::string file_title)
  {
    this->title = file_title;
  }

  std::string IntFileInfo::get_title() const
  {
    return this->title;
  }

  void IntFileInfo::set_traditional_path(std::string path)
  {
    this->traditional_path = path;
  }

  std::string IntFileInfo::get_traditional_path() const
  {
    return this->traditional_path;
  }

  std::string IntFileInfo::to_string() const
  {
    std::stringstream result_stream;
    result_stream << "{" << std::endl;
    result_stream << "  file_id: " << this->get_id() << std::endl;
    result_stream << "  title: " << this->get_title() << std::endl;
    result_stream << "  traditional_path: " << this->get_traditional_path();
    result_stream << std::endl;

    // Writing tags.
    result_stream << "  tags: [";
    std::vector<std::string> tags = this->get_tags();
    std::vector<std::string>::iterator iterator = tags.begin();
    for (; iterator != tags.end(); ++iterator)
    {
      result_stream << *iterator << ", ";
    }
    result_stream << "]" << std::endl;

    result_stream << "}";

    return result_stream.str();
  }

  /*
   * Overrided operator for std::ostream.
   * So it can be used like:
   *   std::cout << file_info;
   */
  std::ostream& operator<<(std::ostream& stream,
                           const IntFileInfo& file_info)
  {
    return stream << file_info.to_string();
  }

  IntFileInfo& IntFileInfo::operator=(const IntFileInfo& source)
  {
    if (this == &source)
    {
      return *this;
    }

    this->id = source.id;
    this->title = source.title;
    this->traditional_path = source.traditional_path;
    this->tags = source.tags;

    return *this;
  }
}
