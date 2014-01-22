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

#include <cmath>
#include <cassert>

#include "base23.h"

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
  assert(num.length() == 7);

  unsigned long result = 0;
  for (short index = 6; index >= 0; index--)
  {
    result += DIGITS.find_first_of(num[index]) * pow(23, 6 - index);
  }
  
  return result;
}
