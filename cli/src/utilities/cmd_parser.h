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

#ifndef TOCCCLI_CMD_PARSER_H_INCLUDED
#define TOCCCLI_CMD_PARSER_H_INCLUDED

#include <vector>

#include "common/cmd_param.h"


namespace tocccli
{

  /*
   * Parses command line parameters.
   *
   * @param argc: Count of parameters.
   * @param argv: Array of parameters.
   *
   * @return: A vector of command line parameters.
   */
  std::vector<CmdParam> parse_cmd(int argc, char* argv[]);

}

#endif /* TOCCCLI_CMD_PARSER_H_INCLUDED */
