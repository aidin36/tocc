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

#include "libtocc/database/base23.h"

#include "libtocc/common/runtime_exceptions.h"
#include "libtocc/database/database.h"
#include "libtocc/common/file_system_exceptions.h"


#include <cmath>
#include <cassert>
#include <stdexcept>

const std::string DIGITS = "0123456789abcdefghijklmn";

std::string to_base23(unsigned long num)
{
  assert(num <= 3404825447);

  std::string result = "0000000";

  short index = 6;
  while (num > 0)
  {
    result[index] = DIGITS[num % 23];
    num = num / 23;
    index--;
  }

  return result;
}

unsigned long from_base23(std::string num)
{
  bool valid_id = true;
  if (num.length() != 7)
  {
    valid_id = false;
  }
  else 
  {
    for (int i = 0; i < 7; i++)
    {
      if (!((num[i] >= '0' && num[i] <= '9')
         || (num[i] >= 'a' && num[i] <= 'm')
         || (num[i] >= 'A' && num[i] <= 'M')))
      {
        valid_id = false;
        break;
      }
    }
  }
  if (! valid_id)
  {
    throw libtocc::InvalidArgumentError(libtocc::invalid_id_msg.c_str());
  }

  unsigned long result = 0;
  for (short index = 6; index >= 0; index--)
  {
    result += DIGITS.find_first_of(num[index]) * pow(23, 6 - index);
  }

  return result;
}
