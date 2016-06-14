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

#include "libtocc/exprs/connectives.h"

#include <list>

#include "libtocc/exprs/compiled_expr.h"


namespace libtocc
{

  class ConnectiveExpr::ProtectedData
  {
  public:
    /*
     * Keeps list of expressions inside this connective expression.
     */
    std::list<Expr*> expressions;

  };

  ConnectiveExpr::ConnectiveExpr(ConnectiveExpr& expression)
  {
    this->protected_data = new ProtectedData();

    this->protected_data->expressions.push_back(expression.clone());
  }

  ConnectiveExpr::ConnectiveExpr(FieldExpr& expression)
  {
    this->protected_data = new ProtectedData();

    this->protected_data->expressions.push_back(expression.clone());
  }

  ConnectiveExpr::ConnectiveExpr(OperationExpr& expression)
  {
    this->protected_data = new ProtectedData();

    this->protected_data->expressions.push_back(expression.clone());
  }

  ConnectiveExpr::ConnectiveExpr(const ConnectiveExpr& source)
  {
    this->protected_data = new ProtectedData();

    // Looping through the source's expression, and copying each element
    // to our private list.
    std::list<Expr*>::const_iterator iterator =
        source.protected_data->expressions.begin();
    for (; iterator != source.protected_data->expressions.end(); iterator++)
    {
      this->protected_data->expressions.push_back((*iterator)->clone());
    }
  }

  ConnectiveExpr::~ConnectiveExpr()
  {
    if (this->protected_data != NULL)
    {
      // Iterating over internal expressions, deleting each one.
      while (!this->protected_data->expressions.empty())
      {
        delete this->protected_data->expressions.back();
        this->protected_data->expressions.pop_back();
      }

      delete this->protected_data;
      this->protected_data = NULL;
    }
  }

  expr_type::ExprType ConnectiveExpr::get_type()
  {
    return expr_type::CONNECTIVE;
  }

  void ConnectiveExpr::add(ConnectiveExpr& expression)
  {
    this->protected_data->expressions.push_back(expression.clone());
  }

  void ConnectiveExpr::add(FieldExpr& expression)
  {
    this->protected_data->expressions.push_back(expression.clone());
  }

  void ConnectiveExpr::add(OperationExpr& expression)
  {
    this->protected_data->expressions.push_back(expression.clone());
  }

  CompiledExprList ConnectiveExpr::compile()
  {
    std::list<CompiledExpr> result;

    // Adding an AND to the begining of the result.
    result.push_back(CompiledExpr(compiled_expr::CONNECTIVE, get_connective_string()));

    // Iterating over internal expressions, compiling and adding them to the result.
    std::list<Expr*>::iterator iterator = this->protected_data->expressions.begin();
    for(; iterator != this->protected_data->expressions.end(); iterator++)
    {
      if ((*iterator)->get_type() == expr_type::FIELD)
      {
	// Simply, compile and append to result.
	result.push_back(((FieldExpr*)*iterator)->compile());
      }
      if ((*iterator)->get_type() == expr_type::OPERATION)
      {
        // Simply, compile and append to result.
        result.push_back(((OperationExpr*)*iterator)->compile());
      }
      else if ((*iterator)->get_type() == expr_type::CONNECTIVE)
      {
	// Compiling the internal expr.
	std::list<CompiledExpr> compile_result =
	    ((ConnectiveExpr*)*iterator)->compile().list;

	// Appending two lists together.
	// `splice' moved elements of `compile_result' to `result'. It's O(1).
	result.splice(result.end(), compile_result);
      }
    }

    // Marking the end of the `and' group.
    result.push_back(CompiledExpr(compiled_expr::END_CONNECTIVE_GROUP, ""));

    // Wrapping the result.
    CompiledExprList expr_list;
    expr_list.list = result;
    return expr_list;
  }

  const char* And::get_connective_string()
  {
    return "&&";
  }

  And::And(ConnectiveExpr& expression)
    : ConnectiveExpr(expression)
  {
  }

  And::And(FieldExpr& expression)
    : ConnectiveExpr(expression)
  {
  }

  And::And(OperationExpr& expression)
    : ConnectiveExpr(expression)
  {
  }

  And::And(const And& source)
    : ConnectiveExpr(source)
  {
  }

  Expr* And::clone()
  {
    return new And(*this);
  }

  const char* Or::get_connective_string()
  {
    return "||";
  }

  Or::Or(ConnectiveExpr& expression)
    : ConnectiveExpr(expression)
  {
  }

  Or::Or(FieldExpr& expression)
    : ConnectiveExpr(expression)
  {
  }

  Or::Or(OperationExpr& expression)
    : ConnectiveExpr(expression)
  {
  }

  Or::Or(const Or& expression)
    : ConnectiveExpr(expression)
  {
  }

  Expr* Or::clone()
  {
    return new Or(*this);
  }

};
