/*
 * This file is part of Tocc. (see <https://tocc.aidinhut.com>)
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

#include "libtocc/exprs/compiled_expr.h"


namespace libtocc
{
  class OperationExpr::ProtectedData
  {
  public:
    FieldExpr* operand;
  };

  OperationExpr::OperationExpr(FieldExpr& operand)
  {
    this->protected_data = new ProtectedData();

    this->protected_data->operand = (FieldExpr*)operand.clone();
  }

  OperationExpr::OperationExpr(const OperationExpr& source)
  {
    this->protected_data = new ProtectedData();

    this->protected_data->operand =
        (FieldExpr*)source.protected_data->operand->clone();
  }

  OperationExpr::~OperationExpr()
  {
    if (this->protected_data != NULL)
    {
      delete this->protected_data->operand;

      delete this->protected_data;
      this->protected_data = NULL;
    }
  }

  expr_type::ExprType OperationExpr::get_type()
  {
    return expr_type::OPERATION;
  }

  CompiledExpr OperationExpr::compile()
  {
    return this->protected_data->operand->compile();
  }

  Expr* OperationExpr::clone()
  {
    return new OperationExpr(*this);
  }

  Not::Not(FieldExpr& operand)
    : OperationExpr(operand)
  {
  }

  Not::Not(const Not& source)
    : OperationExpr(source)
  {
  }

  CompiledExpr Not::compile()
  {
    CompiledExpr result = this->protected_data->operand->compile();
    result.set_is_negative_expr(true);
    return result;
  }

  Expr* Not::clone()
  {
    return new Not(*this);
  }
};
