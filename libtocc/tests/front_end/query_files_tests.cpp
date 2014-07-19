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
#include <string.h>

#include "libtocc/front_end/manager.h"
#include "libtocc/front_end/file_info.h"
#include "libtocc/exprs/query.h"
#include "libtocc/exprs/connectives.h"
#include "libtocc/exprs/fields.h"


TEST_CASE("query_files_tests: simple tag search")
{
  libtocc::Manager manager("/tmp/");

  SECTION("Assign and search 'test_tag_0xUi7'")
  {
    manager.assign_tags("0000001", "test_tag_0xUi7");

    libtocc::Tag tag_expr("test_tag_0xUi7");
    libtocc::And main_and(tag_expr);

    libtocc::Query query(main_and);

    libtocc::FileInfoCollection founded_files = manager.search_files(query);

    REQUIRE(founded_files.size() == 1);
  }

  SECTION("Search two tags")
  {
    manager.assign_tags("0000001", "test_tag_zE1jIqw");

    libtocc::Tag tag_expr("test_tag_0xUi7");
    libtocc::Tag second_tag_expr("test_tag_zE1jIqw");
    libtocc::And main_and(tag_expr);
    main_and.add(second_tag_expr);

    libtocc::Query query(main_and);

    libtocc::FileInfoCollection founded_files = manager.search_files(query);

    REQUIRE(founded_files.size() == 1);
  }

  SECTION("Or two tags")
  {
    libtocc::Tag tag_expr("test_tag_0xUi7");
    libtocc::Tag second_tag_expr("not-existed-tag:jFi92Xhd");

    libtocc::Or main_or(tag_expr);
    main_or.add(second_tag_expr);

    libtocc::Query query(main_or);

    libtocc::FileInfoCollection founded_files = manager.search_files(query);

    REQUIRE(founded_files.size() == 1);
  }

  SECTION("Query a not existed file")
  {
    libtocc::Tag tag_expr("a-not-existed-tag:anFhdu89");
    libtocc::And main_and(tag_expr);

    libtocc::Query query(main_and);

    libtocc::FileInfoCollection founded_files = manager.search_files(query);

    REQUIRE(founded_files.size() == 0);
  }
}

TEST_CASE("query_files_tests: simple title search")
{
  libtocc::Manager manager("/tmp/");

  SECTION("Import and query `IMG007'")
  {
    std::ofstream file_stream;
    file_stream.open("/tmp/XlfYru129384PxQ");
    file_stream << "Not a real photo!";
    file_stream.close();

    libtocc::FileInfo original_file = manager.import_file("/tmp/XlfYru129384PxQ", "IMG007");

    libtocc::Title title_expr("IMG007");
    libtocc::And main_and(title_expr);

    libtocc::Query query(main_and);

    libtocc::FileInfoCollection founded_files = manager.search_files(query);

    // Checking collection size.
    REQUIRE(founded_files.size() == 1);

    // Checking if it's the same file.
    libtocc::FileInfoCollection::Iterator iterator(&founded_files);
    const libtocc::FileInfo* founded_file = iterator.get();
    REQUIRE(strcmp(founded_file->get_title(), "IMG007") == 0);
    REQUIRE(strcmp(founded_file->get_id(), original_file.get_id()) == 0);
  }
}

TEST_CASE("query_files_tests: long query test")
{
  libtocc::Manager manager("/tmp/");

  std::string test_file = "/tmp/iU83FpdAdjcAppfkdj";

  std::ofstream file_stream;
  file_stream.open(test_file.c_str());
  file_stream << "Empty file.";
  file_stream.close();

  // Importing the file.
  libtocc::FileInfo original_file = manager.import_file(test_file.c_str(), "Empty File No. 157895");

  // Assigning tags to it.
  manager.assign_tags(original_file.get_id(), "empty-file");
  manager.assign_tags(original_file.get_id(), "type: text");
  manager.assign_tags(original_file.get_id(), "test");
  manager.assign_tags(original_file.get_id(), "2014-07-19");

  // Querying the file again.
  libtocc::Title title_expr("Empty File No. 157895");
  libtocc::Tag tag_expr_1("empty-file");
  libtocc::Tag tag_expr_2("type: text");
  libtocc::Tag tag_expr_3("test");
  libtocc::Tag tag_expr_4("2014-07-19");

  libtocc::And main_and(title_expr);
  main_and.add(tag_expr_1);
  main_and.add(tag_expr_2);
  main_and.add(tag_expr_3);
  main_and.add(tag_expr_4);

  libtocc::Query query(main_and);

  libtocc::FileInfoCollection founded_files = manager.search_files(query);

  // Checking collection size.
  REQUIRE(founded_files.size() == 1);
  // Checking if it's the same file.
  libtocc::FileInfoCollection::Iterator iterator(&founded_files);
  const libtocc::FileInfo* founded_file = iterator.get();
  REQUIRE(strcmp(founded_file->get_title(), "Empty File No. 157895") == 0);
  REQUIRE(strcmp(founded_file->get_id(), original_file.get_id()) == 0);
}
