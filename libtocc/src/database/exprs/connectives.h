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

#ifndef LIBTOCC_CONNECTIVE_H_INCLUDED
#define LIBTOCC_CONNECTIVE_H_INCLUDED

#include <list>

#include "database/exprs/expr.h"
#include "database/exprs/fields.h"
#include "database/exprs/compiled_expr.h"

namespace libtocc
{

  /*
   * Base class of all connective expressions.
   */
  class ConnectiveExpr : public Expr
  {
  public:
    /*
     * Returns the type of this expression.
     */
    virtual expr_type::ExprType get_type();

    /*
     * Compiled the expression and the ones inside it.
     * And returns list of compiled expressions.
     */
    virtual std::list<CompiledExpr> compile();
  };

  /*
   * Ands expressions together.
   */
  class And : public ConnectiveExpr
  {
  public:
    /*
     * Creates new instance of the And expr.
     *
     * @param expression: an instance of one of the
     *   connective expression.
     */
    And(ConnectiveExpr expression);

    /*
     * Creates new instance of the And expr.
     *
     * @param expression: an instance of one of the
     *   field expression.
     */
    And(FieldExpr expression);

    /*
     * Creates new instance of the And expr.
     *
     * @param expressions[]: array of expressions to and
     *   together.
     * @param length: length of the arrary. If not provided
     *   or passes as zero or negative number, the method
     *   itself will determine the length.
     */
    And(ConnectiveExpr expressions[], int length/*=0*/);

    /*
     * Creates new instance of the And expr.
     *
     * @param expressions[]: array of expressions to and
     *   together.
     * @param length: length of the arrary. If not provided
     *   or passes as zero or negative number, the method
     *   itself will determine the length.
     */
    And(FieldExpr expressions[], int length/*=0*/);

    /*
     * Adds the specified expression.
     */
    void add(ConnectiveExpr expression);

    /*
     * Adds the specified expression.
     */
    void add(FieldExpr expression);

    /*
     * Compiled the expression and the ones inside it.
     * And returns list of compiled expressions.
     */
    virtual std::list<CompiledExpr> compile();

  private:
    std::list<Expr> expressions;
  };

};

#endif /* LIBTOCC_CONNECTIVE_H_INCLUDED */
