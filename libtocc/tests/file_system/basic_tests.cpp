/*
 * This file is part of TOCC. (see <http://www.github.com/aidin36/tocc>)
 * Copyright (C) 2013, Aidin Gharibnavaz <tocc@aidihut.com>
 *
 * TOCC is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Foobar is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 *  along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Defines functions for testing FileManager class.
 */

#include <string>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <string.h> // For strerror function.

#include "constants.h"
#include "common/base_exception.h"
#include "file_system/file_manager.h"


bool file_manager_basic_tests()
{
  std::string base_path = "/tmp/";
  std::string file_id = "t00f4ia";
  std::string equivalent_path = "/tmp/t/00/fa/ia";
  libtocc::FileManager file_manager(base_path);

  try
  {
    // Testing file creation.
    std::cout << "creating first file..." << std::endl;

    int file_descriptor = file_manager.create(file_id);

    std::cout << GREEN << "    created. FD: " << file_descriptor << DEFAULT << std::endl;

    std::cout << "creating second file..." << std::endl;

    int file_descriptor_2 = file_manager.create("t00f501");

    std::cout << GREEN << "    created. FD: " << file_descriptor_2 << DEFAULT << std::endl;

    close(file_descriptor);
    close(file_descriptor_2);

    // Testing file open.
    std::cout << "Openning file..." << std::endl;
    file_descriptor = file_manager.open_file(file_id, 'a');
    std::cout << GREEN << "    done. FD: " << file_descriptor << DEFAULT << std::endl;

    std::cout << "Writing to openned file..." << std::endl;
    int write_result = write(file_descriptor, "Hi there!", 9);
    if (write_result < 0)
    {
      std::cout << RED << "    Failed." << DEFAULT << std::endl;
      std::cout << "error number was: " << write_result << std::endl;
      return false;
    }
    close(file_descriptor);
    std::cout << GREEN << "    done." << DEFAULT << std::endl;

    // Tesing file remove.
    std::cout << "Removing a file..." << std::endl;
    file_manager.remove(file_id);
    std::cout << GREEN << "    done." << DEFAULT << std::endl;

    // Testing file copy.
    std::cout << "Creating a test file to copy..." << std::endl;
    std::ofstream file_stream;
    file_stream.open("/tmp/tocc_test_file_to_copy");
    file_stream << "some data...";
    file_stream.close();
    std::cout << GREEN << "    done." << DEFAULT << std::endl;

    std::cout << "Coping a file..." << std::endl;
    file_manager.copy("/tmp/tocc_test_file_to_copy", "ta59800");
    std::cout << GREEN << "    done." << DEFAULT << std::endl;

    return true;
  }
  catch (libtocc::BaseException& error)
  {
    std::cout << RED << "    Failed." << DEFAULT << std::endl;
    std::cout << "error was: " << error.what() << std::endl;
    //std::cout << "errno: " << error.errno << std::endl;

    return false;
  }
}
