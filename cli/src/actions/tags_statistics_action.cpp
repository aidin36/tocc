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

#include "actions/tags_statistics_action.h"

#include <iostream>

#include "libtocc/front_end/tag_statistics.h"
#include "common/exceptions/cmd_usage_exceptions.h"


namespace tocccli
{

  TagsStatisticsAction::TagsStatisticsAction(libtocc::Manager* manager)
  {
    this->libtocc_manager = manager;
  }

  TagsStatisticsAction::~TagsStatisticsAction()
  {
  }

  std::string TagsStatisticsAction::get_short_form()
  {
    return "-s";
  }

  std::string TagsStatisticsAction::get_long_form()
  {
    return "--tags-statistics";
  }

  std::string TagsStatisticsAction::get_help_text()
  {
    return "-s, --tags-statistics\tPrints all tags, and\n"\
           "          \tnumber of files each tag assigned to.";
  }

  void TagsStatisticsAction::execute(std::vector<libtocc::FileInfo> files,
                                     std::vector<std::string> cmd_arguments)
  {
    if (!cmd_arguments.empty())
    {
      throw InvalidParametersError("--all-tags don't accept any arguments.");
    }

    libtocc::TagStatisticsCollection statistics_collection;

    // Getting statistics.
    if (files.empty())
    {
      statistics_collection = this->libtocc_manager->get_tags_statistics();
    }
    else
    {
      // Converting files vector to array of IDs.
      const char* sizevar;
      const char** files_array = (const char**)malloc(files.size() * sizeof sizevar);
      for (int i = 0; i < files.size(); i++)
      {
        files_array[i] = files[i].get_id();
      }

      statistics_collection =
          this->libtocc_manager->get_tags_statistics(files_array, files.size());
      free(files_array);
    }

    // Print statistics in a pretty format.
    std::cout << "Assigned Files\tTag" << std::endl;
    std::cout << "--------------\t---" << std::endl;

    libtocc::TagStatisticsCollection::Iterator iterator(&statistics_collection);
    for (; !iterator.is_finished(); iterator.next())
    {
      libtocc::TagStatistics tag_statistics = iterator.get();
      std::cout << tag_statistics.get_assigned_files() << "\t\t";
      std::cout << tag_statistics.get_tag() << std::endl;
    }
  }

}
