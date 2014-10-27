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

#include <string>
#include <vector>
#include <utility>
#include <unistd.h> // getcwd
#include <cstdio> // FILENAME_MAX
#include <iostream>
#include <errno.h>

#include "common/cmd_param.h"
#include "utilities/cmd_parser.h"
#include "utilities/errno_translator.h"
#include "engine/cmd_manager.h"


using namespace tocccli;

int main(int argc, char* argv[])
{

  // Parsing passed parameters.
  std::vector<CmdParam> cmd_parameters = parse_cmd(argc, argv);

  // Finding the current directory (default of Base Path).
  char path_buffer[FILENAME_MAX];
  if (!getcwd(path_buffer, FILENAME_MAX))
  {
    std::cout << translate_errno(errno) << std::endl;
    return 201;
  }
  std::string base_path(path_buffer);

  // Checking if user specified base path option.
  std::vector<CmdParam>::iterator iterator = cmd_parameters.begin();
  for (; iterator != cmd_parameters.end(); ++iterator)
  {
    if ((*iterator).option == "-b" ||
        (*iterator).option == "--base-path")
    {
      if ((*iterator).arguments.empty())
      {
        std::cout << "-b or --base-path must have an argument." << std::endl;
        return -101;
      }
      if ((*iterator).arguments.size() != 1)
      {
        std::cout << "-b or --base-path take exactly one argument." << std::endl;
        return -102;
      }

      base_path = (*iterator).arguments.front();

      break;
    }
  }

  // Executing.
  CmdManager cmd_manager(base_path);
  cmd_manager.execute(cmd_parameters);
}
