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


#include <catch.hpp>
#include "testdb_path.hpp"

#include <fstream>
#include <cstring>

#include "libtocc/front_end/manager.h"
#include "libtocc/common/database_exceptions.h"


TEST_CASE("front_end: get tests")
{
  libtocc::Manager manager(testdb_path("").c_str());

  SECTION("file not found error")
  {
    REQUIRE_THROWS_AS(
        manager.get_file_info("e31b6da"),
        libtocc::DatabaseScriptLogicalError);
  }
}

TEST_CASE("front_end: get_by_traditional_path tests")
{
  libtocc::Manager manager(testdb_path("").c_str());

  SECTION("existed file")
  {
    // Creating a file to import.
    std::ofstream file_stream;
    file_stream.open(testdb_path("axU87Ryds.txt").c_str());
    file_stream << "some data...";
    file_stream.close();

    // Importing the file.
    libtocc::FileInfo test_file =
        manager.import_file(testdb_path("axU87Ryds.txt").c_str(),
                            "axU87Ryds.txt",
                            "/old/path/of/test/file/axU87Ryds.txt");

    libtocc::FileInfo got_test_file =
        manager.get_file_by_traditional_path("/old/path/of/test/file/axU87Ryds.txt");

    REQUIRE(strcmp(got_test_file.get_id(), test_file.get_id()) == 0);
    REQUIRE(strcmp(got_test_file.get_title(), test_file.get_title()) == 0);
    REQUIRE(strcmp(got_test_file.get_traditional_path(), test_file.get_traditional_path()) == 0);
  }

  SECTION("not existed file")
  {
    REQUIRE_THROWS_AS(
        manager.get_file_by_traditional_path("/not/existed/traditional/path"),
        libtocc::DatabaseScriptLogicalError);
  }
}
