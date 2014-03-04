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

/*
 * Defines main function, which starts all tests.
 */

#include <iostream>

#include "constants.h"
#include "file_system/basic_tests.cpp"
#include "database/basic_tests.cpp"
#include "database/expr_tests.cpp"
#include "database/tag_operation_tests.cpp"
#include "engine/tags_engine_tests.cpp"
#include "engine/files_engine_tests.cpp"
#include "front_end/front_end_basic_tests.cpp"


int main(int argc, char* argv[])
{
  std::cout << CYAN << "File Manager Basic Tests" << DEFAULT << std::endl;
  file_manager_basic_tests();

  std::cout << CYAN << "Database Basic Tests" << DEFAULT << std::endl;
  database_basic_tests();

  std::cout << CYAN << "Expr Tests" << DEFAULT << std::endl;
  expr_tests();

  std::cout << CYAN << "Tag Operation Tests" << DEFAULT << std::endl;
  tag_operation_tests();

  std::cout << CYAN << "Tags Engine Tests" << DEFAULT << std::endl;
  tags_engine_tests();

  std::cout << CYAN << "Files Engine Tests" << DEFAULT << std::endl;
  files_engine_tests();

  std::cout << CYAN << "Front End Tests" << DEFAULT << std::endl;
  front_end_basic_tests();

  return 0;
}
