/*
 * This file is part of Tocc. (see <http://t-o-c-c.com>)
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

#include <sstream>

#include "libtocc/common/int_file_info.h"

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

  FileInfoCollection::FileInfoCollection()
  {
  }

  FileInfoCollection::FileInfoCollection(std::vector<IntFileInfo> file_infos)
  {
    this->file_infos = file_infos;
  }

  FileInfoCollection::FileInfoCollection(IntFileInfo file_infos[], int count)
  {
    // Fastest way for appending an array to a vector.
    this->file_infos.reserve(count);
    this->file_infos.insert(this->file_infos.end(),
                            &file_infos[0],
                            &file_infos[count - 1]);
  }

  void FileInfoCollection::add_file_info(IntFileInfo file_info)
  {
    this->file_infos.push_back(file_info);
  }

  void FileInfoCollection::add_file_infos(std::vector<IntFileInfo> file_infos)
  {
    // Fastest way for appending two vectors.
    this->file_infos.insert(this->file_infos.end(),
                            file_infos.begin(),
                            file_infos.end());
  }

  void FileInfoCollection::add_file_infos(IntFileInfo file_infos[], int count)
  {
    this->file_infos.reserve(this->file_infos.size() + count);
    this->file_infos.insert(this->file_infos.end(),
                            &file_infos[0],
                            &file_infos[count - 1]);
  }
  
  std::vector<IntFileInfo> FileInfoCollection::get_file_infos()
  {
    return this->file_infos;
  }

  std::vector<std::string> FileInfoCollection::get_file_ids()
  {
    std::vector<std::string> result;
    result.reserve(this->file_infos.size());

    for (std::vector<IntFileInfo>::iterator iterator = this->file_infos.begin();
         iterator != this->file_infos.end(); iterator++)
    {
      result.push_back((*iterator).get_id());
    }

    return result;
  }
}
