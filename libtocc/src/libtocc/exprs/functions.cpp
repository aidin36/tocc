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
#include "libtocc/common/runtime_exceptions.h"
#include <string>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <cstring>

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
    static char buf[200];
    strncpy(buf, result.c_str(), sizeof buf);
    return buf;
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

  static pcre *string_to_regex_pointer(const char *string)
  {
    pcre *regex_pointer;
    sscanf(string, "%p", &regex_pointer);
    return regex_pointer;
  }

  static void  regex_pointer_to_string(pcre *regex_pointer, char *string, size_t string_length)
  {
    if (string_length < 25)
    {
      throw InvalidArgumentError("string less than 25 characters long passed to RegexExpr::regex_pointer_to_string");
    }
    snprintf (string, string_length, "%p", regex_pointer);
  }

  RegexExpr::RegexExpr(const char * const arg, const int cflags)
    : FunctionExpr(arg)
  {
    this->protected_data = new ProtectedData();
    const char* pcre_error_string;
    int pcre_error_offset;
    this->regex = NULL;
    this->regex = pcre_compile(arg, 0, &pcre_error_string, &pcre_error_offset, NULL);

    if (this->regex == NULL)
    {
      std::string error_message = std::string("Invalid regular expression: ") + pcre_error_string;
      throw ExprCompilerError(error_message.c_str());
    }
    char buf[30];
    regex_pointer_to_string (this->regex, buf, sizeof buf);
    this->protected_data->arg = std::string(buf);
  }


  RegexExpr::RegexExpr(RegexExpr& source)
    : FunctionExpr(source)
  {
  }

  RegexExpr::~RegexExpr()
  {
    if (this->regex != NULL)
    {
      pcre_free(this->regex);
    }
  }

  static void replace_string_in_place(std::string& subject, const std::string& search,
                          const std::string& replace) {
    size_t pos = 0;
    while((pos = subject.find(search, pos)) != std::string::npos) {
      subject.replace(pos, search.length(), replace);
      pos += replace.length();
    }
  }

  const char* RegexExpr::compile(const char* second_arg)
  {
    static char buf[300];
    std::string second_arg_s = second_arg;
    replace_string_in_place(second_arg_s, "\\", "\\\\");
    std::string out_str = get_func_name();
    out_str += "('";
    out_str += this->protected_data->arg;
    out_str += "', '";
    out_str += second_arg_s;
    out_str += "')";
    strncpy(buf, out_str.c_str(), sizeof buf);
    return buf;
  }

  Expr* RegexExpr::clone()
  {
    return new RegexExpr(*this);
  }

  const char* RegexExpr::get_func_name()
  {
    return "regular_expresion_compare";
  }

  static int regex_match(unqlite_context *pCtx, int argc, unqlite_value **argv)
  {
    int i;
    if( argc != 2 )
    {
      /*
       * Missing arguments, throw a notice and return NULL.
       * Note that you do not need to log the function name, UnQLite will
       * automatically append the function name for you.
       */
      unqlite_context_throw_error(pCtx, UNQLITE_CTX_NOTICE, "Wrong number of arguments ..");
      /* Return null */
      unqlite_result_null(pCtx);
      return UNQLITE_OK;
    }

    /* If argv[0] is not a string, throw a notice and continue */
    if( !unqlite_value_is_string(argv[0]) )
    {
      unqlite_context_throw_error(pCtx, UNQLITE_CTX_NOTICE,
        "Arg[0]: Expecting a string value");
      unqlite_result_null(pCtx);
      return UNQLITE_OK;
    }
    int string_length;
    const char* regex_address_string = unqlite_value_to_string(argv[0], &string_length);
    pcre *regex = string_to_regex_pointer(regex_address_string);

    if( !unqlite_value_is_string(argv[1]))
    {
      unqlite_context_throw_error(pCtx, UNQLITE_CTX_NOTICE,
        "argv[1]: Expecting a string value");
      unqlite_result_null(pCtx);
      return UNQLITE_OK;
    }
    const char *string_to_compare = unqlite_value_to_string(argv[1], &string_length);
    int match_result = pcre_exec(regex, 0, string_to_compare,
      strlen(string_to_compare), 0, 0, 0, 0);

    bool matched;
    if (match_result >= 0)
    {
      matched = true;
    }
    else
    {
      if (match_result ==  PCRE_ERROR_NOMATCH)
      {
        matched = false;
      }
      else
      {
        std::stringstream out_errmsg;
        out_errmsg << "Error " << match_result << " on pcre_exec in libtocc::RegexExpr::regex_match";
        RuntimeLogicError errx(out_errmsg.str().c_str());
        throw errx;
      }
    }
    unqlite_result_bool(pCtx, matched);

    return UNQLITE_OK;
  }

  void RegexExpr::create_Jx9_regex_match_function(unqlite_vm* pVm)
  {
    int rc = unqlite_create_function(pVm, get_func_name(), regex_match, 0 /* NULL: No private data */);
    if( rc != UNQLITE_OK )
    {
      std::stringstream str1;
      str1 << "Error " << rc << " creating regex_match function in Unqlite";
      RuntimeLogicError err1(str1.str().c_str());
      throw err1;
    }
  }
}
