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

#ifndef LIBTOCC_COMPILED_EXPR_INCLUDED
#define LIBTOCC_COMPILED_EXPR_INCLUDED

#include <string>

namespace libtocc
{

  namespace compiled_expr
  {
    enum ExprType { CONNECTIVE, END_CONNECTIVE_GROUP, TAG, FIELD, NOPE };
  };

  /*
   * When the expression compiles, it returns an instance
   * of this class.
   */
  class CompiledExpr
  {
  public:
    /*
     * Construct a compiled expression.
     *
     * @param type: type of the expression that is compiled.
     * @param value: compiled expression.
     */
    CompiledExpr(compiled_expr::ExprType type, std::string value);

    /*
     * Returns the type of the compiled expression.
     */
    compiled_expr::ExprType get_type();

    /*
     * Returns the value of the compiled expression.
     */
    std::string get_value();

  private:
    compiled_expr::ExprType type;
    std::string value;
  };

};

#endif /* LIBTOCC_COMPILED_EXPR_INCLUDED */
