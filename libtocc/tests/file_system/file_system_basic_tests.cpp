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

/*
 * Defines functions for testing FileManager class.
 */

#include <catch.hpp>
#include <string>
#include <fstream>
#include <unistd.h>

#include "common/base_exception.h"
#include "file_system/file_manager.h"

TEST_CASE("file_system: basic tests")
{
  std::string base_path = "/tmp/";
  std::string file_id = "t00f4ia";
  std::string equivalent_path = "/tmp/t/00/fa/ia";
  libtocc::FileManager file_manager(base_path);

  /*
   * Testing file creation.
   */
  // Creating first file.
  int file_descriptor = file_manager.create(file_id);
  REQUIRE(file_descriptor > 0);

  // Creating second file.
  int file_descriptor_2 = file_manager.create("t00f501");
  REQUIRE(file_descriptor_2 > 0);

  close(file_descriptor);
  close(file_descriptor_2);

  /*
   * Testing file open.
   */
  // Openning file.
  file_descriptor = file_manager.open_file(file_id, 'a');
  REQUIRE(file_descriptor > 0);

  // Writing to openned file.
  int write_result = write(file_descriptor, "Hi there!", 9);
  REQUIRE(write_result >= 0);
  close(file_descriptor);

  /*
   * Tesing file remove.
   */
  // Removing a file.
  file_manager.remove(file_id);

  /*
   * Testing file copy.
   */
  // Creating a test file to copy.
  std::ofstream file_stream;
  file_stream.open("/tmp/tocc_test_file_to_copy");
  file_stream << "some data...";
  file_stream.close();

  // Coping the file.
  file_manager.copy("/tmp/tocc_test_file_to_copy", "ta59800");
}
