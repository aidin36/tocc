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

#ifndef RUNTIME_EXCEPTIONS_H_INCLUDED
#define RUNTIME_EXCEPTIONS_H_INCLUDED

#include <string>

#include "common/base_exception.h"

namespace libtocc
{
  class InvalidArgumentError : public BaseException
  {
  public:
    InvalidArgumentError(std::string message) throw()
    {
      this->message = message;
    }

    virtual ~InvalidArgumentError() throw()
    {
    }

    virtual const char* what() const throw()
    {
      return this->message.c_str();
    }

  private:
    std::string message;
  };

}


#endif /* RUNTIME_EXCEPTIONS_H_INCLUDED */
