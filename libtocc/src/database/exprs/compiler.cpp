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

#include <list>
#include <sstream>

#include "database/exprs/compiler.h"
#include "database/exprs/compiled_expr.h"

namespace libtocc
{

  std::string QueryCompiler::compile(Query& query_to_compile)
  {
    ConnectiveExpr* expression_to_compile = query_to_compile.get_expr();

    // Initializing the result string with the beginning of the Jx9 script.
    std::ostringstream result;
    result << "$filter_func = function($record) { ";

    std::list<CompiledExpr> compiled_list = expression_to_compile->compile();

    std::string group = "and";
    compiled_expr::ExprType previous_field = compiled_expr::FIELD;
    int result_count = 1;

    // Looping through the list and make script from each element.
    std::list<CompiledExpr>::iterator iterator = compiled_list.begin();
    for(;iterator != compiled_list.end(); iterator++)
    {
      if (iterator->get_type() == compiled_expr::CONNECTIVE)
      {
	group = iterator->get_value();
      }
      else if (iterator->get_type() == compiled_expr::END_CONNECTIVE_GROUP)
      {
      }
      else if (iterator->get_type() == compiled_expr::TAG)
      {
	if (previous_field != compiled_expr::TAG)
	{
	  // Starting a new loop over the tags.
	  result << " foreach ($record.tags as $tag) {";
	  result << " if (";
	}
	else
	{
	  result << " " << group << " ";
	}
	
	result << iterator->get_value();
      }
      else if (iterator->get_type() == compiled_expr::FIELD)
      {
	if (previous_field == compiled_expr::TAG)
	{
	  // End the loop over tags.
	  result << ") { $r" << result_count << " = True; } }";
	  result_count += 1;
	}

	result << " if (" << iterator->get_value() << ") { $r" << result_count << " = True; }";
      }

      previous_field = iterator->get_type();
    }

    // Finalizing the script.
    result << " };" << " $fetched_records = db_fetch_all('files', $filter_func);";

    return result.str();
  }

};
