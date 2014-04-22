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

#include <catch.hpp>
#include <string>

#include "database/exprs/query.h"
#include "database/exprs/connectives.h"
#include "database/exprs/fields.h"
#include "database/exprs/compiler.h"

// TODO: Give generated Jx9 scripts to Unqlite, to check if their
//       syntactically correct.
TEST_CASE("database: expr tests")
{
  // Compiling a simple expression.
  libtocc::And* all_expressions = libtocc::And::create(libtocc::Tag::create("book"));
  all_expressions->add(libtocc::Tag::create("2010"));
  all_expressions->add(libtocc::Title::create("Programming"));

  libtocc::Query query_object(all_expressions);

  libtocc::QueryCompiler compiler;

  std::string compiled_expression = compiler.compile(query_object);

  // Compiling a little more complex expression.
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

}
