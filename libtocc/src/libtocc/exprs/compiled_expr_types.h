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

#ifndef LIBTOCC_COMPILED_EXPR_TYPES_H_INCLUDED
#define LIBTOCC_COMPILED_EXPR_TYPES_H_INCLUDED


namespace libtocc
{

  namespace compiled_expr
  {
    /*
     * Types of compiled expressions, used by CompiledExpr class.
     */
    enum ExprType { CONNECTIVE, END_CONNECTIVE_GROUP, TAG, FIELD, NOPE };
  };

}

#endif /* LIBTOCC_COMPILED_EXPR_TYPES_H_INCLUDED */
