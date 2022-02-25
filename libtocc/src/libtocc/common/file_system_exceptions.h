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

#ifndef LIBTOCC_FILE_SYSTEM_EXCEPTIONS_H_INCLUDED
#define LIBTOCC_FILE_SYSTEM_EXCEPTIONS_H_INCLUDED

/*
 * Defines exceptions related to file system layer.
 */

#include "libtocc/common/base_exception.h"

namespace libtocc
{

  /*
   * Base class for all exceptions related to File System layer.
   */
  class BaseFileSystemException : public BaseException
  {
  public:
    BaseFileSystemException(int err_no) throw();

    ~BaseFileSystemException() throw();

    virtual const char* what() const throw();

    int get_errno();

  protected:
    /*
     * If any system error happens, this field will be set
     * to the `errno'. If not, it is zero.
     */
    int err_no;
  };

  class InsufficientSpaceError : public BaseFileSystemException
  {
  public:
    InsufficientSpaceError() throw();
  };

  class XAttrsAreNotSupportedError : public BaseFileSystemException
  {
  public:
    XAttrsAreNotSupportedError() throw();
  };

  class AccessDeniedError : public BaseFileSystemException
  {
  public:
    AccessDeniedError(const char* file_path) throw();

    ~AccessDeniedError() throw();

    virtual const char* what() const throw();

  private:
    const char* file_path;
  };

  class BadFDError : public BaseFileSystemException
  {
  public:
    BadFDError(const char* file_path) throw();

    ~BadFDError() throw();

    virtual const char* what() const throw();

  private:
    const char* file_path;
  };

  class BadAddressError : public BaseFileSystemException
  {
  public:
    BadAddressError(const char* file_path) throw();

    ~BadAddressError() throw();

    virtual const char* what() const throw();

  private:
    const char* file_path;
  };

  class InfinitLinkLoopError : public BaseFileSystemException
  {
  public:
    InfinitLinkLoopError(const char* file_path) throw();

    ~InfinitLinkLoopError() throw();

    virtual const char* what() const throw();

  private:
    const char* file_path;
  };

  class TooLongPathError : public BaseFileSystemException
  {
  public:
    TooLongPathError() throw();
  };

  class BadPathError : public BaseFileSystemException
  {
  public:
    BadPathError(const char* file_path) throw();

    ~BadPathError() throw();

    virtual const char* what() const throw();

  private:
    const char* file_path;
  };

  class OutOfMemoryError : public BaseFileSystemException
  {
  public:
    OutOfMemoryError() throw();
  };

  class NotADirectoryError : public BaseFileSystemException
  {
  public:
    NotADirectoryError() throw();
  };

  class MaxOpenFilesReachedError : public BaseFileSystemException
  {
  public:
    MaxOpenFilesReachedError() throw();
  };

  class SizeOfBufferIsTooSmallError : public BaseFileSystemException
  {
  public:
    SizeOfBufferIsTooSmallError(const char* file_path) throw();

    ~SizeOfBufferIsTooSmallError() throw();

    virtual const char* what() const throw();

  private:
    const char* file_path;
  };

  class ReadOnlyFileSystemError : public BaseFileSystemException
  {
  public:
    ReadOnlyFileSystemError() throw();
  };

  class OtherFileSystemError : public BaseFileSystemException
  {
  public:
    OtherFileSystemError(int err_no) throw();
  };

}

#endif /* LIBTOCC_FILE_SYSTEM_EXCEPTIONS_H_INCLUDED */
