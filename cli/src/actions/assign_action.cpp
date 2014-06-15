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

#include "common/exceptions/cmd_usage_exceptions.h"
#include "actions/assign_action.h"


namespace tocccli
{

  AssignAction::AssignAction(libtocc::Manager* manager)
  {
    this->libtocc_manager = manager;
  }

  AssignAction::~AssignAction()
  {
  }

  std::string AssignAction::get_short_form()
  {
    return "-a";
  }

  std::string AssignAction::get_long_form()
  {
    return "--assign";
  }

  std::string AssignAction::get_help_text()
  {
    return "-a, --assign=TAGS\tAssigns tags to files. TAGS is a list of tags\n"\
           "                 \tseparated by space.";
  }

  void AssignAction::execute(std::vector<libtocc::FileInfo> files, std::vector<std::string> cmd_arguments)
  {
    if (cmd_arguments.empty())
    {
      throw InvalidParametersError("-a, --assign, must have at least one argument.");
    }

    // Converting files vector to array.
    const char* files_array[files.size()];
    for (int i = 0; i < files.size(); i++)
    {
      files_array[i] = files[i].get_id();
    }

    // Converting tags vector to a tags collection.
    libtocc::TagsCollection tags_collection(cmd_arguments.size());
    std::vector<std::string>::iterator args_iterator = cmd_arguments.begin();
    for (; args_iterator != cmd_arguments.end(); args_iterator++)
    {
      tags_collection.add_tag(args_iterator->c_str());
    }

    this->libtocc_manager->assign_tags(files_array, files.size(), &tags_collection);
  }
}
