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

#ifndef LIBTOCC_CONNECTIVE_H_INCLUDED
#define LIBTOCC_CONNECTIVE_H_INCLUDED

#include "libtocc/exprs/expr.h"
#include "libtocc/exprs/fields.h"
#include "libtocc/exprs/operations.h"


namespace libtocc
{

  // Forward declaration: This shouldn't be exposed in the public headers.
  class CompiledExprList;

  /*
   * Base class of all connective expressions.
   */
  class ConnectiveExpr : public Expr
  {
  public:
    /*
     * Creates new instance of the expr.
     *
     * @param expression: First internal element of this
     *   connective expression.
     */
    ConnectiveExpr(ConnectiveExpr& expression);

    /*
     * Creates new instance of the expr.
     *
     * @param expression: First internal element of this
     *   connective expression.
     */
    ConnectiveExpr(FieldExpr& expression);

    /*
     * Creates new instance of the expr.
     *
     * @param expression: First internal element of this
     *   connective expression.
     */
    ConnectiveExpr(OperationExpr& expression);

    /*
     * Copy constructor.
     */
    ConnectiveExpr(const ConnectiveExpr& source);

    virtual ~ConnectiveExpr();

    /*
     * Returns the type of this expression.
     */
    virtual expr_type::ExprType get_type();

    /*
     * Adds the specified expression.
     */
    void add(ConnectiveExpr& expression);

    /*
     * Adds the specified expression.
     */
    void add(FieldExpr& expression);

    /*
     * Adds the specified expression.
     */
    void add(OperationExpr& expression);

    /*
     * Compiles the expression and the ones inside it.
     * And returns list of compiled expressions.
     */
    virtual CompiledExprList compile();

    /*
     * Clones this instance.
     */
    virtual Expr* clone() = 0;

  protected:
    class ProtectedData;
    ProtectedData* protected_data;

    /*
     * Returns the equivalent string of this connective expression.
     */
    virtual const char* get_connective_string() = 0;
  };

  /*
   * Ands expressions together.
   *
   * @note: Note that you cannot directly create instances of this class.
   * use `create' method instead.
   */
  class And : public ConnectiveExpr
  {
  public:
    /*
     * Creates new instance of the expr.
     *
     * @param expression: First internal element of this
     *   connective expression.
     */
    And(ConnectiveExpr& expression);

    /*
     * Creates new instance of the expr.
     *
     * @param expression: First internal element of this
     *   connective expression.
     */
    And(FieldExpr& expression);

    /*
     * Creates new instance of the expr.
     *
     * @param expression: First internal element of this
     *   connective expression.
     */
    And(OperationExpr& expression);

    /*
     * Copy constructor.
     */
    And(const And& source);

    /*
     * Clones this instance.
     */
    virtual Expr* clone();

  protected:
    /*
     * Returns the equivalent string of this connective expression.
     */
    virtual const char* get_connective_string();
  };


  /*
   * Or expressions together.
   *
   * @note: Note that you cannot directly create instances of this class.
   * use `create' method instead.
   */
  class Or : public ConnectiveExpr
  {
  public:
    /*
     * Creates new instance of the expr.
     *
     * @param expression: First internal element of this
     *   connective expression.
     */
    Or(ConnectiveExpr& expression);

    /*
     * Creates new instance of the expr.
     *
     * @param expression: First internal element of this
     *   connective expression.
     */
    Or(FieldExpr& expression);

    /*
     * Creates new instance of the expr.
     *
     * @param expression: First internal element of this
     *   connective expression.
     */
    Or(OperationExpr& expression);

    /*
     * Copy constructor.
     */
    Or(const Or& source);

    /*
     * Clones this instance.
     */
    virtual Expr* clone();

  protected:
    /*
     * Returns the equivalent string of this connective expression.
     */
    virtual const char* get_connective_string();

  };

};

#endif /* LIBTOCC_CONNECTIVE_H_INCLUDED */
