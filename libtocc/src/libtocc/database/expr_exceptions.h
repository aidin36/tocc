/*
 * This file is part of Tocc. (see <https://tocc.aidinhut.com>)
 * Copyright (C) 2013, 2014, Aidin Gharibnavaz <tocc@aidinhut.com>
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

#ifndef LIBTOCC_EXPR_EXCEPTIONS_H_INCLUDED
#define LIBTOCC_EXPR_EXCEPTIONS_H_INCLUDED

#include "libtocc/common/base_exception.h"

namespace libtocc
{

  /*
   * Base class of all the errors related to expressions.
   */
  class BaseExprException : public BaseException
  {
  public:
    BaseExprException(const char* message) throw();

    virtual ~BaseExprException() throw();

    virtual const char* what() const throw();

  private:
    const char* message;
  };

  /*
   * Raises if any errors occur during the compilation of expressions.
   */
  class ExprCompilerError : public BaseExprException
  {
  public:
    ExprCompilerError(const char* message) throw();
  };
}

#endif /* LIBTOCC_EXPR_EXCEPTIONS_H_INCLUDED */
