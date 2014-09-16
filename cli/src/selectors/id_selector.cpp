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

#include "selectors/id_selector.h"
#include "common/exceptions/cmd_usage_exceptions.h"

namespace tocccli
{

  IDSelector::IDSelector(libtocc::Manager* manager)
  {
    this->libtocc_manager = manager;
  }

  IDSelector::~IDSelector()
  {
  }

  std::string IDSelector::get_short_form()
  {
    return "-d";
  }

  std::string IDSelector::get_long_form()
  {
    return "--id";
  }

  std::string IDSelector::get_help_text()
  {
    return "-d, --id=ID\tSelects a file by its ID.";
  }

  std::vector<libtocc::FileInfo> IDSelector::execute(std::vector<std::string> cmd_arguments)
  {
    if (cmd_arguments.empty() || cmd_arguments.size() != 1)
    {
      throw InvalidParametersError("-i or --id takes exactly one argument.");
    }

    libtocc::FileInfo selected_file =
        this->libtocc_manager->get_file_info(cmd_arguments.front().c_str());

    std::vector<libtocc::FileInfo> result;
    result.push_back(selected_file);
    return result;
  }
}
