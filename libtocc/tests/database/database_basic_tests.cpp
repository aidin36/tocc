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

#include "catch.hpp"
#include "testdb_path.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "libtocc/common/int_file_info.h"
#include "libtocc/database/database.h"

/* The database initializer test was moved to here because, under Windows,
 * it is not executed before the database basic tests if it is in a
 * different file.
*/

 // This should be run before all the other database tests, since it's
 // initialize an environment for tests.
TEST_CASE("Database_Initializer:init")
{
	std::string path = testdb_path(DATABASE_FILE);
	libtocc::Database db(path.c_str());
	db.initialize();
}


TEST_CASE("database: basic tests")
{
  // Creating the database.
  libtocc::Database db(testdb_path(DATABASE_FILE).c_str());
   // Creating a file with no property.
  libtocc::IntFileInfo new_file_1 = db.create_file();
  // Checking if it's OK.
  REQUIRE(new_file_1.get_title() == "");
  REQUIRE(new_file_1.get_traditional_path() == "");
  REQUIRE(new_file_1.get_tags().size() == 0);

  // Creating a file with title and traditional path.
  libtocc::IntFileInfo new_file_2 =
      db.create_file("Title of the second file", "/old/path");
  REQUIRE(new_file_2.get_title() == "Title of the second file");
  REQUIRE(new_file_2.get_traditional_path() == "/old/path");
  REQUIRE(new_file_2.get_tags().size() == 0);

  // Creating a file with tags.
  std::vector<std::string> tags;
  tags.push_back("photo");
  tags.push_back("abstract");
  tags.push_back("b&w");
  libtocc::IntFileInfo new_file_3 = db.create_file(tags, "First Photo");
  // Checking if it's OK.
  REQUIRE(new_file_3.get_title() == "First Photo");
  REQUIRE(new_file_3.get_traditional_path() == "");
  std::vector<std::string> file_3_tags = new_file_3.get_tags();
  REQUIRE(file_3_tags.size() == 3);
  std::vector<std::string>::iterator file_3_tags_iterator = file_3_tags.begin();
  REQUIRE((*file_3_tags_iterator) == "photo");
  ++file_3_tags_iterator;
  REQUIRE((*file_3_tags_iterator) == "abstract");
  ++file_3_tags_iterator;
  REQUIRE((*file_3_tags_iterator) == "b&w");

  // Fetching first file.
  libtocc::IntFileInfo fetched_file_1 = db.get(new_file_1.get_id());
  // Checking if it's OK.
  REQUIRE(fetched_file_1.get_title() == "");
  REQUIRE(fetched_file_1.get_traditional_path() == "");
  REQUIRE(fetched_file_1.get_tags().size() == 0);

  // Fetching second file.
  libtocc::IntFileInfo fetched_file_2 = db.get(new_file_2.get_id());
  // Checking if it's OK.
  REQUIRE(fetched_file_2.get_title() == "Title of the second file");
  REQUIRE(fetched_file_2.get_traditional_path() == "/old/path");
  REQUIRE(fetched_file_2.get_tags().size() == 0);

  // Fetching third file.
  libtocc::IntFileInfo fetched_file_3 = db.get(new_file_3.get_id());
  // Checking if it's OK.
  REQUIRE(fetched_file_3.get_title() == "First Photo");
  REQUIRE(fetched_file_3.get_traditional_path() == "");

  std::vector<std::string> fetched_tags = fetched_file_3.get_tags();
  REQUIRE(fetched_tags.size() == 3);
  std::vector<std::string>::iterator fetched_tags_iterator = fetched_tags.begin();
  REQUIRE((*fetched_tags_iterator) == "photo");
  ++fetched_tags_iterator;
  REQUIRE((*fetched_tags_iterator) == "abstract");
  ++fetched_tags_iterator;
  REQUIRE((*fetched_tags_iterator) == "b&w");
}
