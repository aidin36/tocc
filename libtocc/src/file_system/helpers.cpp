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

/*
 * Defines some helper functions for the file system layer.
 */

#include <errno.h>

#include "common/file_system_exceptions.h"

namespace libtocc
{

  /*
   * Throws and exception according to the err_no.
   */
  void handle_errno(int err_no)
  {
    if (err_no == ENOSPC || err_no == EDQUOT)
    {
      throw InsufficientSpaceError();
    }
    if (err_no == ENOTSUP)
    {
      throw XAttrsAreNotSupportedError();
    }
    if (err_no == EACCES)
    {
      throw AccessDeniedError();
    }
    if (err_no == EBADF)
    {
      throw BadFDError();
    }
    if (err_no == EFAULT)
    {
      throw BadAddressError();
    }
    if (err_no == ELOOP)
    {
      throw InfinitLinkLoopError();
    }
    if (err_no == ENAMETOOLONG)
    {
      throw TooLongPathError();
    }
    if (err_no == ENOENT)
    {
      throw BadPathError();
    }
    if (err_no == ENOMEM)
    {
      throw OutOfMemoryError();
    }
    if (err_no == ENOTDIR)
    {
      throw NotADirectoryError();
    }
    if (err_no == ERANGE)
    {
      throw SizeOfBufferIsTooSmallError();
    }
    if (err_no == EMFILE)
    {
      throw MaxOpenFilesReachedError();
    }
    // If it was none of the above.
    throw UnknownFileSystemError();
  }

}
