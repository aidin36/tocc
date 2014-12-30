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

#include "libtocc/exprs/functions.h"
#include "libtocc/common/expr_exceptions.h"
#include <string>
#include <sstream>
namespace libtocc
{
  class FunctionExpr::ProtectedData
  {
  public:
    std::string arg;
  };

  FunctionExpr::FunctionExpr(const char* arg)
  {
    this->protected_data = new ProtectedData();

    this->protected_data->arg = arg;
  }

  FunctionExpr::FunctionExpr(FunctionExpr& source)
  {
    this->protected_data = new ProtectedData();

    this->protected_data->arg = source.protected_data->arg;
  }

  expr_type::ExprType FunctionExpr::get_type()
  {
    return expr_type::FUNCTION;
  }

  const char* FunctionExpr::compile(const char* second_arg)
  {
    std::string result(get_func_name());
    result += "('" + this->protected_data->arg + "', ";
    result += second_arg;
    result += ")";

    return result.c_str();
  }

  Expr* FunctionExpr::clone()
  {
    return new FunctionExpr(*this);
  }

  const char* FunctionExpr::get_func_name()
  {
    return "NotImplementedFunc";
  }

  WildCardExpr::WildCardExpr(const char* arg)
    : FunctionExpr(arg)
  {
  }

  WildCardExpr::WildCardExpr(WildCardExpr& source)
    : FunctionExpr(source)
  {
  }

  Expr* WildCardExpr::clone()
  {
    return new WildCardExpr(*this);
  }

  const char* WildCardExpr::get_func_name()
  {
    return "wild_card_compare";
  }

  RegexExpr::RegexExpr(unqlite_vm *p_uniqlite_vm, const char * const arg, const int cflags)

    : FunctionExpr(arg)
  {
    this->p_unqlite_vm = p_uniqlite_vm;
    int return_code = regcomp(&this->regex, arg, cflags);
    if (return_code != 0)
    {
       char error_buffer[400];
       size_t error_message_length = regerror(return_code, &this->regex,
         error_buffer, sizeof error_buffer);
       std::string error_message = std::string("Invalid regular expression: ") + error_buffer;
       throw ExprCompilerError(error_message.c_str());
    }
    unqlite_value *p_unqlite_value;
    return_code = unqlite_value_resource(p_unqlite_value, &regex);
    // check rc
    // Create unique regex name regex_name.
   std::ostringstream ostream;
    ostream << "regex_" << count_of_regexes_built();
    this->arg = ostream.str();
    return_code = unqlite_vm_config(p_unqlite_vm, UNQLITE_VM_CONFIG_CREATE_VAR, this->arg.c_str(), p_unqlite_value);
    // check rc
  }

  RegexExpr::RegexExpr(RegexExpr& source)
    : FunctionExpr(source)
  {
  }

  RegexExpr::~RegexExpr()
  {
    regfree(&this->regex);
  }

  Expr* RegexExpr::clone()
  {
    return new RegexExpr(*this);
  }

   static unsigned long long count_of_regexes_built()
   {
       static unsigned long long count = 0;
       count++;
       return count;
   }


  const char* RegexExpr::get_func_name()
  {
    return "regular_expresion_compare";
  }

};

