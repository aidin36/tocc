/*
 * This file is part of Tocc. (see <http://www.github.com/aidin36/tocc>)
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

#include <string>
#include <vector>

#include "utilities/file_info_converter.h"

namespace libtocc
{

  FileInfo to_external_file_info(const IntFileInfo* internal_file_info)
  {
    // FileInfo copies each of these parameters. So, we just passed a
    // pointer to the internal variable of each string.

    std::vector<std::string> tags_vector = internal_file_info->get_tags();
    TagsCollection tags = vector_to_tags(&tags_vector);

    FileInfo result(internal_file_info->get_id().c_str(),
                    internal_file_info->get_title().c_str(),
                    internal_file_info->get_traditional_path().c_str(),
                    &tags);
    return result;
  }

  IntFileInfo to_internal_file_info(const FileInfo* external_file_info)
  {
    TagsCollection tags = external_file_info->get_tags();
    std::vector<std::string> tags_vector = tags_to_vector(&tags);

    IntFileInfo result(external_file_info->get_id(),
                       external_file_info->get_title(),
                       external_file_info->get_traditional_path(),
                       tags_vector);

    return result;
  }

  std::vector<std::string> tags_to_vector(const TagsCollection* collection)
  {
    std::vector<std::string> tags_vector;
    tags_vector.reserve(collection->size());

    TagsCollection::Iterator iterator(collection);
    for (; !iterator.is_finished(); iterator.next())
    {
      tags_vector.push_back(iterator.get());
    }

    return tags_vector;
  }

  TagsCollection vector_to_tags(const std::vector<std::string>* vector)
  {
    if (vector->empty())
    {
      return TagsCollection();
    }

    const char* tags[vector->size()];
    for (unsigned int i = 0; i < vector->size(); ++i)
    {
      tags[i] = (*vector)[i].c_str();
    }

    return TagsCollection(tags, vector->size());
  }

}
