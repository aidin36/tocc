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

#include "testdb_path.hpp"
#include "catch.hpp"
#include <string>
#include <vector>
#include <iostream>

#include "libtocc/common/int_file_info.h"
#include "libtocc/common/database_exceptions.h"
#include "libtocc/database/database.h"


TEST_CASE("database: duplicated traditional path tests")
{
  // Creating the database.
   libtocc::Database db(testdb_path(DATABASE_FILE).c_str());
  // Creating two files without traditional path
  libtocc::IntFileInfo new_file_1 = db.create_file("Title 1");
  libtocc::IntFileInfo new_file_2 = db.create_file("Title 2");

  // Should pass
  REQUIRE(new_file_1.get_title() == "Title 1");
  REQUIRE(new_file_1.get_traditional_path() == "");

  REQUIRE(new_file_2.get_title() == "Title 2");
  REQUIRE(new_file_2.get_traditional_path() == "");

  // Creating two files with different traditional path
  libtocc::IntFileInfo new_file_3 =
    db.create_file("Title 3", "/old/path/test_file_3");
  libtocc::IntFileInfo new_file_4 =
    db.create_file("Title 4", "/old/path/test_file_4");

  // Should pass
  REQUIRE(new_file_3.get_title() == "Title 3");
  REQUIRE(new_file_3.get_traditional_path() == "/old/path/test_file_3");
  REQUIRE(new_file_4.get_title() == "Title 4");
  REQUIRE(new_file_4.get_traditional_path() == "/old/path/test_file_4");

  // Creating two files with identical traditional path
  libtocc::IntFileInfo new_file_5 =
    db.create_file("Title 5", "/old/path/test_file");

  // Should throw exception
  REQUIRE_THROWS_AS(
          db.create_file("Title 6", "/old/path/test_file"),
          libtocc::DatabaseScriptLogicalError);
}
