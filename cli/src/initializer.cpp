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

/*
 * This is a stand alone binary (tocc-initialize), which initialize a
 * Tocc Managed File System.
 */

#include <iostream>
#include <unistd.h> // getcwd
#include <cstdio> // FILENAME_MAX
#include <errno.h>

#include <libtocc/front_end/manager.h>

#include "utilities/errno_translator.h"


int main(int argc, char* argv[])
{
  // Checking if arguments are correct.
  if (argc > 2)
  {
    std::cout << "Invalid number of arguments." << std::endl;
    std::cout << "You should provide a path as a single argument. i.e.:" << std::endl;
    std::cout << "   tocc-initialize /opt/tocc-managed/" << std::endl;
    std::cout << "Or provide no argument, which initializes the current directory." << std::endl;

    return 101;
  }

  std::string base_path;

  if (argc == 2)
  {
    // Creating a standard string from the first argument.
    base_path = argv[1];
  }
  else
  {
    // Using current directory as the base path.
    char path_buffer[FILENAME_MAX];
    if (!getcwd(path_buffer, FILENAME_MAX))
    {
      std::cout << tocccli::translate_errno(errno) << std::endl;
      return 201;
    }
    base_path = path_buffer;
  }

  try
  {
    // Initializing the path.
    libtocc::Manager libtocc_manager(base_path.c_str());
    libtocc_manager.initialize();
  }
  catch (std::exception& error)
  {
    std::cout << error.what() << std::endl;
  }
}
