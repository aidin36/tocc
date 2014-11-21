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

#include "engine/fs_handler.h"

#include "libtocc/exprs/connectives.h"
#include "libtocc/exprs/query.h"

#include "utils/string_utils.h"


namespace toccfs
{

  libtocc::FileInfo get_empty_file_info()
  {
    // A work-around for not having a NULL FileInfo.
    return libtocc::FileInfo("-1");
  }

  FSHandler::FSHandler(std::string base_path)
  {
    this->libtocc_manager = new libtocc::Manager(base_path.c_str());

    this->base_path = base_path;
  }

  FSHandler::~FSHandler()
  {
    delete this->libtocc_manager;
  }

  std::string FSHandler::get_base_path()
  {
    return this->base_path;
  }

  libtocc::FileInfo FSHandler::get_by_path(std::string path)
  {
    // First, we check if the specified path matches exactly with a
    // Traditional Path. If it is, we return that file.
    // Then, we check if the path contains tags and title of a file. We assume
    // each directory in the path is a tag, and the last element is title of
    // a file. If it matches a single file, we return that.

    /*
     * First try: Checking if path exactly matches a Traditional Path.
     */
    // TODO: First, check the traditional path.

    /*
     * Second try: Last element is the file title and others are tags.
     */
    std::vector<std::string> path_items = split_string(path, '/');

    if (path_items.empty())
    {
      // Returning a NULL file info.
      return get_empty_file_info();
    }

    // Assume the last element is the file title.
    libtocc::Title title_expr(path_items.back().c_str());
    path_items.pop_back();
    libtocc::And main_and(title_expr);

    if (!path_items.empty())
    {
      // Each of the items considered a tag.
      std::vector<std::string>::iterator path_items_iterator = path_items.begin();
      for (; path_items_iterator != path_items.end(); path_items_iterator++)
      {
        if (*path_items_iterator == ".." || *path_items_iterator == ".")
        {
          // Ignore . or ..
          continue;
        }
        libtocc::Tag tag_expr(path_items_iterator->c_str());
        main_and.add(tag_expr);
      }
    }

    // Executing the query.
    libtocc::Query second_query(main_and);
    libtocc::FileInfoCollection second_query_result =
        this->libtocc_manager->search_files(second_query);

    if (second_query_result.size() == 1)
    {
      // If exactly one file found, this is what we wanted.
      libtocc::FileInfoCollection::Iterator query_result_iterator(&second_query_result);
      // Copying the pointer.
      libtocc::FileInfo result(*query_result_iterator.get());

      return result;
    }

    // Nothing found. Returning a NULL FileInfo.
    return get_empty_file_info();
  }


  std::vector<libtocc::FileInfo> FSHandler::query_by_path(std::string path)
  {
    // We assume that each element of the path is a tag, and return
    // everything matches with it.

    std::vector<std::string> path_items = split_string(path, '/');

    // The previous step didn't find the correct result. Now, assuming
    // that all the elements in path are tags.
    std::vector<std::string>::iterator path_items_iterator = path_items.begin();

    // Adding first element to the And.
    libtocc::Tag first_tag(path_items_iterator->c_str());
    libtocc::And third_main_and(first_tag);
    path_items_iterator++;

    for (; path_items_iterator != path_items.end(); path_items_iterator++)
    {
      if (*path_items_iterator == ".." || *path_items_iterator == ".")
      {
        // Ignore . or ..
        continue;
      }

      libtocc::Tag tag_expr(path_items_iterator->c_str());
      third_main_and.add(tag_expr);
    }

    // Executing the query.
    libtocc::Query third_query(third_main_and);
    libtocc::FileInfoCollection third_query_result =
        this->libtocc_manager->search_files(third_query);

    if (third_query_result.size() > 0)
    {
      std::vector<libtocc::FileInfo> result;
      libtocc::FileInfoCollection::Iterator query_result_iterator(&third_query_result);
      for (; !query_result_iterator.is_finished(); query_result_iterator.next())
      {
        result.push_back(*query_result_iterator.get());
      }

      return result;
    }

    // Nothing found? Returning an empty result.
    std::vector<libtocc::FileInfo> result;
    return result;
  }

  std::vector<std::string> FSHandler::get_related_tags(std::vector<libtocc::FileInfo> files)
  {
    // Converting list of FileInfo into list of IDs.
    const char* file_ids[files.size()];
    for (int i = 0; i < files.size(); i++)
    {
      file_ids[i] = files[i].get_id();
    }

    libtocc::TagStatisticsCollection statistics =
        this->libtocc_manager->get_tags_statistics(file_ids, files.size());

    // Converting collection into a vector.
    std::vector<std::string> result;
    result.reserve(statistics.size());
    libtocc::TagStatisticsCollection::Iterator iterator(&statistics);
    for (; !iterator.is_finished(); iterator.next())
    {
      result.push_back(iterator.get().get_tag());
    }

    return result;
  }

  std::vector<std::string> FSHandler::get_all_tags()
  {
    libtocc::TagStatisticsCollection statistics =
        this->libtocc_manager->get_tags_statistics();

    // Converting collection into a vector.
    std::vector<std::string> result;
    result.reserve(statistics.size());
    libtocc::TagStatisticsCollection::Iterator iterator(&statistics);
    for (; !iterator.is_finished(); iterator.next())
    {
      result.push_back(iterator.get().get_tag());
    }

    return result;
  }
}
