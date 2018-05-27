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

#include <errno.h>
#include <sstream>


namespace tocccli
{

  std::string translate_errno(int err_no)
  {
    if (err_no == EACCES)
    {
      return "Permission denied on the specified path.";
    }
    if (err_no == ENAMETOOLONG)
    {
      return "Path is too long.";
    }
    if (err_no == ENOENT)
    {
      return "The current working directory has been unlinked.";
    }

    std::ostringstream stream;
    stream << "Unknown error: " << err_no;
    return stream.str();
  }
}
