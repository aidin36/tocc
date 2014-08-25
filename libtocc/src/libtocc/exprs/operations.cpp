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

  const char* OperationExpr::compile()
  {
    return "Not Implemented";
  }

  Expr* OperationExpr::clone()
  {
    return new OperationExpr(*this);
  }

  NotEqual::NotEqual(const char* operand)
    : OperationExpr(operand)
  {
  }

  NotEqual::NotEqual(const NotEqual& source)
    : OperationExpr(source)
  {
  }

  const char* NotEqual::compile()
  {
    std::string result(" != \"" + this->protected_data->operand + "\"");
    return result.c_str();
  }

  Expr* NotEqual::clone()
  {
    return new NotEqual(*this);
  }
};
