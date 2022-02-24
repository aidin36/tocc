/*
 * This file is part of Tocc. (see <https://tocc.aidinhut.com>)
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

/*
 * Defines functions for testing FileManager class.
 */

#include <catch.hpp>
#include "testdb_path.hpp"
#include <string>
#include <fstream>
#ifdef _MSC_VER
#include "unistdx.h"
#else
#include <unistd.h>
#endif

#include "libtocc/common/base_exception.h"
#include "libtocc/file_system/file_manager.h"

TEST_CASE("file_system: basic tests")
{
  std::string base_path = testdb_path("");
  std::string file_id = "t00f4ia";
  std::string equivalent_path = testdb_path("t/00/fa/ia");
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
#ifdef _MSCCVER
#undef close
#endif
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
  file_stream.open(testdb_path("tocc_test_file_to_copy").c_str());
  file_stream << "some data...";
#undef close
  file_stream.close();
  // Coping the file.
  file_manager.copy(testdb_path("tocc_test_file_to_copy").c_str(), "ta59800");
}
