/*
 * This file is part of Tocc. (see <http://www.github.com/aidin36/tocc>)
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
#include <catch.hpp>

#include "common/int_file_info.h"
#include "database/database.h"
#include "engine/tags_engine.h"
#include "engine/files_engine.h"
#include "engine/files_engine.h"


TEST_CASE("engine: files engine tests")
{
  /*
   * Creating instance of files engine.
   */
  libtocc::Database db("/tmp/tocc.test.db");
  libtocc::FileManager file_manager("/tmp/");
  libtocc::TagsEngine tags_engine(&db);
  libtocc::FilesEngine files_engine(&db, &file_manager, &tags_engine);

  /*
   * Testing file copy.
   */
  // Creating a test file to copy.
  std::ofstream file_stream;
  file_stream.open("/tmp/tocc_a_file_to_copy");
  file_stream << "some data...";
  file_stream.close();

  // Copying the file.
  libtocc::IntFileInfo first_file = files_engine.copy_file("/tmp/tocc_a_file_to_copy");
  // Checking if it's OK.
  REQUIRE(first_file.get_title() == "");
  REQUIRE(first_file.get_traditional_path() == "");
  REQUIRE(first_file.get_tags().size() == 0);

  /*
   * Getting the same file.
   */
  libtocc::IntFileInfo fetched_first_file = files_engine.get(first_file.get_id());
  // Checking if it's OK.
  REQUIRE(fetched_first_file.get_title() == "");
  REQUIRE(fetched_first_file.get_traditional_path() == "");
  REQUIRE(fetched_first_file.get_tags().size() == 0);

}
