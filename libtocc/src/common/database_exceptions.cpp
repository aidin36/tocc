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

#include "common/database_exceptions.h"

namespace libtocc
{

  BaseDatabaseException::BaseDatabaseException(std::string message) throw()
  {
    this->message = message;
  }

  BaseDatabaseException::~BaseDatabaseException() throw()
  {
  }

  const char* BaseDatabaseException::what() const throw()
  {
    return this->message.c_str();
  }

  DatabaseInitializationError::DatabaseInitializationError(std::string message) throw()
    : BaseDatabaseException(message)
  {
  }

  DatabaseScriptCompilationError::DatabaseScriptCompilationError(std::string message) throw()
    : BaseDatabaseException(message)
  {
  }

  DatabaseScriptExecutionError::DatabaseScriptExecutionError(std::string message) throw()
    : BaseDatabaseException(message)
  {
  }
}
