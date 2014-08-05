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

#include <vector>
#include <string>
#include <algorithm>

#include <catch.hpp>

#include "libtocc/common/int_file_info.h"
#include "libtocc/database/database.h"

TEST_CASE("database: tag operation tests")
{
  libtocc::Database db("/tmp/tocc.test.db");

  SECTION("Assigning a single tag")
  {
    // Assigning a single tag.
    db.assign_tag("0000001", "unique_book");

    // Checking if it's OK.
    libtocc::IntFileInfo file_info = db.get("0000001");
    REQUIRE(file_info.get_tags().size() >= 1);

    std::vector<std::string> file_tags = file_info.get_tags();
    REQUIRE(std::find(file_tags.begin(), file_tags.end(), "unique_book") != file_tags.end());


  //Unassign a tag from a file
  std::string file_id("0000001");
  std::string tag("unique_book");
  db.unassign_tag(file_id, tag);

  file_info = db.get("0000001");
  file_tags = file_info.get_tags();

  REQUIRE(std::find(file_tags.begin(), file_tags.end(), "unique_book") == file_tags.end());

  //Assign many tags to a file
  std::vector<std::string> tags;
  tags.push_back("programming_book");
  tags.push_back("language_C");
  tags.push_back("linux");

  db.assign_tag("0000001", tags);
  
  file_info = db.get("0000001");
  file_tags = file_info.get_tags();

  REQUIRE(std::find(file_tags.begin(), file_tags.end(), "programming_book") != file_tags.end());
  
  REQUIRE(std::find(file_tags.begin(), file_tags.end(), "language_C") != file_tags.end());

  REQUIRE(std::find(file_tags.begin(), file_tags.end(), "linux") != file_tags.end());

  //Unassign tags from a file
  std::vector<std::string> tags_to_unassign;
  tags_to_unassign.push_back("programming_book");
  tags_to_unassign.push_back("linux");

  db.unassign_tags(file_id, tags_to_unassign);

  file_info = db.get("0000001");
  file_tags = file_info.get_tags();

  REQUIRE(std::find(file_tags.begin(), file_tags.end(), "linux") == file_tags.end());

  REQUIRE(std::find(file_tags.begin(), file_tags.end(), "programming_book") == file_tags.end());

  REQUIRE(std::find(file_tags.begin(), file_tags.end(), "language_C") != file_tags.end());

  //Unassign tags from files
  //Note that file 1 has already a tag "language_C"

  libtocc::IntFileInfo file_info2 = db.get("0000002");
  
  db.assign_tag("0000002", "language_C");
  
  std::vector<std::string> file_ids;
  file_ids.push_back("0000001");
  file_ids.push_back("0000002");

  tags_to_unassign.clear();
  tags_to_unassign.push_back("language_C");
  
  //Unassign tag "language_C" from both file 1 and file 2
  db.unassign_tags(file_ids, tags_to_unassign);

  //TEST
  file_info = db.get("0000001");
  file_tags = file_info.get_tags();

  file_info2 = db.get("0000002");
  std::vector<std::string> file_tags2 = file_info2.get_tags();

  REQUIRE(std::find(file_tags.begin(), file_tags.end(), "language_C") == file_tags.end());

  REQUIRE(std::find(file_tags2.begin(), file_tags2.end(), "language_C") == file_tags2.end());
  }
}

