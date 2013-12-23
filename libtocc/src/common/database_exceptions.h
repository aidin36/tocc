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

#ifndef DATABASE_EXCEPTIONS_H_INCLUDED
#define DATABASE_EXCEPTIONS_H_INCLUDED

/*
 * Defines exceptions related to database layer.
 */

#include <string>

#include "common/base_exception.h"

namespace libtocc
{
  /*
   * Base class of all the errors related to database layer.
   */
  class BaseDatabaseException : public BaseException
  {
  public:
    BaseDatabaseException(std::string message) throw();

    virtual ~BaseDatabaseException() throw();

    virtual const char* what() const throw();

  private:
    std::string message;
  };

  /*
   * Raises when any error occur during the initialization of the database.
   */
  class DatabaseInitializationError : public BaseDatabaseException
  {
  public:
    DatabaseInitializationError(std::string message) throw();
  };

  /*
   * Raises if any error happens during the compilation of a database script.
   */
  class DatabaseScriptCompilationError : public BaseDatabaseException
  {
  public:
    DatabaseScriptCompilationError(std::string message) throw();
  };

  class DatabaseScriptExecutionError : BaseDatabaseException
  {
  public:
    DatabaseScriptExecutionError(std::string message) throw();
  };
}

#endif /* DATABASE_EXCEPTIONS_H_INCLUDED */
