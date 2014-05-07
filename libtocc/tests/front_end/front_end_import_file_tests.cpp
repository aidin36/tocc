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


TEST_CASE("front_end: file import")
{
  // Creating a file to import.
  std::ofstream file_stream;
  file_stream.open("/tmp/tocc_test_file_to_import_2");
  file_stream << "some data...";
  file_stream.close();

  // Creating an instance of the manager.
  libtocc::Manager manager("/tmp/");

  // Importing the file with no property.
  libtocc::FileInfo test_file =
      manager.import_file("/tmp/tocc_test_file_to_import_2");
  // Checking if it's OK.
  REQUIRE(strcmp(test_file.get_title(), "") == 0);
  REQUIRE(strcmp(test_file.get_traditional_path(), "") == 0);
  REQUIRE(test_file.get_tags().size() == 0);

  // Importing the file with Title and Traditional Path.
  libtocc::FileInfo test_file_2 =
      manager.import_file("/tmp/tocc_test_file_to_import_2",
                          "Title of the test file",
                          "/home/not_well_organized/test");
  // Checking if it's OK.
  REQUIRE(strcmp(test_file_2.get_title(), "Title of the test file") == 0);
  REQUIRE(strcmp(test_file_2.get_traditional_path(), "/home/not_well_organized/test") == 0);
  REQUIRE(test_file_2.get_tags().size() == 0);

  // Importing the file with some tags.
  libtocc::TagsCollection tags;
  tags.add_tag("test");
  tags.add_tag("safe-to-remove");
  libtocc::FileInfo test_file_3 =
      manager.import_file("/tmp/tocc_test_file_to_import_2",
                          "Third import",
                          "/home/not_well_organized/test3",
                          &tags);

  // Checking if it's OK.
  REQUIRE(strcmp(test_file_3.get_title(), "Third import") == 0);
  REQUIRE(strcmp(test_file_3.get_traditional_path(), "/home/not_well_organized/test3") == 0);

  libtocc::TagsCollection file_tags = test_file_3.get_tags();

  REQUIRE(file_tags.size() == 2);

  libtocc::TagsCollection::Iterator iterator(&file_tags);
  REQUIRE(strcmp(iterator.get(), "test") == 0);
  iterator.next();
  REQUIRE(strcmp(iterator.get(), "safe-to-remove") == 0);

  // Getting first file.
  libtocc::FileInfo fetched_test_file = manager.get_file_info(test_file.get_id());
  // Checking if it's OK.
  REQUIRE(strcmp(fetched_test_file.get_title(), "") == 0);
  REQUIRE(strcmp(fetched_test_file.get_traditional_path(), "") == 0);
  REQUIRE(fetched_test_file.get_tags().size() == 0);

  // Getting second file.
  libtocc::FileInfo fetched_test_file_2 = manager.get_file_info(test_file_2.get_id());
  // Checking if it's OK.
  REQUIRE(strcmp(fetched_test_file_2.get_title(), "Title of the test file") == 0);
  REQUIRE(strcmp(fetched_test_file_2.get_traditional_path(), "/home/not_well_organized/test") == 0);
  REQUIRE(fetched_test_file_2.get_tags().size() == 0);

  // Getting third file.
  libtocc::FileInfo fetched_test_file_3 = manager.get_file_info(test_file_3.get_id());
  // Checking if it's OK.
  REQUIRE(strcmp(fetched_test_file_3.get_title(), "Third import") == 0);
  REQUIRE(strcmp(fetched_test_file_3.get_traditional_path(), "/home/not_well_organized/test3") == 0);

  libtocc::TagsCollection fetched_file_tags = fetched_test_file_3.get_tags();

  REQUIRE(fetched_file_tags.size() == 2);

  libtocc::TagsCollection::Iterator tags_iterator(&fetched_file_tags);
  REQUIRE(strcmp(tags_iterator.get(), "test") == 0);
  tags_iterator.next();
  REQUIRE(strcmp(tags_iterator.get(), "safe-to-remove") == 0);

}
