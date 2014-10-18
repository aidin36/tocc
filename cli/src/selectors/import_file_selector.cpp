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

#include "selectors/import_file_selector.h"
#include "common/exceptions/cmd_usage_exceptions.h"
#include "engine/wild_card_manager.h"
#include <cassert>
#include <cstdio>

namespace tocccli
{

  ImportFileSelector::ImportFileSelector(libtocc::Manager* manager)
  {
    this->libtocc_manager = manager;
  }

  ImportFileSelector::~ImportFileSelector()
  {
  }

  std::string ImportFileSelector::get_short_form()
  {
    return "-i";
  }

  std::string ImportFileSelector::get_long_form()
  {
    return "--import";
  }

  std::string ImportFileSelector::get_help_text()
  {
    return "-i, --import=PATH\tImports a file from the specified path to the \n"
           "                 \tTocc managed file system.";
  }

  std::vector<libtocc::FileInfo> ImportFileSelector::execute(std::vector<std::string> cmd_arguments)
  {
    if (cmd_arguments.size() != 1)
    {
      throw InvalidParametersError("-i and --import must have an argument.");
    }

    assert(WILDCARD_MANAGER != 0);

    std::vector<libtocc::FileInfo> result;
    std::vector<std::string> files = WILDCARD_MANAGER->detect_wild_cards(cmd_arguments.front());
    for(int i = 0; i < files.size(); i++)
    {      
      libtocc::FileInfo new_file = this->libtocc_manager->import_file(files[i].c_str());   
      printf("%s \n", files[i].c_str());
      result.push_back(new_file);
    }
    
    return result;
  }

}
