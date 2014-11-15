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

#include "libtocc/exprs/compiled_expr.h"

namespace libtocc
{
  CompiledExpr::CompiledExpr(compiled_expr::ExprType type, std::string value)
  {
    this->type = type;
    this->value = value;
    this->negative_expr = false;
  }

  CompiledExpr::CompiledExpr(compiled_expr::ExprType type,
                             std::string value,
                             bool negative_expr)
  {
    this->type = type;
    this->value = value;
    this->negative_expr = negative_expr;
  }

  compiled_expr::ExprType CompiledExpr::get_type()
  {
    return this->type;
  }

  std::string CompiledExpr::get_value()
  {
    return this->value;
  }

  bool CompiledExpr::is_negative_expr()
  {
    return this->negative_expr;
  }

  void CompiledExpr::set_is_negative_expr(bool value)
  {
    this->negative_expr = value;
  }
};
