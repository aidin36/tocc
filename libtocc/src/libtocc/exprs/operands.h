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


#ifndef LIBTOCC_OPERAND_H_INCLUDED
#define LIBTOCC_OPERAND_H_INCLUDED

#include <string>
#include "libtocc/exprs/expr.h"

namespace libtocc
{

  /*
   * Base class of all operand expressions.
   */
  class OperandExpr : public Expr
  {
  public:
    virtual expr_type::ExprType get_type();

    virtual std::string compile();
  };

};

#endif /* LIBTOCC_OPERAND_H_INCLUDED */