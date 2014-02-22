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
#include <string>
#include <vector>

#include "constants.h"
#include "common/base_exception.h"
#include "common/int_file_info.h"
#include "database/database.h"

bool database_basic_tests()
{
  try
  {
    // TODO: After fetching each created file, check if all its properties
    // (title, tags, etc) is correct.

    std::cout << "Creating database." << std::endl;
    libtocc::Database db("/tmp/tocc.test.db");
    std::cout << GREEN << "    done." << DEFAULT << std::endl;

    std::cout << "Creating a file..." << std::endl;
    libtocc::IntFileInfo new_file_1 = db.create_file();
    std::cout << "new file: " << new_file_1 << std::endl;
    std::cout << GREEN << "    done." << DEFAULT << std::endl;

    std::cout << "Creating another file..." << std::endl;
    libtocc::IntFileInfo new_file_2 =
        db.create_file("Title of the second file", "/old/path/");
    std::cout << "new file: " << new_file_2 << std::endl;
    std::cout << GREEN << "    done." << DEFAULT << std::endl;

    std::cout << "Creating a file with tags..." << std::endl;
    std::vector<std::string> tags;
    tags.push_back("photo");
    tags.push_back("abstract");
    tags.push_back("b&w");
    libtocc::IntFileInfo new_file_3 = db.create_file(tags, "First Photo");
    std::cout << "new file: " << new_file_3 << std::endl;
    std::cout << GREEN << "    done." << DEFAULT << std::endl;

    std::cout << "Fetching first file..." << std::endl;
    libtocc::IntFileInfo file_info = db.get(new_file_1.get_id());
    std::cout << file_info << std::endl;

    std::cout << "Fetching second file..." << std::endl;
    file_info = db.get(new_file_2.get_id());
    std::cout << file_info << std::endl;

    std::cout << "Fetching third file..." << std::endl;
    file_info = db.get(new_file_3.get_id());
    std::cout << file_info << std::endl;

    return true;
  }
  catch (libtocc::BaseException &error)
  {
    std::cout << RED << "    Failed." << DEFAULT << std::endl;
    std::cout << "error was: " << error.what() << std::endl;
    return false;
  }
}
