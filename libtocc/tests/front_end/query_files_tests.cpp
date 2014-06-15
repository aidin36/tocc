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

    libtocc::Tag* tag_expr = libtocc::Tag::create("test_tag_0xUi7");
    libtocc::And* main_and = libtocc::And::create(tag_expr);

    libtocc::Query query(main_and);

    libtocc::FileInfoCollection founded_files = manager.search_files(query);

    REQUIRE(founded_files.size() == 1);
  }

  SECTION("Search two tags")
  {
    manager.assign_tags("0000001", "test_tag_zE1jIqw");

    libtocc::Tag* tag_expr = libtocc::Tag::create("test_tag_0xUi7");
    libtocc::Tag* second_tag_expr = libtocc::Tag::create("test_tag_zE1jIqw");
    libtocc::And* main_and = libtocc::And::create(tag_expr);
    main_and->add(second_tag_expr);

    libtocc::Query query(main_and);

    libtocc::FileInfoCollection founded_files = manager.search_files(query);

    REQUIRE(founded_files.size() == 1);
  }

  SECTION("Or two tags")
  {
    libtocc::Tag* tag_expr = libtocc::Tag::create("test_tag_0xUi7");
    libtocc::Tag* second_tag_expr = libtocc::Tag::create("not-existed-tag:jFi92Xhd");

    libtocc::Or* main_or = libtocc::Or::create(tag_expr);
    main_or->add(second_tag_expr);

    libtocc::Query query(main_or);

    libtocc::FileInfoCollection founded_files = manager.search_files(query);

    REQUIRE(founded_files.size() == 1);
  }

  SECTION("Query a not existed file")
  {
    libtocc::Tag* tag_expr = libtocc::Tag::create("a-not-existed-tag:anFhdu89");
    libtocc::And* main_and = libtocc::And::create(tag_expr);

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

    libtocc::Title* title_expr = libtocc::Title::create("IMG007");
    libtocc::And* main_and = libtocc::And::create(title_expr);

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
