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
 * Defines main function, which starts all tests.
 */

// The following define causes the Catch to generate a main fucntion here.
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <iostream>

/*
** Initialisation of Library
*/
class TestInitialiser
{
  public:
    TestInitialiser()
    {
      // clean previous test files
      if (int status = system("rm -rf /tmp/tocctests"))
      {
        std::cout << "Test initialisation failed -\
          Unable to delete files" << std::endl;
        exit(status);
      }
      else if (int status = system("mkdir /tmp/tocctests"))
      {
        std::cout << "Test initialisation failed -\
          Unable to create base directory" << std::endl;
        exit(status);
      }
    };
};

TestInitialiser now;
