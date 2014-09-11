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


#ifndef LIBTOCC_OPERAND_H_INCLUDED
#define LIBTOCC_OPERAND_H_INCLUDED

#include "libtocc/exprs/expr.h"


namespace libtocc
{

  /*
   * Base class of all operand expressions.
   */
  class OperationExpr : public Expr
  {
  public:
    /*
     * @param operand: Operand of this operation.
     *   For example: NotEqual("bad-photo")
     */
    OperationExpr(const char* operand);

    /*
     * Copy constructor.
     */
    OperationExpr(const OperationExpr& source);

    virtual ~OperationExpr();

    /*
     * Gets the type of this expression.
     */
    virtual expr_type::ExprType get_type();

    /*
     * Returns true if it's a negative expression.
     *
     * Negative expression means that this expression
     * have negative effect: e.g. if it's a condition and is correct, the
     * final result should be false.
     */
    virtual bool is_negative_expr();

    /*
     * Compiles the expression into a string.
     */
    virtual const char* compile();

    /*
     * Creates a copy of the expression.
     */
    virtual Expr* clone();

  protected:
    class ProtectedData;
    ProtectedData* protected_data;
  };

  class Equal : public OperationExpr
  {
  public:
    Equal(const char* operand);

    Equal(const Equal& source);

    /*
     * Compiles the expression into a string.
     */
    virtual const char* compile();

    /*
     * Creates a copy of the expression.
     */
    virtual Expr* clone();
  };

  class NotEqual : public Equal
  {
  public:
    NotEqual(const char* operand);

    NotEqual(const NotEqual& source);

    virtual bool is_negative_expr();

    /*
     * Creates a copy of the expression.
     */
    virtual Expr* clone();
  };
};

#endif /* LIBTOCC_OPERAND_H_INCLUDED */
