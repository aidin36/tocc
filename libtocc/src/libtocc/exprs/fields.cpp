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

namespace libtocc
{

  FieldExpr::FieldExpr(const char* tag)
  {
    this->value = tag;
    this->internal_type = 0;
    this->operand = NULL;
    this->function = NULL;
  }

  FieldExpr::FieldExpr(FunctionExpr* expression)
  {
    this->function = expression;
    this->internal_type = 1;
    this->operand = NULL;
  }

  FieldExpr::FieldExpr(OperandExpr* expression)
  {
    this->operand = expression;
    this->internal_type = 2;
    this->function = NULL;
  }

  FieldExpr::~FieldExpr()
  {
    if (this->internal_type == 1)
    {
      delete this->function;
      this->function = NULL;
    }
    else if (this->internal_type == 2)
    {
      delete this->operand;
      this->operand = NULL;
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
			  this->function->compile(get_field_name()).c_str());
    }
    else
    {
      std::string result(get_field_name() + this->operand->compile());
      return CompiledExpr(get_compiled_expr_type(),
			  result.c_str());
    }
  }

  std::string FieldExpr::get_field_name()
  {
    return "Have to be overrided!";
  }

  compiled_expr::ExprType FieldExpr::get_compiled_expr_type()
  {
    return compiled_expr::FIELD;
  }

  Tag* Tag::create(const char* tag)
  {
    return new Tag(tag);
  }

  Tag* Tag::create(FunctionExpr* expression)
  {
    return new Tag(expression);
  }

  Tag* Tag::create(OperandExpr* expression)
  {
    return new Tag(expression);
  }

  Tag::Tag(const char* tag)
    : FieldExpr(tag)
  {
  }

  Tag::Tag(FunctionExpr* expression)
    : FieldExpr(expression)
  {
  }

  Tag::Tag(OperandExpr* expression)
    : FieldExpr(expression)
  {
  }

  compiled_expr::ExprType Tag::get_compiled_expr_type()
  {
    return compiled_expr::TAG;
  }

  std::string Tag::get_field_name()
  {
    return "$tag";
  }

  Title* Title::create(const char* tag)
  {
    return new Title(tag);
  }

  Title* Title::create(FunctionExpr* expression)
  {
    return new Title(expression);
  }

  Title* Title::create(OperandExpr* expression)
  {
    return new Title(expression);
  }

  Title::Title(const char* tag)
    : FieldExpr(tag)
  {
  }

  Title::Title(FunctionExpr* expression)
    : FieldExpr(expression)
  {
  }

  Title::Title(OperandExpr* expression)
    : FieldExpr(expression)
  {
  }

  std::string Title::get_field_name()
  {
    return "$record.$title";
  }

};
