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


#include "libtocc/exprs/operations.h"

#include <string>


namespace libtocc
{
  class OperationExpr::ProtectedData
  {
  public:
    std::string operand;
  };

  OperationExpr::OperationExpr(const char* operand)
  {
    this->protected_data = new ProtectedData();

    this->protected_data->operand = operand;
  }

  OperationExpr::OperationExpr(const OperationExpr& source)
  {
    this->protected_data = new ProtectedData();

    this->protected_data->operand = source.protected_data->operand;
  }

  OperationExpr::~OperationExpr()
  {
    if (this->protected_data != NULL)
    {
      delete this->protected_data;
      this->protected_data = NULL;
    }
  }

  expr_type::ExprType OperationExpr::get_type()
  {
    return expr_type::OPERATION;
  }

  bool OperationExpr::is_negative_expr()
  {
    return false;
  }

  const char* OperationExpr::compile()
  {
    return "Not Implemented";
  }

  Expr* OperationExpr::clone()
  {
    return new OperationExpr(*this);
  }

  Equal::Equal(const char* operand)
    : OperationExpr(operand)
  {
  }

  Equal::Equal(const Equal& source)
    : OperationExpr(source)
  {
  }

  const char* Equal::compile()
  {
    std::string result(" == \"" + this->protected_data->operand + "\"");
    return result.c_str();
  }

  Expr* Equal::clone()
  {
    return new Equal(*this);
  }


  NotEqual::NotEqual(const char* operand)
    : Equal(operand)
  {
  }

  NotEqual::NotEqual(const NotEqual& source)
    : Equal(source)
  {
  }

  bool NotEqual::is_negative_expr()
  {
    return true;
  }

  Expr* NotEqual::clone()
  {
    return new NotEqual(*this);
  }
};
