/*
 * This file is part of Tocc. (see <http://t-o-c-c.com>)
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


TEST_CASE("front_end: delete file")
{
  // Creating a file to import.
  std::ofstream file_stream;
  file_stream.open("/tmp/tocc_test_file_to_delete_1");
  file_stream << "some data...";
  file_stream.close();

  // Creating an instance of the manager.
  libtocc::Manager manager("/tmp/");

  // Importing the file
    libtocc::FileInfo test_file =
        manager.import_file("/tmp/tocc_test_file_to_delete_1");
  
  std::string file_id = test_file.get_id();
  
  REQUIRE(manager.delete_file(file_id.c_str()) == true);

  //Deleting a file that doesn't exist
  REQUIRE_THROWS_AS(
      manager.delete_file(file_id.c_str()), 
      libtocc::DatabaseScriptLogicalError);
}

