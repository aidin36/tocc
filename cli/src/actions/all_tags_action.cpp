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

#include "actions/all_tags_action.h"

#include <iostream>

#include "libtocc/front_end/tag_statistics.h"
#include "common/exceptions/cmd_usage_exceptions.h"


namespace tocccli
{

  AllTagsAction::AllTagsAction(libtocc::Manager* manager)
  {
    this->libtocc_manager = manager;
  }

  AllTagsAction::~AllTagsAction()
  {
  }

  std::string AllTagsAction::get_short_form()
  {
    // It don't have any short form.
    return "";
  }

  std::string AllTagsAction::get_long_form()
  {
    return "--all-tags";
  }

  std::string AllTagsAction::get_help_text()
  {
    return "--all-tags\tPrints all tags, and number of files "\
           "          \teach tag assigned to.";
  }

  void AllTagsAction::execute(std::vector<libtocc::FileInfo> files,
                              std::vector<std::string> cmd_arguments)
  {
    if (!cmd_arguments.empty())
    {
      throw new InvalidParametersError("--all-tags don't accept any arguments.");
    }

    // Getting statistics.
    libtocc::TagStatisticsCollection statistics_collection =
        this->libtocc_manager->get_tags_statistics();

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
