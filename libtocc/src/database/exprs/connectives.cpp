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

#include "database/exprs/connectives.h"

namespace libtocc
{

  expr_type::ExprType ConnectiveExpr::get_type()
  {
    return expr_type::CONNECTIVE;
  }

  void ConnectiveExpr::add(ConnectiveExpr* expression)
  {
    this->expressions.push_back(expression);
  }

  void ConnectiveExpr::add(FieldExpr* expression)
  {
    this->expressions.push_back(expression);
  }

  ConnectiveExpr::ConnectiveExpr(Expr* expression)
  {
    this->expressions.push_back(expression);
  }

  ConnectiveExpr::~ConnectiveExpr()
  {
    // Iterating over internal expressions, deleting each one.
    while (!this->expressions.empty())
    {
      this->expressions.pop_back();
    }
  }

  std::list<CompiledExpr> ConnectiveExpr::compile()
  {
    // TODO: sort the result list, and keep similar elements together.

    std::list<CompiledExpr> result;

    // Adding an AND to the begining of the result.
    result.push_back(CompiledExpr(compiled_expr::CONNECTIVE, get_connective_string()));

    // Iterating over internal expressions, compiling and adding them to the result.
    std::list<Expr*>::iterator iterator = this->expressions.begin();
    for(; iterator != this->expressions.end(); iterator++)
    {
      if ((*iterator)->get_type() == expr_type::FIELD)
      {
	// Simply, compile and append to result.
	result.push_back(((FieldExpr*)*iterator)->compile());
      }
      else if ((*iterator)->get_type() == expr_type::CONNECTIVE)
      {
	// Compiling the internal expr.
	std::list<CompiledExpr> compile_result = ((ConnectiveExpr*)*iterator)->compile();

	// Appending two lists together.
	// `splice' moved elements of `compile_result' to `result'. It's O(1).
	result.splice(result.end(), compile_result);
      }
    }

    // Marking the end of the `and' group.
    result.push_back(CompiledExpr(compiled_expr::END_CONNECTIVE_GROUP, ""));

    return result;
  }

  And* And::create(ConnectiveExpr* expression)
  {
    return new And(expression);
  }

  And* And::create(FieldExpr* expression)
  {
    return new And(expression);
  }

  std::string And::get_connective_string()
  {
    return "&&";
  }

  And::And(Expr* expression)
    : ConnectiveExpr(expression)
  {
  }

  Or* Or::create(ConnectiveExpr* expression)
  {
    return new Or(expression);
  }

  Or* Or::create(FieldExpr* expression)
  {
    return new Or(expression);
  }

  std::string Or::get_connective_string()
  {
    return "||";
  }

  Or::Or(Expr* expression)
    : ConnectiveExpr(expression)
  {
  }

};
