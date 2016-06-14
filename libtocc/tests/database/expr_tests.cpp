/*
 * This file is part of Tocc. (see <http://t-o-c-c.com>)
 * Copyright (C) 2013, 2014, Aidin Gharibnavaz <aidin@t-o-c-c.com>
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

#include "libtocc/exprs/query.h"
#include "libtocc/exprs/connectives.h"
#include "libtocc/exprs/fields.h"
#include "libtocc/exprs/compiler.h"

// TODO: Give generated Jx9 scripts to Unqlite, to check if their
//       syntactically correct.
TEST_CASE("database: expr tests")
{
  // Compiling a simple expression.
  libtocc::Tag book_tag("book");
  libtocc::And all_expressions(book_tag);
  libtocc::Tag year_tag("2010");
  all_expressions.add(year_tag);
  libtocc::Title title("Programming");
  all_expressions.add(title);

  libtocc::Query query_object(all_expressions);

  libtocc::QueryCompiler compiler;

  std::string compiled_expression = compiler.compile(query_object);

  // Compiling a little more complex expression.
  libtocc::Tag photo_tag("photo");
  libtocc::And main_and(photo_tag);
  libtocc::Tag bw_tag("b&w");
  libtocc::Or first_or(bw_tag);
  libtocc::Tag abstract_tag("abstract");
  first_or.add(abstract_tag);
  libtocc::Tag hdr_tag("hdr");
  libtocc::Or second_or(hdr_tag);
  libtocc::Tag landscape_tag("landscape");
  second_or.add(landscape_tag);
  libtocc::And internal_and(first_or);
  internal_and.add(second_or);
  main_and.add(internal_and);

  libtocc::Query complex_query_object(main_and);

  std::string complex_result = compiler.compile(complex_query_object);

}
