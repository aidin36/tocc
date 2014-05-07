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

#ifndef LIBTOCC_QUERY_H_INCLUDED
#define LIBTOCC_QUERY_H_INCLUDED

#include "libtocc/exprs/connectives.h"

namespace libtocc
{

  /*
   * Defines a Query object.
   * To execute a query on database, use need
   * an instance of this class.
   */
  class Query
  {
  public:
    /*
     * @param expression: Expression of this query.
     *   i.e. the expression that will be executed when
     *   this query object executes.
     */
    Query(ConnectiveExpr* expression);

    ~Query();

    /*
     * Gets the internal expression.
     */
    ConnectiveExpr* get_expr();

  private:
    ConnectiveExpr* expr;
  };
}

#endif /* LIBTOCC_QUERY_H_INCLUDED */
