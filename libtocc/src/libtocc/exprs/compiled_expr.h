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

#include "libtocc/exprs/compiled_expr_types.h"


namespace libtocc
{

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
     * Construct a compiled expression.
     *
     * @param type: type of the expression that is compiled.
     * @param value: compiled expression.
     * @param negative_expr: If set to true, it means that this expression
     *   have negative effect: e.g. if it's a condition and is correct, the
     *   final result should be false.
     */
    CompiledExpr(compiled_expr::ExprType type,
                 std::string value,
                 bool negative_expr);

    /*
     * Returns the type of the compiled expression.
     */
    compiled_expr::ExprType get_type();

    /*
     * Returns the value of the compiled expression.
     */
    std::string get_value();

    /*
     * Returns true if this is a negative expression.
     *
     * Negative expression means that this expression
     * have negative effect: e.g. if it's a condition and is correct, the
     * final result should be false.
     */
    bool is_negative_expr();

  private:
    compiled_expr::ExprType type;
    std::string value;
    bool negative_expr;
  };

};

#endif /* LIBTOCC_COMPILED_EXPR_INCLUDED */
