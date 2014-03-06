/*
 * This file is part of TOCC. (see <http://www.github.com/aidin36/tocc>)
 * Copyright (C) 2013, 2014, Aidin Gharibnavaz <tocc@aidinhut.com>
 *
 * TOCC is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * TOCC is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 *  along with TOCC.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include "constants.h"
#include "libtocc.h"

bool front_end_copy_file_tests()
{
  try
  {
    libtocc::Manager manager("/tmp/");

    // Testing file copy.
    std::cout << "Creating a test file to copy..." << std::endl;
    std::ofstream file_stream;
    file_stream.open("/tmp/tocc_test_file_to_copy_2");
    file_stream << "some data...";
    file_stream.close();
    std::cout << GREEN << "    done." << DEFAULT << std::endl;

    std::cout << "Coping the file..." << std::endl;
    libtocc::FileInfo new_file = manager.copy_file("/tmp/tocc_test_file_to_copy_2");
    std::cout << new_file << std::endl;
    std::cout << GREEN << "    done." << DEFAULT << std::endl;

    std::cout << "Coping the file with info..." << std::endl;
    libtocc::TagsCollection tags;
    tags.add_tag("test");
    tags.add_tag("temporary");
    libtocc::FileInfo new_file_2 =
        manager.copy_file("/tmp/tocc_test_file_to_copy_2",
                          "Test File 2",
                          "/home/tocc/test_2",
                          &tags);
    std::cout << new_file_2 << std::endl;
    std::cout << GREEN << "    done." << DEFAULT << std::endl;

    return true;
  }
  catch (libtocc::BaseException &error)
  {
    std::cout << RED << "    Failed." << DEFAULT << std::endl;
    std::cout << "error was: " << error.what() << std::endl;
    return false;
  }
}
