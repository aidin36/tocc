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

#include "database/exprs/connectives.h"

namespace libtocc
{

  expr_type::ExprType ConnectiveExpr::get_type()
  {
    return expr_type::CONNECTIVE;
  }

  And::And(ConnectiveExpr expression)
  {
    this->expressions.push_back(expression);
  }

  And::And(FieldExpr expression)
  {
    this->expressions.push_back(expression);
  }

  And::And(ConnectiveExpr expressions[], int length=0)
  {
    if (length <= 0)
    {
      // Length is not provided. Calculating it.
      length = sizeof(expressions) / sizeof(expressions[0]);
    }
    
    // Appending the array to the private list.
    this->expressions.assign(expressions, expressions + length);
  }

  And::And(FieldExpr expressions[], int length=0)
  {
    if (length <= 0)
    {
      // Length is not provided. Calculating it.
      length = sizeof(expressions) / sizeof(expressions[0]);
    }
    
    // Appending the array to the private list.
    this->expressions.assign(expressions, expressions + length);
  }

  void And::add(ConnectiveExpr expression)
  {
    this->expressions.push_back(expression);
  }

  void And::add(FieldExpr expression)
  {
    this->expressions.push_back(expression);
  }

  std::list<CompiledExpr> And::compile()
  {
    std::list<CompiledExpr> result;

    std::list<Expr>::iterator iterator = this->expressions.begin();
    for(; iterator != this->expressions.end(); iterator++)
    {
      if (iterator->get_type() == expr_type::FIELD)
      {
	// Simply, compile and append to result.
	result.push_back(((FieldExpr*)&*iterator)->compile());
      }
      else if (iterator->get_type() == expr_type::CONNECTIVE)
      {
	// Compiling the internal expr.
	std::list<CompiledExpr> compile_result = ((ConnectiveExpr*)&*iterator)->compile();

	// Appending two lists together.
	// `splice' moved elements of `compile_result' to `result'. It's O(1).
	result.splice(result.end(), compile_result);
      }
    }

    return result;
  }

};
