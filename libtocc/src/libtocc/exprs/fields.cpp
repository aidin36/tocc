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

#include "libtocc/exprs/fields.h"
#include "libtocc/exprs/compiled_expr.h"


namespace libtocc
{

  FieldExpr::FieldExpr(const char* value)
  {
    this->value = value;
    this->internal_type = 0;
    this->operation = NULL;
    this->function = NULL;
  }

  FieldExpr::FieldExpr(FunctionExpr& expression)
  {
    this->function = (FunctionExpr*)expression.clone();
    this->internal_type = 1;
    this->operation = NULL;
  }

  FieldExpr::FieldExpr(OperationExpr& expression)
  {
    this->operation = (OperationExpr*)expression.clone();
    this->internal_type = 2;
    this->function = NULL;
  }

  FieldExpr::FieldExpr(const FieldExpr& source)
  {
    this->value = source.value;
    this->internal_type = source.internal_type;
    if (source.operation != NULL)
    {
      this->operation = (OperationExpr*)source.operation->clone();
    }
    else
    {
      this->operation = NULL;
    }
    if (source.function != NULL)
    {
      this->function = (FunctionExpr*)source.function->clone();
    }
    else
    {
      this->function = NULL;
    }
  }

  FieldExpr::~FieldExpr()
  {
    if (this->function != NULL)
    {
      delete this->function;
      this->function = NULL;
    }
    else if (this->operation != NULL)
    {
      delete this->operation;
      this->operation = NULL;
    }
  }

  expr_type::ExprType FieldExpr::get_type()
  {
    return expr_type::FIELD;
  }

  CompiledExpr FieldExpr::compile()
  {
    if (this->internal_type == 0)
    {
      std::string compiled_value(get_field_name() + " == '" + this->value + "'");
      return CompiledExpr(get_compiled_expr_type(), compiled_value.c_str());
    }
    else if (this->internal_type == 1)
    {
      return CompiledExpr(get_compiled_expr_type(),
                          this->function->compile(get_field_name().c_str()),
                          this->function->is_negative_expr());
    }
    else
    {
      std::string compiled_value(get_field_name());
      std::string compiled_operation(this->operation->compile());
      compiled_value += compiled_operation;
      return CompiledExpr(get_compiled_expr_type(),
                          compiled_value.c_str(),
                          this->operation->is_negative_expr());
    }
  }

  Expr* FieldExpr::clone()
  {
    return new FieldExpr(*this);
  }

  std::string FieldExpr::get_field_name()
  {
    return "Have to be override!";
  }

  compiled_expr::ExprType FieldExpr::get_compiled_expr_type()
  {
    return compiled_expr::FIELD;
  }

  Tag::Tag(const char* tag)
    : FieldExpr(tag)
  {
  }

  Tag::Tag(FunctionExpr& expression)
    : FieldExpr(expression)
  {
  }

  Tag::Tag(OperationExpr& expression)
    : FieldExpr(expression)
  {
  }

  Tag::Tag(const Tag& source)
    : FieldExpr(source)
  {
  }

  Expr* Tag::clone()
  {
    return new Tag(*this);
  }

  compiled_expr::ExprType Tag::get_compiled_expr_type()
  {
    return compiled_expr::TAG;
  }

  std::string Tag::get_field_name()
  {
    return "$tag";
  }

  Title::Title(const char* tag)
    : FieldExpr(tag)
  {
  }

  Title::Title(FunctionExpr& expression)
    : FieldExpr(expression)
  {
  }

  Title::Title(OperationExpr& expression)
    : FieldExpr(expression)
  {
  }

  Title::Title(const Title& source)
    : FieldExpr(source)
  {
  }

  Expr* Title::clone()
  {
    return new Title(*this);
  }

  std::string Title::get_field_name()
  {
    return "$record.title";
  }

};
