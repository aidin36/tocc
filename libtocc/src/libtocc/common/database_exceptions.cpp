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

#ifdef _MSC_VER
#pragma warning(disable: 4996)
#endif

#include "libtocc/common/database_exceptions.h"
#include <string.h>

namespace libtocc
{

  BaseDatabaseException::BaseDatabaseException(const char* message) throw()
  {
    /* String copy message to this->message to avoid using
     * pointer which is invalidated during stack unwind when
     * the exception is thrown.
     */
    this->message = new char[strlen(message) + 1];
    strcpy(this->message, message);
  }

  BaseDatabaseException::BaseDatabaseException(const BaseDatabaseException& source) throw()
  {
    this->message = new char[strlen(source.message) + 1];
    strcpy(this->message, source.message);
  }

  BaseDatabaseException& BaseDatabaseException::operator=(const BaseDatabaseException& source) throw()
  {
    if (this == &source)
    {
      return *this;
    }

    if (this->message != NULL)
    {
      delete[] this->message;
    }

    this->message = new char[strlen(source.message) + 1];
    strcpy(this->message, source.message);

    return *this;
  }

  BaseDatabaseException::~BaseDatabaseException() throw()
  {
    if (this->message != NULL)
    {
      delete[] this->message;
      this->message = NULL;
    }
  }

  const char* BaseDatabaseException::what() const throw()
  {
    return this->message;
  }

  DatabaseInitializationError::DatabaseInitializationError(const char* message) throw()
    : BaseDatabaseException(message)
  {
  }

  DatabaseInitializationError::DatabaseInitializationError(const DatabaseInitializationError& source) throw()
    : BaseDatabaseException(source)
  {
  }

  DatabaseScriptCompilationError::DatabaseScriptCompilationError(const char* message) throw()
    : BaseDatabaseException(message)
  {
  }

  DatabaseScriptCompilationError::DatabaseScriptCompilationError(const DatabaseScriptCompilationError& source) throw()
    : BaseDatabaseException(source)
  {
  }

  DatabaseScriptExecutionError::DatabaseScriptExecutionError(const char* message) throw()
    : BaseDatabaseException(message)
  {
  }

  DatabaseScriptExecutionError::DatabaseScriptExecutionError(const DatabaseScriptExecutionError& source) throw()
    : BaseDatabaseException(source)
  {
  }

  DatabaseScriptLogicalError::DatabaseScriptLogicalError(const char* message) throw()
    : BaseDatabaseException(message)
  {
  }

  DatabaseScriptLogicalError::DatabaseScriptLogicalError(const DatabaseScriptLogicalError& source) throw()
    : BaseDatabaseException(source)
  {
  }
}
