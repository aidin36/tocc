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

#ifndef TOCCCLI_CMD_PARAM_H_INCLUDED
#define TOCCCLI_CMD_PARAM_H_INCLUDED

#include <string>
#include <vector>

namespace tocccli
{

  /*
   * Represents a command line parameter.
   */
  class CmdParam
  {
  public:

    /*
     * Command line option.
     */
    std::string option;

    /*
     * List of arguments of the option.
     * It will be an empty vector if no argument pass
     * for this option.
     */
    std::vector<std::string> arguments;
  };
}

#endif /* TOCCCLI_CMD_PARAM_H_INCLUDED */
