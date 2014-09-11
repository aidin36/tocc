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
#include "libtocc/exprs/operations.h"


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

TEST_CASE("query_files_tests: Not Equal tests")
{
  libtocc::Manager manager("/tmp/tocctests/");

  // Creating two test files.
  std::string test_file_1 = "/tmp/tocctests/libtocctests_Unx12Pfiedkc";
  std::string test_file_2 = "/tmp/tocctests/libtocctests_fPe98ncloEqs";

  std::ofstream file_stream;
  file_stream.open(test_file_1.c_str());
  file_stream << "Random data.";
  file_stream.close();

  std::ofstream file_stream_2;
  file_stream_2.open(test_file_2.c_str());
  file_stream_2 << "Random data.";
  file_stream_2.close();

  // Importing files.
  libtocc::FileInfo original_file_1 = manager.import_file(test_file_1.c_str(), "Random Title Unx12Pfiedkc");
  libtocc::FileInfo original_file_2 = manager.import_file(test_file_2.c_str(), "Random Title fPe98ncloEqs");

  // Assigning tags to it.
  manager.assign_tags(original_file_1.get_id(), "random aw3r445");
  manager.assign_tags(original_file_2.get_id(), "random aw3r445");
  manager.assign_tags(original_file_2.get_id(), "random cfE394a");

  // Query files. First, checking NotEqual on a Title.
  libtocc::Tag tag_expr("random aw3r445");
  libtocc::NotEqual not_equal_expr("Random Title fPe98ncloEqs");
  libtocc::Title title_expr(not_equal_expr);

  libtocc::And main_and(tag_expr);
  main_and.add(title_expr);

  libtocc::Query query(main_and);

  libtocc::FileInfoCollection founded_files = manager.search_files(query);

  // Checking collection size.
  REQUIRE(founded_files.size() == 1);
  // Checking if it's the first file.
  libtocc::FileInfoCollection::Iterator iterator(&founded_files);
  const libtocc::FileInfo* founded_file = iterator.get();
  REQUIRE(strcmp(founded_file->get_id(), original_file_1.get_id()) == 0);

  // Query files. Second, using NotEqual on a Tag.
  libtocc::NotEqual not_equal_tag_expr("random cfE394a");
  libtocc::Tag second_tag_expr(not_equal_tag_expr);

  libtocc::And second_and(tag_expr);
  second_and.add(second_tag_expr);

  libtocc::Query second_query(main_and);

  founded_files = manager.search_files(second_query);

  // Checking collection size.
  REQUIRE(founded_files.size() == 1);
  // Checking if it's the first file.
  libtocc::FileInfoCollection::Iterator second_iterator(&founded_files);
  founded_file = second_iterator.get();
  REQUIRE(strcmp(founded_file->get_id(), original_file_1.get_id()) == 0);
}
