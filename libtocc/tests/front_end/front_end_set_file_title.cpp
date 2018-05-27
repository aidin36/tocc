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

#include <catch.hpp>
#include <fstream>
#include <cstring>

#include "libtocc/front_end/manager.h"
#include "libtocc/front_end/file_info.h"
#include "libtocc/common/database_exceptions.h"



TEST_CASE("front_end: set files title tests")
{

  //Creating files

  std::ofstream file_stream1;
  file_stream1.open("/tmp/tocctests/tocc_test_random_file_1");
  file_stream1 << "I'm file 1";
  file_stream1.close();

  // Creating a file to import.
  std::ofstream file_stream2;
  file_stream1.open("/tmp/tocctests/tocc_test_random_file_2");
  file_stream1 << "I'm file 2";
  file_stream1.close();

  // Creating an instance of the manager.
  libtocc::Manager manager("/tmp/tocctests/");

  // Creating 2 files with a title and a traditional path.
  libtocc::FileInfo new_file1 = manager.import_file("/tmp/tocctests/tocc_test_random_file_1");
  libtocc::FileInfo new_file2 = manager.import_file("/tmp/tocctests/tocc_test_random_file_2");

  //Setting the title of the first file
  manager.set_title(new_file1.get_id(), "new title 1");

  //Test
  new_file1 = manager.get_file_info(new_file1.get_id());
  REQUIRE(strcmp(new_file1.get_title(), "new title 1") == 0);

  //Setting the title of a the 2 files simultanously
  const char* file_ids[] = { new_file1.get_id(), new_file2.get_id() };

  manager.set_titles(file_ids, 2, "new title 2");

  //Test
  new_file1 = manager.get_file_info(new_file1.get_id());
  new_file2 = manager.get_file_info(new_file2.get_id());
  REQUIRE(strcmp(new_file1.get_title(), "new title 2") == 0);
  REQUIRE(strcmp(new_file2.get_title(), "new title 2") == 0);

  //Remove the first file
  manager.remove_file(new_file1);

  //Setting a title of a file that doesn't exist
  REQUIRE_THROWS_AS(
    manager.set_title(new_file1.get_id(), "new title 3"),
    libtocc::DatabaseScriptLogicalError);

  //Setting the title of a group of files where some files don't exist in the database
  const char* file_ids2[] = { new_file2.get_id(), new_file1.get_id(), "0000012" };
  manager.set_titles(file_ids2, 3, "new title 3");
  
  //Test
  new_file2 = manager.get_file_info(new_file2.get_id());
  REQUIRE(strcmp(new_file2.get_title(), "new title 3") == 0);
}
