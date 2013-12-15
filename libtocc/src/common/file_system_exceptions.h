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

#ifndef FILE_SYSTEM_EXCEPTIONS_H_INCLUDED
#define FILE_SYSTEM_EXCEPTIONS_H_INCLUDED

/*
 * Defines exceptions related to file system layer.
 */

#include "base_exception.h"

namespace libtocc
{

  class InsufficientSpaceError : public BaseException
  {
    virtual const char* what() const throw()
    {
      return "No space left on device.";
    }
  };

  class XAttrsAreNotSupportedError : public BaseException
  {
    virtual const char* what() const throw()
    {
      return "Extended attributes are not supported.";
    }
  };

  class AccessDeniedError : public BaseException
  {
    virtual const char* what() const throw()
    {
      //TODO: add file path to exception message.
      return "Access is denied.";
    }
  };
 
  class BadFDError : public BaseException
  {
    virtual const char* what() const throw()
    {
      //TODO: add file path to exception message.
      return "Bad file descriptor.";
    }
  };

  class BadAddressError : public BaseException
  {
    virtual const char* what() const throw()
    {
      //TODO: add file path to exception message.
      return "Bad address.";
    }
  };

  class InfinitLinkLoopError : public BaseException
  {
    virtual const char* what() const throw()
    {
      //TODO: add file path to exception message.
      return "Too many symbolic links encountered while traversing the path.";
    }
  };

  class TooLongPathError : public BaseException
  {
    virtual const char* what() const throw()
    {
      //TODO: add file path to exception message.
      return "Path is too long.";
    }
  };

  class BadPathError : public BaseException
  {
    virtual const char* what() const throw()
    {
      //TODO: add file path to exception message.
      return "A component of path does not exist, or path is an empty string.";
    }
  };

  class OutOfMemoryError : public BaseException
  {
    virtual const char* what() const throw()
    {
      return "Out of memory.";
    }
  };

  class NotADirectoryError : public BaseException
  {
    virtual const char* what() const throw()
    {
      return "A component of the path prefix of path is not a directory.";
    }
  };

  class MaxOpenFilesReachedError : public BaseException
  {
    virtual const char* what() const throw()
    {
      return "The system limit on the total number of open files has been reached.";
    }
  };

  class UnknownFileSystemError : public BaseException
  {
    virtual const char* what() const throw()
    {
      //TODO: Add errno to exception message.
      return "Unknown error.";
    }
  };

  class NoAttributeFoundError : public BaseException
  {
    virtual const char* what() const throw()
    {
      //TODO: add file path to exception message.
      return "No attribute found, or the application does not have access to it.";
    }
  };

  class SizeOfBufferIsTooSmallError : public BaseException
  {
    virtual const char* what() const throw()
    {
      //TODO: add file path to exception message.
      return "Size of the specified buffer is too small to hold the value.";
    }
  };

}

#endif /* FILE_SYSTEM_EXCEPTIONS_H_INCLUDED */
