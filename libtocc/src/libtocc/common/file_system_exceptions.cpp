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

#include <string.h> // For `strerror'.
#include <errno.h>

#include "libtocc/common/file_system_exceptions.h"

namespace libtocc
{
  BaseFileSystemException::BaseFileSystemException(int err_no) throw()
  {
    this->err_no = err_no;
  }

  BaseFileSystemException::~BaseFileSystemException() throw()
  {
  }

  const char* BaseFileSystemException::what() const throw()
  {
    return strerror(this->err_no);
  }

  int BaseFileSystemException::get_errno()
  {
    return this->err_no;
  }

  InsufficientSpaceError::InsufficientSpaceError() throw()
    : BaseFileSystemException(ENOSPC)
  {
  }

  XAttrsAreNotSupportedError::XAttrsAreNotSupportedError() throw()
    : BaseFileSystemException(ENOTSUP)
  {
  }

  AccessDeniedError::AccessDeniedError(const char* file_path) throw()
    : BaseFileSystemException(EACCES)
  {
    this->file_path = file_path;
  }

  AccessDeniedError::~AccessDeniedError() throw()
  {
  }

  const char* AccessDeniedError::what() const throw()
  {
    std::string result(strerror(this->err_no));
    result += " [";
    result += this->file_path;
    result += "]";
    return result.c_str();
  }

  BadFDError::BadFDError(const char* file_path) throw()
    : BaseFileSystemException(EBADF)
  {
    this->file_path = file_path;
  }

  BadFDError::~BadFDError() throw()
  {
  }

  const char* BadFDError::what() const throw()
  {
    std::string result(strerror(this->err_no));
    result += " [";
    result += this->file_path;
    result += "]";
    return result.c_str();
  }

  BadAddressError::BadAddressError(const char* file_path) throw()
    : BaseFileSystemException(EFAULT)
  {
    this->file_path = file_path;
  }

  BadAddressError::~BadAddressError() throw()
  {
  }

  const char* BadAddressError::what() const throw()
  {
    std::string result(strerror(this->err_no));
    result += " [";
    result += this->file_path;
    result += "]";
    return result.c_str();    
  }

  InfinitLinkLoopError::InfinitLinkLoopError(const char* file_path) throw()
    : BaseFileSystemException(ELOOP)
  {
    this->file_path = file_path;
  }

  InfinitLinkLoopError::~InfinitLinkLoopError() throw()
  {
  }

  const char* InfinitLinkLoopError::what() const throw()
  {
    std::string result(strerror(this->err_no));
    result += " [";
    result += this->file_path;
    result += "]";
    return result.c_str();
  }

  TooLongPathError::TooLongPathError() throw()
    : BaseFileSystemException(ENAMETOOLONG)
  {
  }

  BadPathError::BadPathError(const char* file_path) throw()
    : BaseFileSystemException(ENOENT)
  {
    this->file_path = file_path;
  }

  BadPathError::~BadPathError() throw()
  {
  }

  const char* BadPathError::what() const throw()
  {
    std::string result(strerror(this->err_no));
    result += " [";
    result += this->file_path;
    result += "]";
    return result.c_str();    
  }

  OutOfMemoryError::OutOfMemoryError() throw()
    : BaseFileSystemException(ENOMEM)
  {
  }

  NotADirectoryError::NotADirectoryError() throw()
    : BaseFileSystemException(ENOTDIR)
  {
  }

  MaxOpenFilesReachedError::MaxOpenFilesReachedError() throw()
    : BaseFileSystemException(EMFILE)
  {
  }

  SizeOfBufferIsTooSmallError::SizeOfBufferIsTooSmallError(const char* file_path) throw()
    : BaseFileSystemException(ERANGE)
  {
    this->file_path = file_path;
  }

  SizeOfBufferIsTooSmallError::~SizeOfBufferIsTooSmallError() throw()
  {
  }

  const char* SizeOfBufferIsTooSmallError::what() const throw()
  {
    std::string result(strerror(this->err_no));
    result += " [";
    result += this->file_path;
    result += "]";
    return result.c_str();
  }

  ReadOnlyFileSystemError::ReadOnlyFileSystemError() throw()
    : BaseFileSystemException(EROFS)
  {
  }

  OtherFileSystemError::OtherFileSystemError(int err_no) throw()
    : BaseFileSystemException(err_no)
  {
  }

};
