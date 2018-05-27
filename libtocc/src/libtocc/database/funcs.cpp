/*
 * This file is part of Tocc. (see <https://tocc.aidinhut.com>)
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

#include "libtocc/database/funcs.h"

#include <sstream>


namespace libtocc
{

  bool wild_card_compare(const char* pattern, const char* string)
  {
    // Ensuring they're filled.
    if (!pattern || !*pattern || !string || !*string)
    {
      return false;
    }

    // Looping through both strings character by character,
    // and comparing them.
    while(true)
    {
      if (!*string)
      {
        if (!*pattern)
        {
          // Pattern is also finished. So both matched.
          return true;
        }
        // We reached end of the string.
        if (*pattern == '*' and !*(pattern + 1))
        {
          // If last character of pattern was wild card, they're matched
          // successfully.
          return true;
        }

        // Not matched.
        return false;
      }
      if (!*pattern)
      {
        // Pattern is finished, but string is not.
        return false;
      }

      // Comparing next character of pattern and string.
      if (*pattern == *string)
      {
        // Two character matches. Continuing to the next character.
        pattern++;
        string++;
      }
      else
      {
        if (*pattern == '*')
        {
          // Pattern is a wild card.
          if (*(pattern + 1) && *(pattern + 1) == *string)
          {
            // Next character of pattern matches the string. So we're passing
            // the wild card.
            pattern += 2;
            string++;
          }
          else
          {
            // Wild card matched.
            string++;
          }
        }
        else // Two character doesn't match.
        {
          return false;
        }
      }
    }

    // We will never reaches here, but it makes the compiler happy. (:
    return false;
  }

  int wild_card_compare_unqlite_func(unqlite_context* context,
                                     int argc,
                                     unqlite_value** argv)
  {
    // Checking arguments.
    if (argc != 2)
    {
      // Invalid number of arguments.
      std::stringstream error_message;
      error_message << "`wild_card_compare' expected two arguments, received ";
      error_message << argc;
      unqlite_context_throw_error(context, UNQLITE_CTX_WARNING,
                                  error_message.str().c_str());
    }

    // First argument is the pattern.
    int string_length;
    const char* pattern = unqlite_value_to_string(argv[0], &string_length);
    if (string_length <= 0 || !pattern)
    {
      // Invalid argument.
      unqlite_context_throw_error(context, UNQLITE_CTX_WARNING,
          "wild_card_compare: first argument was an invalid string");
      return UNQLITE_ABORT;
    }

    // Second argument is the string.
    const char* string = unqlite_value_to_string(argv[1], &string_length);
    if (string_length <= 0 || !pattern)
    {
      // Invalid argument.
      unqlite_context_throw_error(context, UNQLITE_CTX_WARNING,
          "wild_card_compare: second argument was an invalid string");
      return UNQLITE_ABORT;
    }

    // Calling compare method.
    bool result = wild_card_compare(pattern, string);

    // Filling result of the Jx9 function.
    unqlite_result_bool(context, result);

    // Returning OK
    return UNQLITE_OK;
  }
}
