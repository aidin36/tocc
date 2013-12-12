/*
 * This file is part of TOCC. (see <http://www.github.com/aidin36/tocc>)
 * Copyright (C) 2013, Aidin Gharibnavaz <tocc@aidihut.com>
 *
 * TOCC is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Foobar is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 *  along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef _BASE_EXCEPTION_H_INCLUDED
#define _BASE_EXCEPTION_H_INCLUDED

#include <exception>

namespace libtocc
{
  /*
   * Base class for all exceptions in libtocc.
   */
  class BaseException : public std::exception
  {
  public:
    /*
     * If any system error happens, this field will be set
     * to the `errno'. If not, it is zero.
     */
    int errno;
  };
}

#endif /* _BASE_EXCEPTION_H_INCLUDED */
