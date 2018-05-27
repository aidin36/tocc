/*
 * This file is part of Tocc. (see <https://tocc.aidinhut.com>)
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

#include "actions/set_title_action.h"

#include <iostream>

#include "common/exceptions/cmd_usage_exceptions.h"
#include <libtocc/front_end/manager.h>


namespace tocccli
{

  SetTitleAction::SetTitleAction(libtocc::Manager* manager)
  {
    this->libtocc_manager = manager;
  }

  SetTitleAction::~SetTitleAction()
  {
  }

  std::string SetTitleAction::get_short_form()
  {
    return "-t";
  }

  std::string SetTitleAction::get_long_form()
  {
    return "--set-title";
  }

  std::string SetTitleAction::get_help_text()
  {
    return "-t, --set-title=TITLE\tSets the title of files.";
  }

  void SetTitleAction::execute(std::vector<libtocc::FileInfo> files,
                            std::vector<std::string> cmd_arguments)
  {
    if (cmd_arguments.empty() || cmd_arguments.size() > 1)
    {
      throw InvalidParametersError("-t, --set-title must have a title as an argument.");
    }

    //extract file ids to an array
    const char* file_ids[files.size()];
    for(int i = 0; i < files.size(); i++)
    {
      file_ids[i] = files[i].get_id();
    }

    this->libtocc_manager->set_titles(file_ids, files.size(), cmd_arguments.front().c_str());
  }
}
