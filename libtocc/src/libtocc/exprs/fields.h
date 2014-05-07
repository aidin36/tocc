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

#ifndef LIBTOCC_FIELD_H_INCLUDED
#define LIBTOCC_FIELD_H_INCLUDED

#include <string>

#include "libtocc/exprs/expr.h"
#include "libtocc/exprs/operands.h"
#include "libtocc/exprs/functions.h"
#include "libtocc/exprs/compiled_expr.h"

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
     * Compiles the expression.
     */
    virtual CompiledExpr compile();

  protected:
    /*
     * this field determines which of the private fields are
     * filled:
     *   0: value is filled.
     *   1: function is filled.
     *   2: operand is filled.
     * This is here, because I can't know if function or operand
     * is filled.
     */
    int internal_type;

    std::string value;
    FunctionExpr* function;
    OperandExpr* operand;

    /*
     * Represents a field that exactly matches the
     * specified string.
     */
    FieldExpr(const char* value);

    /*
     * Represents a field that matches with the specified
     * expression.
     */
    FieldExpr(FunctionExpr* expression);

    /*
     * Represents a field that matches with the specified
     * expression.
     */
    FieldExpr(OperandExpr* expression);

    virtual ~FieldExpr();

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
     * Creates an instance of Tag expression, which matches
     * exactly with the specified string.
     *
     * @param tag: Tag to match.
     *
     * @return: A pointer to the newly created expression.
     *
     * @note: You cannot free the pointer you received. It
     *   will be freed as soon as its related Query object
     *   releases. (see the documentation)
     */
    static Tag* create(const char* tag);

    /*
     * Creates an instance of a tag that matches with the
     * specified expression.
     *
     * Example of usage:
     *   Tag(Regex("..."))
     *
     * @param expression: Expression to match.
     *
     * @return: A pointer to the newly created expression.
     *
     * @note: You cannot free the pointer you received. It
     *   will be freed as soon as its related Query object
     *   releases. (see the documentation)
     */
    static Tag* create(FunctionExpr* expression);

    /*
     * Creates an instance of a tag that matches with the
     * specified expression.
     *
     * Example of usage:
     *   Tag(Regex("..."))
     *
     * @param expression: Expression to match.
     *
     * @return: A pointer to the newly created expression.
     *
     * @note: You cannot free the pointer you received. It
     *   will be freed as soon as its related Query object
     *   releases. (see the documentation)
     */
    static Tag* create(OperandExpr* expression);

  protected:
    /*
     * Represents a Tag that exactly matches the
     * specified string.
     */
    Tag(const char* value);

    /*
     * Represents a Tag that matches with the specified
     * expression.
     */
    Tag(FunctionExpr* expression);

    /*
     * Represents a Tag that matches with the specified
     * expression.
     */
    Tag(OperandExpr* expression);

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
     * Creates an instance of a Title that exactly matches
     * the specified string.
     *
     * @param expression: Expression to match.
     *
     * @return: A pointer to the newly created expression.
     *
     * @note: You cannot free the pointer you received. It
     *   will be freed as soon as its related Query object
     *   releases. (see the documentation)
     */
    static Title* create(const char* tag);

    /*
     * Creates an instance of a Title that matches with the
     * specified expression.
     *
     * Example of usage:
     *   Title(Regex("..."))
     *
     * @param expression: Expression to match.
     *
     * @return: A pointer to the newly created expression.
     *
     * @note: You cannot free the pointer you received. It
     *   will be freed as soon as its related Query object
     *   releases. (see the documentation)
     */
    static Title* create(FunctionExpr* expression);

    /*
     * Creates an instance of a Title that matches with the
     * specified expression.
     *
     * @param expression: Expression to match.
     *
     * @return: A pointer to the newly created expression.
     *
     * @note: You cannot free the pointer you received. It
     *   will be freed as soon as its related Query object
     *   releases. (see the documentation)
     */
    static Title* create(OperandExpr* expression);

  protected:
    /*
     * Represents a Title that exactly matches the
     * specified string.
     */
    Title(const char* tag);

    /*
     * Represents a Title that matches with the specified
     * expression.
     */
    Title(FunctionExpr* expression);

    /*
     * Represents a Title that matches with the specified
     * expression.
     */
    Title(OperandExpr* expression);


    /*
     * Returns name of this field that should be appear in the
     * compiled string.
     */
    virtual std::string get_field_name();
  };

};

#endif /* LIBTOCC_FIELD_H_INCLUDED */
