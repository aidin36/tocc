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

void file_manager_basic_tests()
{
  std::string base_path = "/tmp/";
  std::string file_id = "tc00f4ia";
  std::string equivalent_path = "/tmp/tc/00/fa/ia";
  libtocc::FileManager file_manager(base_path);

  int file_descriptor = file_manager.create(file_id);

  std::cout << "file created. FD: " << file_descriptor << std::endl;
}
