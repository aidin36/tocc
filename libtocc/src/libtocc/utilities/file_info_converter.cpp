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

#include "libtocc/utilities/file_info_converter.h"

#include <string>
#include <vector>

#include "libtocc/database/base23.h"


namespace libtocc
{

  FileInfo to_external_file_info(const IntFileInfo* internal_file_info,
                                 FileManager* file_manager)
  {
    // FileInfo copies each of these parameters. So, we just passed a
    // pointer to the internal variable of each string.

    std::vector<std::string> tags_vector = internal_file_info->get_tags();
    TagsCollection tags = vector_to_tags(&tags_vector);

    FileInfo result(internal_file_info->get_id().c_str(),
                    internal_file_info->get_title().c_str(),
                    internal_file_info->get_traditional_path().c_str(),
                    file_manager->get_physical_path(internal_file_info->get_id()).c_str(),
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

  FileInfoCollection to_external_file_infos(std::vector<IntFileInfo> internal_file_infos,
                                            FileManager* file_manager)
  {
    if (internal_file_infos.empty())
    {
      // Returning an empty collection.
      return FileInfoCollection();
    }

    // File info collection with reserved size.
    FileInfoCollection result((int) internal_file_infos.size());

    std::vector<IntFileInfo>::iterator iterator = internal_file_infos.begin();
    for (; iterator != internal_file_infos.end(); ++iterator)
    {
      result.add_file_info(to_external_file_info(&*iterator, file_manager));
    }

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

  TagsCollection vector_to_tags(const std::vector<std::string>* const vector)
  {
    if (vector->empty())
    {
      return TagsCollection();
    }

    const size_t sz = vector->size();
    
    char c;
    TagsCollection tc = TagsCollection();
    int size1 = sizeof &c;
    char** tags = (char**) malloc(size1 * sz);
    for (unsigned int i = 0; i < vector->size(); ++i)
    {
        tags[i] = (char *)(*vector)[i].c_str();
    }

    tc = TagsCollection((const char **)tags, (int) vector->size());
    free(tags);
    return tc;
  }

  std::vector<std::string> file_info_collection_to_vector_ids(const FileInfoCollection& file_info_collection)
  {
    std::vector<std::string> file_ids;

    FileInfoCollection::Iterator file_info_collection_iterator(&file_info_collection);
    for (; !file_info_collection_iterator.is_finished(); ++file_info_collection_iterator)
    {
      if(FileInfo* file_info = const_cast<FileInfo*>(file_info_collection_iterator.get()))
      {
        file_ids.push_back(std::string(file_info->get_id()));
      }
    }
    return file_ids;
  }

  std::vector<std::string> const_char_array_to_vector(const char* char_array[], int char_array_size)
  {
    std::vector<std::string> char_array_vector;

    for(int i = 0; i < char_array_size; i++)
    {
      char_array_vector.push_back(std::string(char_array[i]));
    }

    return char_array_vector;
  }

  std::vector<unsigned long> string_vector_to_ulong_vector(const std::vector<std::string> vect_of_strings)
  {
    std::vector<unsigned long> converted_strings;
    std::vector<std::string>::const_iterator iterator = vect_of_strings.begin();
    for(; iterator != vect_of_strings.end(); ++iterator)
    {
      converted_strings.push_back(from_base23(*iterator));
    }

    return converted_strings;
  }
}
