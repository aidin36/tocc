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

#ifndef TOCCCLI_STRING_UTILS_H_INCLUDED
#define TOCCCLI_STRING_UTILS_H_INCLUDED

#include <string>


namespace tocccli
{

  /*
   * Checks if `str' starts with `str_to_check'. (i.e. `str_to_check'
   * is at the beginning of `str'.)
   */
  bool string_starts_with(std::string& str, std::string& str_to_check);

}

#endif /* TOCCCLI_STRING_UTILS_H_INCLUDED */
