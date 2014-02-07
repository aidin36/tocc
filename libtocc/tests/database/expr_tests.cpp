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
    // TODO: Give compiled Jx9 algorithms to Unqlite, to check if their
    //       syntactically correct.

    std::cout << "Compiling a simple expression..." << std::endl;

    libtocc::And* all_expressions = libtocc::And::create(libtocc::Tag::create("book"));
    all_expressions->add(libtocc::Tag::create("2010"));
    all_expressions->add(libtocc::Title::create("Programming"));

    libtocc::Query query_object(all_expressions);

    libtocc::QueryCompiler compiler;
  
    std::string compiled_expression = compiler.compile(query_object);

    std::cout << compiled_expression << std::endl;

    std::cout << GREEN << "    done." << DEFAULT << std::endl;

    std::cout << "Compiling a little more complex expression..." << std::endl;

    // And(Tag("photo"), And(Or(Tag("b&w"), Tag("abstract")), Or(Tag("hdr"), Tag("landscape"))))
    libtocc::And* main_and = libtocc::And::create(libtocc::Tag::create("photo"));
    libtocc::Or* first_or = libtocc::Or::create(libtocc::Tag::create("b&w"));
    first_or->add(libtocc::Tag::create("abstract"));
    libtocc::Or* second_or = libtocc::Or::create(libtocc::Tag::create("hdr"));
    second_or->add(libtocc::Tag::create("landscape"));
    libtocc::And* internal_and = libtocc::And::create(first_or);
    internal_and->add(second_or);
    main_and->add(internal_and);

    libtocc::Query complex_query_object(main_and);

    std::string complex_result = compiler.compile(complex_query_object);

    std::cout << complex_result << std::endl;

    std::cout << GREEN << "   done." << DEFAULT << std::endl;

    return true;
  }
  catch (libtocc::BaseException &error)
  {
    std::cout << RED << "    Failed." << DEFAULT << std::endl;
    std::cout << "error was: " << error.what() << std::endl;
    return false;
  }
}
