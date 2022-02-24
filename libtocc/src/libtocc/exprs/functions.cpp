/*
 * This file is part of Tocc. (see <https://tocc.aidinhut.com>)
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

#include "libtocc/exprs/functions.h"

#include <string>


namespace libtocc
{
  class FunctionExpr::ProtectedData
  {
  public:
    std::string arg;
  };

  FunctionExpr::FunctionExpr(const char* arg)
  {
    this->protected_data = new ProtectedData();

    this->protected_data->arg = arg;
  }

  FunctionExpr::FunctionExpr(FunctionExpr& source)
  {
    this->protected_data = new ProtectedData();

    this->protected_data->arg = source.protected_data->arg;
  }

  expr_type::ExprType FunctionExpr::get_type()
  {
    return expr_type::FUNCTION;
  }

  const char* FunctionExpr::compile(const char* second_arg)
  {
    std::string result(get_func_name());
    result += "('" + this->protected_data->arg + "', ";
    result += second_arg;
    result += ")";

    return result.c_str();
  }

  Expr* FunctionExpr::clone()
  {
    return new FunctionExpr(*this);
  }

  const char* FunctionExpr::get_func_name()
  {
    return "NotImplementedFunc";
  }

  WildCardExpr::WildCardExpr(const char* arg)
    : FunctionExpr(arg)
  {
  }

  WildCardExpr::WildCardExpr(WildCardExpr& source)
    : FunctionExpr(source)
  {
  }

  Expr* WildCardExpr::clone()
  {
    return new WildCardExpr(*this);
  }

  const char* WildCardExpr::get_func_name()
  {
    return "wild_card_compare";
  }
};
