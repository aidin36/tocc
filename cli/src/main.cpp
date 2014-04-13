/*
 * This file is part of Tocc. (see <http://www.github.com/aidin36/tocc>)
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

#include <string>
#include <vector>
#include <unistd.h> // getcwd
#include <cstdio> // FILENAME_MAX
#include <iostream>
#include <errno.h>

#include "utilities/cmd_parser.h"
#include "utilities/errno_translator.h"
#include "engine/cmd_manager.h"


using namespace tocccli;

int main(int argc, char* argv[])
{

  // Parsing passed parameters.
  std::vector<std::vector<std::string> > cmd_parameters = parse_cmd(argc, argv);

  // Finding the current directory (default of Base Path).
  char path_buffer[FILENAME_MAX];
  if (!getcwd(path_buffer, FILENAME_MAX))
  {
    std::cout << translate_errno(errno) << std::endl;
    return 201;
  }
  std::string base_path(path_buffer);

  // Checking if user specified base path option.
  std::vector<std::vector<std::string> >::iterator iterator =
      cmd_parameters.begin();
  for (; iterator != cmd_parameters.end(); ++iterator)
  {
    if ((*iterator).front() == "-p" ||
        (*iterator).front() == "--base-path")
    {
      base_path = (*iterator).back();
      if (base_path == "")
      {
        std::cout << "-p or --base-path must have a value." << std::endl;
        return -101;
      }
      break;
    }
  }

  std::cout << "Base Path: " << base_path << std::endl;

  // Executing.
  CmdManager cmd_manager(base_path);
  cmd_manager.execute(cmd_parameters);
}
