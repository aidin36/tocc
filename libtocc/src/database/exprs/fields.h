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

#ifndef LIBTOCC_FIELD_H_INCLUDED
#define LIBTOCC_FIELD_H_INCLUDED

#include "database/exprs/expr.h"
#include "database/exprs/operands.h"

namespace libtocc
{

  /*
   * Base class of expressions that represents a field.
   */
  class FieldExpr : public Expr
  {
  public:
    virtual expr_type::ExprType get_type();
  };

  /*
   * Repersents a Tag.
   */
  class Tag : public FieldExpr
  {
  public:
    /*
     * Represents a tag that exactly matches the
     * specified string.
     */
    Tag(const char* tag_name);

    /*
     * Represetns a tag that matches with the specified
     * expression.
     *
     * Example of usage:
     *   Tag(Regex("..."))
     */
    Tag(OperandExpr expression);
  };

};

#endif /* LIBTOCC_FIELD_H_INCLUDED */
