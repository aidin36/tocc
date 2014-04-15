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

#ifndef TOCCCLI_CMD_PARSER_H_INCLUDED
#define TOCCCLI_CMD_PARSER_H_INCLUDED

#include <string>
#include <vector>
#include <utility>


namespace tocccli
{

  /*
   * Parses command line parameters.
   *
   * @param argc: Count of parameters.
   * @param argv: Array of parameters.
   *
   * @return: A vector of options and their values. First element of the
   *   the internal pair is the option, and second element is its value.
   */
  std::vector<std::pair<std::string, std::string> > parse_cmd(int argc, char* argv[]);

}

#endif /* TOCCCLI_CMD_PARSER_H_INCLUDED */
