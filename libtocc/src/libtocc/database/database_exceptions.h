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

#ifndef LIBTOCC_DATABASE_EXCEPTIONS_H_INCLUDED
#define LIBTOCC_DATABASE_EXCEPTIONS_H_INCLUDED

/*
 * Defines exceptions related to database layer.
 */


#include "libtocc/common/base_exception.h"

namespace libtocc
{
  /*
   * Base class of all the errors related to database layer.
   */
  class BaseDatabaseException : public BaseException
  {
  public:
    BaseDatabaseException(const char* message) throw();

    BaseDatabaseException(const BaseDatabaseException& source) throw();

    BaseDatabaseException& operator=(const BaseDatabaseException& source) throw();

    virtual ~BaseDatabaseException() throw();

    virtual const char* what() const throw();

  private:
    char* message;
  };

  /*
   * Raises when any error occur during the initialization of the database.
   */
  class DatabaseInitializationError : public BaseDatabaseException
  {
  public:
    DatabaseInitializationError(const char* message) throw();

    DatabaseInitializationError(const DatabaseInitializationError& source) throw();
  };

  /*
   * Raises if any error happens during the compilation of a database script.
   */
  class DatabaseScriptCompilationError : public BaseDatabaseException
  {
  public:
    DatabaseScriptCompilationError(const char* message) throw();

    DatabaseScriptCompilationError(const DatabaseScriptCompilationError& source) throw();
  };

  /*
   * Raises if error occurs when executing a database script.
   */
  class DatabaseScriptExecutionError : public BaseDatabaseException
  {
  public:
    DatabaseScriptExecutionError(const char* message) throw();

    DatabaseScriptExecutionError(const DatabaseScriptExecutionError& source) throw();
  };

  /*
   * Raises if any logical error happened in database. i.e. a file ID
   * not found.
   */
  class DatabaseScriptLogicalError : public BaseDatabaseException
  {
  public:
    DatabaseScriptLogicalError(const char* message) throw();

    DatabaseScriptLogicalError(const DatabaseScriptLogicalError& source) throw();
  };
}

#endif /* LIBTOCC_DATABASE_EXCEPTIONS_H_INCLUDED */
