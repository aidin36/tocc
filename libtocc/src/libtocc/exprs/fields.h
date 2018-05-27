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

#ifndef LIBTOCC_FIELD_H_INCLUDED
#define LIBTOCC_FIELD_H_INCLUDED

#include <string>

#include "libtocc/exprs/expr.h"
#include "libtocc/exprs/functions.h"
#include "libtocc/exprs/compiled_expr_types.h"


namespace libtocc
{

  // Forward declaration: This shouldn't be exposed in the public headers.
  class CompiledExpr;

  /*
   * Base class of expressions that represents a field.
   */
  class FieldExpr : public Expr
  {
  public:
    /*
     * Represents a field that exactly matches the
     * specified string.
     */
    FieldExpr(const char* value);

    /*
     * Represents a field that matches with the specified
     * expression.
     */
    FieldExpr(FunctionExpr& expression);

    /*
     * Copy constructor.
     */
    FieldExpr(const FieldExpr& source);

    virtual ~FieldExpr();

    /*
     * Returns the type of this expression, which is
     * expr_type::FIELD.
     */
    virtual expr_type::ExprType get_type();

    /*
     * Compiles the expression.
     */
    virtual CompiledExpr compile();

    /*
     * Clones this instance.
     */
    virtual Expr* clone();

  protected:
    class ProtectedData;
    ProtectedData* protected_data;

    /*
     * (Should be override by the subclass.)
     * Returns name of this field that should be appear in the
     * compiled string.
     */
    virtual std::string get_field_name();

    /*
     * Returns type of the compiled expression.
     */
    virtual compiled_expr::ExprType get_compiled_expr_type();
  };


  /*
   * Represents a Tag.
   */
  class Tag : public FieldExpr
  {
  public:
    /*
     * Represents a Tag that exactly matches the
     * specified string.
     */
    Tag(const char* value);

    /*
     * Represents a Tag that matches with the specified
     * expression.
     */
    Tag(FunctionExpr& expression);

    /*
     * Copy constructor.
     */
    Tag(const Tag& source);

    /*
     * Clones this instance.
     */
    virtual Expr* clone();

  protected:

    /*
     * Returns name of this field that should be appear in the
     * compiled string.
     */
    virtual std::string get_field_name();

    /*
     * Returns type of the compiled expression.
     */
    virtual compiled_expr::ExprType get_compiled_expr_type();
  };


  /*
   * Represents Title of a file.
   */
  class Title : public FieldExpr
  {
  public:
    /*
     * Represents a Title that exactly matches the
     * specified string.
     */
    Title(const char* tag);

    /*
     * Represents a Title that matches with the specified
     * expression.
     */
    Title(FunctionExpr& expression);

    /*
     * Copy constructor.
     */
    Title(const Title& source);

    /*
     * Clones this instance.
     */
    virtual Expr* clone();

  protected:

    /*
     * Returns name of this field that should be appear in the
     * compiled string.
     */
    virtual std::string get_field_name();
  };

};

#endif /* LIBTOCC_FIELD_H_INCLUDED */
