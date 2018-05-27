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

#include "actions/remove_action.h"
#include "common/exceptions/cmd_usage_exceptions.h"
#include <libtocc/front_end/manager.h>

namespace tocccli
{

  RemoveAction::RemoveAction(libtocc::Manager* manager)
  {
    libtocc_manager = manager;
  }

  RemoveAction::~RemoveAction()
  {
  }

  std::string RemoveAction::get_short_form()
  {
    return "-r";
  }

  std::string RemoveAction::get_long_form()
  {
    return "--remove";
  }

  std::string RemoveAction::get_help_text()
  {
    return "-r, --remove\tRemoves the giving file(s).";
  }

  void RemoveAction::execute(std::vector<libtocc::FileInfo> files, std::vector<std::string> cmd_arguments)
  {
    if(!cmd_arguments.empty())
    {
      throw InvalidParametersError("-r, --remove, doesn't accept arguments.");
    }

    //Extracting files ids into an array
    const char* file_ids[files.size()];
    for(int i = 0; i < files.size(); i++)
    {
      file_ids[i] = files[i].get_id();
    }

    //Removing the files
    if(libtocc_manager != 0)
    {
      this->libtocc_manager->remove_files(file_ids, files.size());
    }
  }
}
