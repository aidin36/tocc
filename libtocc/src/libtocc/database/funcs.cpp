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

}
