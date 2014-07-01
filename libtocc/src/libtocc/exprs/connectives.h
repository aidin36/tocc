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

#ifndef LIBTOCC_CONNECTIVE_H_INCLUDED
#define LIBTOCC_CONNECTIVE_H_INCLUDED

#include <list>

#include "libtocc/exprs/expr.h"
#include "libtocc/exprs/fields.h"

namespace libtocc
{

  // Forward declaration: This shouldn't be exposed in the public headers.
  class CompiledExpr;

  /*
   * Base class of all connective expressions.
   */
  class ConnectiveExpr : public Expr
  {
    // To allow this class to delete a pointer to ConnectiveExpr.
    friend class Query;

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
     * Compiled the expression and the ones inside it.
     * And returns list of compiled expressions.
     */
    virtual std::list<CompiledExpr> compile();

    /*
     * Clones this instance.
     */
    virtual Expr* clone() = 0;

  protected:

    /*
     * Returns the equivalent string of this connective expression.
     */
    virtual std::string get_connective_string() = 0;

    /*
     * Keeps list of expressions inside this connective expression.
     */
    std::list<Expr*> expressions;
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
    virtual std::string get_connective_string();
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
    virtual std::string get_connective_string();

  };

};

#endif /* LIBTOCC_CONNECTIVE_H_INCLUDED */
