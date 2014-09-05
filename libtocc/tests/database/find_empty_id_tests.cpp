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

#include "catch.hpp"
#include <string>
#include <vector>
#include <cstdlib>

#include "libtocc/common/int_file_info.h"
#include "libtocc/database/database.h"


TEST_CASE("database: find empty ID")
{
  // Creating the database.
  libtocc::Database db("/tmp/tocctests/tocc.test.db");

  // Creating files
  libtocc::IntFileInfo new_file_1 = db.create_file("file__1", "/old/path");
  libtocc::IntFileInfo new_file_2 = db.create_file("file__2", "/old/path");

  //delete file 1
  std::vector<std::string> ids_to_delete;
  ids_to_delete.push_back(new_file_1.get_id());
  std::vector<libtocc::IntFileInfo> founded_files;
  
  db.remove_files(ids_to_delete, founded_files);

  //create a new file
  libtocc::IntFileInfo new_file_3 = db.create_file("file__3", "/old/path");
  
  REQUIRE(atoi(new_file_1.get_id().c_str()) == atoi(new_file_3.get_id().c_str()));

  //Delete a bunch of files
  ids_to_delete.clear();
  ids_to_delete.push_back(new_file_2.get_id());
  ids_to_delete.push_back(new_file_3.get_id());
  
  db.remove_files(ids_to_delete, founded_files);
 
  //create new files
  // Note file__4 has the file__1 first id
  libtocc::IntFileInfo new_file_4 = db.create_file("file__4", "/old/path");
  REQUIRE(atoi(new_file_4.get_id().c_str()) == atoi(new_file_3.get_id().c_str()));

  libtocc::IntFileInfo new_file_5 = db.create_file("file__5", "/old/path");
  REQUIRE(atoi(new_file_5.get_id().c_str()) == atoi(new_file_2.get_id().c_str()));
}
