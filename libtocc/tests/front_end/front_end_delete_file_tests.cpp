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
#include <fstream>
#include <cstring>

#include "libtocc/front_end/manager.h"
#include "libtocc/front_end/file_info.h"
#include "libtocc/common/database_exceptions.h"


TEST_CASE("front_end: delete file")
{
  // Creating a file to import.
  std::ofstream file_stream1;
  file_stream1.open("/tmp/tocctests/tocc_test_file_to_delete_1");
  file_stream1 << "data...";
  file_stream1.close();

  // Creating a file to import.
  std::ofstream file_stream2;
  file_stream2.open("/tmp/tocctests/tocc_test_file_to_delete_2");
  file_stream2 << "data...";
  file_stream2.close();

  //Creating files for collection
  std::ofstream file_stream3;
  file_stream3.open("/tmp/tocctests/tocc_test_file_to_delete_3");
  file_stream3 << "data...";
  file_stream3.close();

  std::ofstream file_stream4;
  file_stream4.open("/tmp/tocctests/tocc_test_file_to_delete_4");
  file_stream4 << "data...";
  file_stream4.close();

  std::ofstream file_stream5;
  file_stream5.open("/tmp/tocctests/tocc_test_file_to_delete_5");
  file_stream5 << "data...";
  file_stream5.close();

  //Creating files for array's ids
  std::ofstream file_stream6;
  file_stream6.open("/tmp/tocctests/tocc_test_file_to_delete_6");
  file_stream6 << "data...";
  file_stream6.close();

  std::ofstream file_stream7;
  file_stream7.open("/tmp/tocctests/tocc_test_file_to_delete_7");
  file_stream7 << "data...";
  file_stream7.close();

  std::ofstream file_stream8;
  file_stream8.open("/tmp/tocctests/tocc_test_file_to_delete_8");
  file_stream8 << "data...";
  file_stream8.close();

  // Creating an instance of the manager.
  libtocc::Manager manager("/tmp/tocctests/");

  // Importing the file
  libtocc::FileInfo test_file1 =
      manager.import_file("/tmp/tocctests/tocc_test_file_to_delete_1");

  libtocc::FileInfo test_file2 =
      manager.import_file("/tmp/tocctests/tocc_test_file_to_delete_2");

  std::string file_id = std::string(test_file1.get_id());

  //FileInfoCollection
  libtocc::FileInfo test_file3 =
      manager.import_file("/tmp/tocctests/tocc_test_file_to_delete_3");

  libtocc::FileInfo test_file4 =
      manager.import_file("/tmp/tocctests/tocc_test_file_to_delete_4");

  libtocc::FileInfo test_file5 =
      manager.import_file("/tmp/tocctests/tocc_test_file_to_delete_5");

  libtocc::FileInfo test_file_infos[] = { test_file3, test_file4 };

  libtocc::FileInfoCollection test_file_info_collection(test_file_infos, 2);

  //File ids array
  libtocc::FileInfo test_file6 =
      manager.import_file("/tmp/tocctests/tocc_test_file_to_delete_6");

  libtocc::FileInfo test_file7 =
      manager.import_file("/tmp/tocctests/tocc_test_file_to_delete_7");

  libtocc::FileInfo test_file8 =
      manager.import_file("/tmp/tocctests/tocc_test_file_to_delete_8");

  std::string file_id6 = std::string(test_file6.get_id());
  std::string file_id7 = std::string(test_file7.get_id());
  const char* file_ids[] = { file_id6.c_str(), file_id7.c_str() };

  //Remove a file by its id
  manager.remove_file(file_id.c_str());

  //Remove a file by FileInfo
  manager.remove_file(test_file2);

  //Remove FileInfoCollection
  manager.remove_files(test_file_info_collection);

  //Remove file ids array
  manager.remove_files(file_ids, 2);

  //Deleting a file that doesn't exist
  REQUIRE_THROWS_AS(
      manager.remove_file(file_id.c_str()),
      libtocc::DatabaseScriptLogicalError);

  REQUIRE_THROWS_AS(
      manager.remove_file(test_file2),
      libtocc::DatabaseScriptLogicalError);

  REQUIRE_THROWS_AS(
      manager.remove_file(test_file3),
      libtocc::DatabaseScriptLogicalError);

  REQUIRE_THROWS_AS(
      manager.remove_file(test_file4),
      libtocc::DatabaseScriptLogicalError);

  REQUIRE_THROWS_AS(
      manager.remove_file(test_file6),
      libtocc::DatabaseScriptLogicalError);

  REQUIRE_THROWS_AS(
      manager.remove_file(test_file7),
      libtocc::DatabaseScriptLogicalError);

  //file ids array with an already removed file and the other not yet removed
  //Notice file_test6 has been removed, test_file8 is not yet removed
  const char* file_ids2[] = { test_file6.get_id(), test_file8.get_id() };

  manager.remove_files(file_ids2, 2);

  //The once not yet removed file is now removed
  REQUIRE_THROWS_AS(
      manager.remove_file(test_file8),
      libtocc::DatabaseScriptLogicalError);

  //Collection with already removed files, not yet removed files mixed up
  //Notice : test_file3 has been removed, test_file5 is not yet removed
  libtocc::FileInfo test_file_infos2[] = { test_file3, test_file5 };

  libtocc::FileInfoCollection test_file_info_collection2(test_file_infos2, 2);

  manager.remove_files(test_file_info_collection2);

  //The once not yet removed file is now removed
  REQUIRE_THROWS_AS(
      manager.remove_file(test_file5),
      libtocc::DatabaseScriptLogicalError);
}

