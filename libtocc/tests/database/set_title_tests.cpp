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

#include "libtocc/common/int_file_info.h"
#include "libtocc/database/database.h"
#include "libtocc/common/database_exceptions.h"


TEST_CASE("database: set file's title tests")
{
  // Creating the database.
  libtocc::Database db("/tmp/tocc.test.db");

  // Creating a file with title and traditional path.
  libtocc::IntFileInfo new_file = db.create_file("Title", "/old/path/");

  // Checking if it's the title's right.
  REQUIRE(new_file.get_title() == "Title");
  
  //Setting the file's title with a new title
  db.set_title(std::string(new_file.get_id()), "new title");

  //Getting the file from the database
  new_file = db.get(std::string(new_file.get_id()));

  //Checking the new file's title
  REQUIRE(new_file.get_title() == "new title");

  //Setting the file's title with the same old title
  db.set_title(std::string(new_file.get_id()), "new title");
  REQUIRE(new_file.get_title() == "new title");

  //Setting the title of an unexisting file
  REQUIRE_THROWS_AS(
    db.set_title(std::string("0000012"), "new title"),
    libtocc::DatabaseScriptLogicalError);
}
