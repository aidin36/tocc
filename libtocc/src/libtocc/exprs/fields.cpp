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

  class FieldExpr::ProtectedData
  {
  public:
    /*
     * this field determines which of the private fields are
     * filled:
     *   0: value is filled.
     *   1: function is filled.
     * This is here, because I can't know if function or operation
     * is filled.
     */
    int internal_type;

    std::string value;
    FunctionExpr* function;
  };

  FieldExpr::FieldExpr(const char* value)
  {
    this->protected_data = new ProtectedData;

    this->protected_data->value = value;
    this->protected_data->internal_type = 0;
    this->protected_data->function = NULL;
  }

  FieldExpr::FieldExpr(FunctionExpr& expression)
  {
    this->protected_data = new ProtectedData;

    this->protected_data->function = (FunctionExpr*)expression.clone();
    this->protected_data->internal_type = 1;
  }

  FieldExpr::FieldExpr(const FieldExpr& source)
  {
    this->protected_data = new ProtectedData;

    this->protected_data->value = source.protected_data->value;
    this->protected_data->internal_type = source.protected_data->internal_type;
    if (source.protected_data->function != NULL)
    {
      this->protected_data->function =
          (FunctionExpr*)source.protected_data->function->clone();
    }
    else
    {
      this->protected_data->function = NULL;
    }
  }

  FieldExpr::~FieldExpr()
  {
    if (this->protected_data != NULL)
    {
      if (this->protected_data->function != NULL)
      {
        delete this->protected_data->function;
        this->protected_data->function = NULL;
      }

      delete this->protected_data;
      this->protected_data = NULL;
    }
  }

  expr_type::ExprType FieldExpr::get_type()
  {
    return expr_type::FIELD;
  }

  CompiledExpr FieldExpr::compile()
  {
    if (this->protected_data->internal_type == 0)
    {
      std::string compiled_value(
          get_field_name() + " == '" + this->protected_data->value + "'");
      return CompiledExpr(get_compiled_expr_type(), compiled_value.c_str());
    }
    else if (this->protected_data->internal_type == 1)
    {
      return CompiledExpr(get_compiled_expr_type(),
                          this->protected_data->function->compile(get_field_name().c_str()));
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
