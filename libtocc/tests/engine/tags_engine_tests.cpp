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
#include <vector>
#include <string>

#include "database/database.h"
#include "engine/tags_engine.h"

bool tags_engine_tests()
{
  try
  {
    libtocc::Database db("/tmp/tocc.test.db");
    libtocc::TagsEngine tags_engine(&db);

    std::cout << "Assigning some tags..." << std::endl;
    std::vector<std::string> new_tags;
    new_tags.push_back("author: Mr.Pen");
    new_tags.push_back("type: PDF");
    tags_engine.assign_tags("0000001", new_tags);
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

