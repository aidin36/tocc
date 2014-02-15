/*
 * This file is part of TOCC. (see <http://www.github.com/aidin36/tocc>)
 * Copyright (C) 2013, 2014, Aidin Gharibnavaz <tocc@aidinhut.com>
 *
 * TOCC is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * TOCC is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 *  along with TOCC.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>

#include "common/int_file_info.h"
#include "database/database.h"
#include "engine/tags_engine.h"
#include "engine/files_engine.h"
#include "engine/files_engine.h"

bool files_engine_tests()
{
  try
  {
    libtocc::Database db("/tmp/tocc.test.db");
    libtocc::FileManager file_manager("/tmp/");
    libtocc::TagsEngine tags_engine(&db);
    libtocc::FilesEngine files_engine(&db, &file_manager, &tags_engine);

    // Testing file copy.
    std::cout << "Creating a test file to copy..." << std::endl;
    std::ofstream file_stream;
    file_stream.open("/tmp/tocc_a_file_to_copy");
    file_stream << "some data...";
    file_stream.close();
    std::cout << GREEN << "    done." << DEFAULT << std::endl;

    std::cout << "Copying the file..." << std::endl;
    libtocc::IntFileInfo result = files_engine.copy_file("/tmp/tocc_a_file_to_copy");
    std::cout << "file id is: " << result.get_id() << std::endl;
    std::cout << GREEN << "    done." << DEFAULT << std::endl;

    return true;
  }
  catch (libtocc::BaseException &error)
  {
    std::cout << RED << "    Failed." << DEFAULT << std::endl;
    std::cout << "error was: " << error.what() << std::endl;
    return false;
  }
}
