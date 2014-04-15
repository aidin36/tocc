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


#include "utilities/cmd_parser.h"
#include "common/exceptions/cmd_usage_exceptions.h"


namespace tocccli
{

  std::vector<std::pair<std::string, std::string> > parse_cmd(int argc, char* argv[])
  {
    std::vector<std::pair<std::string, std::string> > result;

    // We started the loop from one, because zero is the name of the binary.
    for (int i = 1; i < argc; ++i)
    {
      if (argv[i][0] == '-')
      {
        // A new option.
        result.push_back(std::make_pair(argv[i], ""));
      }
      else
      {
        if (result.empty())
        {
          throw new InvalidParametersError(
              "First parameter have to be an option (e.g. starts with a dash)");
        }

        if (result.back().second != "")
        {
          result.back().second += " ";
        }
        result.back().second += argv[i];
      }
    }

    return result;
  }

}
