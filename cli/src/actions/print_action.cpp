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

#include "actions/print_action.h"
#include "common/exceptions/cmd_usage_exceptions.h"

namespace tocccli
{

  PrintAction::PrintAction(libtocc::Manager* manager)
  {
    this->libtocc_manager = manager;
  }

  PrintAction::~PrintAction()
  {
  }

  std::string PrintAction::get_short_form()
  {
    return "-p";
  }

  std::string PrintAction::get_long_form()
  {
    return "--print";
  }

  std::string PrintAction::get_help_text()
  {
    return "-p, --print\tPrints founded files on output.";
  }

  void PrintAction::execute(std::vector<libtocc::FileInfo> files,
                            std::vector<std::string> cmd_arguments)
  {
    if (!cmd_arguments.empty())
    {
      throw InvalidParametersError("`--print' does not accept any argument.");
    }

    std::vector<libtocc::FileInfo>::iterator iterator = files.begin();
    for (; iterator != files.end(); ++iterator)
    {
      std::cout << (*iterator).get_title() << "\t";
    }
    std::cout << std::endl;
  }
}
