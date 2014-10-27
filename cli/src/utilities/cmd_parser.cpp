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


#include "utilities/cmd_parser.h"
#include "common/exceptions/cmd_usage_exceptions.h"


namespace tocccli
{

  std::vector<CmdParam> parse_cmd(int argc, char* argv[])
  {
    std::vector<CmdParam> result;

    // We started the loop from one, because zero is the name of the binary.
    for (int i = 1; i < argc; ++i)
    {
      if (argv[i][0] == '-')
      {
        // A new option.
        CmdParam new_param;
        new_param.option = argv[i];
        result.push_back(new_param);
      }
      else
      {
        if (result.empty())
        {
          throw new InvalidParametersError(
              "First parameter have to be an option (e.g. starts with a dash)");
        }

        result.back().arguments.push_back(argv[i]);
      }
    }

    return result;
  }

}
