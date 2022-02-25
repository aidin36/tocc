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

#include <fstream>
#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "testdb_path.hpp"


#include "libtocc/common/int_file_info.h"
#include "libtocc/database/database.h"
#include "libtocc/engine/tags_engine.h"
#include "libtocc/engine/files_engine.h"
#include "libtocc/engine/files_engine.h"


TEST_CASE("engine: files engine tests")
{
  /*
   * Creating instance of files engine.
   */
  libtocc::Database db(testdb_path(DATABASE_FILE).c_str());
  libtocc::FileManager file_manager(testdb_path("").c_str());
  libtocc::TagsEngine tags_engine(&db);
  libtocc::FilesEngine files_engine(&db, &file_manager, &tags_engine);

  /*
   * Testing file import.
   */
  // Creating a test file to import.
  std::ofstream file_stream;
  file_stream.open(testdb_path("tocc_a_file_to_import").c_str());
  file_stream << "some data...";
  file_stream.close();

  // Copying the file.
  libtocc::IntFileInfo first_file = files_engine.import_file(testdb_path("tocc_a_file_to_import").c_str());
  // Checking if it's OK.
  REQUIRE(first_file.get_title() == "tocc_a_file_to_import");
  REQUIRE(first_file.get_traditional_path() == "");
  REQUIRE(first_file.get_tags().size() == 0);

  /*
   * Getting the same file.
   */
  libtocc::IntFileInfo fetched_first_file = files_engine.get(first_file.get_id());
  // Checking if it's OK.
  REQUIRE(fetched_first_file.get_title() == "tocc_a_file_to_import");
  REQUIRE(fetched_first_file.get_traditional_path() == "");
  REQUIRE(fetched_first_file.get_tags().size() == 0);

}
