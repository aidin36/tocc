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

#include <string>

#include "database/exprs/expr.h"
#include "database/exprs/operands.h"
#include "database/exprs/functions.h"
#include "database/exprs/compiled_expr.h"

namespace libtocc
{

  /*
   * Base class of expressions that represents a field.
   */
  class FieldExpr : public Expr
  {
  public:
    /*
     * Returns the type of this expression, which is
     * expr_type::FIELD.
     */
    virtual expr_type::ExprType get_type();

    /*
     * Represents a field that exactly matches the
     * specified string.
     */
    FieldExpr(const char* tag);

    /*
     * Represents a field that matches with the specified
     * expression.
     */
    FieldExpr(FunctionExpr expression);

    /*
     * Represents a field that matches with the specified
     * expression.
     */
    FieldExpr(OperandExpr expression);

    /*
     * Compiles the expression.
     */
    virtual CompiledExpr compile();

  protected:
    /*
     * this field determines which of the private fields are
     * filled:
     *   0: tag is filled.
     *   1: function is filled.
     *   2: operand is filled.
     * This is here, because I can't know if function or operand
     * is filled.
     */
    int internal_type;
    std::string tag;
    FunctionExpr function;
    OperandExpr operand;

    /*
     * (Should be overrided by the subclass.)
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
   * Repersents a Tag.
   */
  class Tag : public FieldExpr
  {
  public:
    /*
     * Represents a tag that exactly matches the
     * specified string.
     */
    Tag(const char* tag);

    /*
     * Represents a tag that matches with the specified
     * expression.
     *
     * Example of usage:
     *   Tag(Regex("..."))
     */
    Tag(FunctionExpr expression);

    /*
     * Represents a tag that matches with the specified
     * expression.
     */
    Tag(OperandExpr expression);

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
  class Title : FieldExpr
  {
  public:
    /*
     * Represents a tag that exactly matches the
     * specified string.
     */
    Title(const char* tag);

    /*
     * Represents a tag that matches with the specified
     * expression.
     *
     * Example of usage:
     *   Title(Regex("..."))
     */
    Title(FunctionExpr expression);

    /*
     * Represents a tag that matches with the specified
     * expression.
     */
    Title(OperandExpr expression);

  protected:
    /*
     * Returns name of this field that should be appear in the
     * compiled string.
     */
    virtual std::string get_field_name();
  };

};

#endif /* LIBTOCC_FIELD_H_INCLUDED */
