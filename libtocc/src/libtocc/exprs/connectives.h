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
#include "libtocc/exprs/compiled_expr.h"

namespace libtocc
{

  /*
   * Base class of all connective expressions.
   */
  class ConnectiveExpr : public Expr
  {
    // To allow this class to delete a pointer to ConnectiveExpr.
    friend class Query;

  public:
    /*
     * Returns the type of this expression.
     */
    virtual expr_type::ExprType get_type();

    /*
     * Adds the specified expression.
     */
    void add(ConnectiveExpr* expression);

    /*
     * Adds the specified expression.
     */
    void add(FieldExpr* expression);

    /*
     * Compiled the expression and the ones inside it.
     * And returns list of compiled expressions.
     */
    virtual std::list<CompiledExpr> compile();

  protected:
    /*
     * Creates new instance of the expr.
     *
     * @param expression: an instance of one of the
     *   ConnectiveExpr or FieldExpr.
     */
    ConnectiveExpr(Expr* expression);

    virtual ~ConnectiveExpr();

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
     * Creates an instance of the And Expression. With another
     * connective expression inside it.
     *
     * @param expression: A pointer to a ConnectiveExpr.
     *
     * @return: A pointer to the newly created expression.
     *
     * @note: You cannot free the pointer you received. It
     *   will be freed as soon as its related Query object
     *   releases. (see the documentation)
     */
    static And* create(ConnectiveExpr* expression);

    /*
     * Creates an instance of the And Expression. With a
     * field expression inside it.
     *
     * @param expression: A pointer to a FieldExpr.
     *
     * @return: A pointer to the newly created expression.
     *
     * @note: You cannot free the pointer you received. It
     *   will be freed as soon as its related Query object
     *   releases. (see the documentation)
     */
    static And* create(FieldExpr* expression);

  protected:
    /*
     * Returns the equivalent string of this connective expression.
     */
    virtual std::string get_connective_string();

  private:
    /*
     * Creates new instance of the And expr.
     *
     * @param expression: an instance of one of the
     *   ConnectiveExpr or FieldExpr.
     */
    And(Expr* expression);

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
     * Creates an instance of the Or Expression. With another
     * connective expression inside it.
     *
     * @param expression: A pointer to a ConnectiveExpr.
     *
     * @return: A pointer to the newly created expression.
     *
     * @note: You cannot free the pointer you received. It
     *   will be freed as soon as its related Query object
     *   releases. (see the documentation)
     */
    static Or* create(ConnectiveExpr* expression);

    /*
     * Creates an instance of the And Expression. With a
     * field expression inside it.
     *
     * @param expression: A pointer to a FieldExpr.
     *
     * @return: A pointer to the newly created expression.
     *
     * @note: You cannot free the pointer you received. It
     *   will be freed as soon as its related Query object
     *   releases. (see the documentation)
     */
    static Or* create(FieldExpr* expression);

  protected:
    /*
     * Returns the equivalent string of this connective expression.
     */
    virtual std::string get_connective_string();

  private:
    /*
     * Creates new instance of the Or expr.
     *
     * @param expression: an instance of one of the
     *   ConnectiveExpr or FieldExpr.
     */
    Or(Expr* expression);

  };

};

#endif /* LIBTOCC_CONNECTIVE_H_INCLUDED */
