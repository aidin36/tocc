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

#ifndef LIBTOCC_BASE_23_H_INCLUDED
#define LIBTOCC_BASE_23_H_INCLUDED

#include <string>

/*
 * Defines functions to converting from/to base 23.
 */

/*
 * Converts a base 10 number to base 23.
 * Note: num cannot be greater than 3404825447
 * Length of return string is 7.
 */
std::string to_base23(unsigned long num);

/*
 * Converts a base 23 number to base 10.
 * Note: Length of num must be 7.
 */
unsigned long from_base23(std::string num);

#endif /* LIBTOCC_BASE_23_H_INCLUDED */
