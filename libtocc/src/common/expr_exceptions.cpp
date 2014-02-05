/*
 * This file is part of TOCC. (see <http://www.github.com/aidin36/tocc>)
 * Copyright (C) 2013, 2014, Aidin Gharibnavaz <tocc@aidinhut.com>
 *
 * TOCC is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * TOCC is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 *  along with TOCC.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "common/expr_exceptions.h"

namespace libtocc
{

BaseExprException::BaseExprException(std::string message) throw()
{
  this->message = message;
}

BaseExprException::~BaseExprException() throw()
{
}

const char* BaseExprException::what() const throw()
{
  return this->message.c_str();
}

ExprCompilerError::ExprCompilerError(std::string message) throw()
    : BaseExprException(message)
{
}

}
