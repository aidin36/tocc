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

#ifndef LIBTOCC_FUNCS_H_INCLUDED
#define LIBTOCC_FUNCS_H_INCLUDED

// `unqlite.h' is a C header, thus included inside a "C" scope.
extern "C"
{
#include <unqlite.h>
}

namespace libtocc
{

  /*
   * Compares pattern and string. Pattern can contain `*' as the wild card
   * character.
   * Returns true if two matches, false otherwise.
   */
  bool wild_card_compare(const char* pattern, const char* string);

  /*
   * It's an adapter for calling `wild_card_compare' from Jx9 scripts.
   */
  int wild_card_compare_unqlite_func(unqlite_context* context,
                                     int argc,
                                     unqlite_value** argv);
}

#endif /* LIBTOCC_FUNCS_H_INCLUDED */
