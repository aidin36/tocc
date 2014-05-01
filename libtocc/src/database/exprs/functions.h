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

#ifndef LIBTOCC_FUNCTION_H_INCLUDED
#define LIBTOCC_FUNCTION_H_INCLUDED

#include <string>
#include "database/exprs/expr.h"

namespace libtocc
{

  /*
   * Defines base class of all function expressions.
   */
  class FunctionExpr : public Expr
  {
  public:
    virtual expr_type::ExprType get_type();

    /*
     * Compiled the function.
     *
     * @param base_arg: This will be used as the first argument
     *   that passes to the function.
     *   for example:
     *   compile("tag") -> "Regex("tag", "...")
     */
    virtual std::string compile(std::string base_arg);
  };

};

#endif /* LIBTOCC_FUNCTION_H_INCLUDED */
