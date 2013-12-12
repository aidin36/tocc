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

#include "file_system/file_manager.h"

const std::string GREEN = "\033[0;32m";
const std::string RED = "\033[0;31m";
const std::string DEFAULT = "\033[0m";

bool file_manager_basic_tests()
{
  std::string base_path = "/tmp/";
  std::string file_id = "tc00f4ia";
  std::string equivalent_path = "/tmp/tc/00/fa/ia";
  libtocc::FileManager file_manager(base_path);

  try
  {
    std::cout << "creating first file..." << std::endl;

    int file_descriptor = file_manager.create(file_id);

    std::cout << GREEN << "    created. FD: " << file_descriptor << DEFAULT << std::endl;

    std::cout << "creating second file..." << std::endl;

    int file_descriptor_2 = file_manager.create("tc00f501");

    std::cout << GREEN << "    created. FD: " << file_descriptor_2 << DEFAULT << std::endl;

    return true;
  }
  catch (...)
  {
    std::cout << RED << "    Failed." << DEFAULT << std::endl;
    return false;
  }
}
