/*
 * This file is part of Tocc. (see <http://www.github.com/aidin36/tocc>)
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

#ifndef TOCCCLI_CMD_USAGE_EXCEPTIONS_H_INCLUDED
#define TOCCCLI_CMD_USAGE_EXCEPTIONS_H_INCLUDED

#include <string>

#include "common/exceptions/base_exception.h"

namespace tocccli
{

  /*
   * Base class of all exceptions that are related to invocation of CLI command.
   */
  class CmdUsageBaseException : public BaseException
  {
  public:
    CmdUsageBaseException(std::string message) throw();

    virtual ~CmdUsageBaseException() throw();

  };

  /*
   * Throws when parameters that are passed to CLI is wrong.
   */
  class InvalidParametersError : public CmdUsageBaseException
  {
  public:
    InvalidParametersError(std::string message) throw();

    virtual ~InvalidParametersError() throw();
  };
}

#endif /* TOCCCLI_CMD_USAGE_EXCEPTIONS_H_INCLUDED */
