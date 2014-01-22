/*
 * This file is part of TOCC. (see <http://www.github.com/aidin36/tocc>)
 * Copyright (C) 2013, Aidin Gharibnavaz <tocc@aidihut.com>
 *
 * TOCC is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Foobar is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 *  along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <string>
#include <iostream>

#include "common/base_exception.h"
#include "database/exprs/query.h"
#include "database/exprs/connectives.h"
#include "database/exprs/fields.h"
#include "database/exprs/compiler.h"
#include "constants.h"

bool expr_tests()
{
  try
  {
    std::cout << "Compiling a simple expression..." << std::endl;

    libtocc::And* all_expressions = libtocc::And::create(new libtocc::Tag("book"));
    all_expressions->add(new libtocc::Tag("2010"));
    all_expressions->add(new libtocc::Title("Programming"));

    libtocc::Query query_object(all_expressions);

    libtocc::QueryCompiler compiler;
  
    std::string compiled_expression = compiler.compile(query_object);

    std::cout << compiled_expression << std::endl;

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
