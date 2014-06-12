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

#include <iostream>

#include "actions/set_title_action.h"
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
    return "-t, --set-title\tSets the title of the file on the output.";
  }

  void SetTitleAction::execute(std::vector<libtocc::FileInfo> files,
                            std::vector<std::string> cmd_arguments)
  {
    if (cmd_arguments.empty())
    {
      throw InvalidParametersError("`-t, --set-title' needs a title as argument.");
    }

    //Sets the title only for the first file with the first argument of the command
    //it silently ignores the other files and arguments of the command
    std::vector<libtocc::FileInfo>::iterator iterator = files.begin();
    std::vector<std::string>::iterator cmd_arguments_iterator = cmd_arguments.begin();
  
    if(this->libtocc_manager != 0)
    {
      this->libtocc_manager->set_title((*iterator).get_id(), (*cmd_arguments_iterator).c_str());
    }
  }
}
