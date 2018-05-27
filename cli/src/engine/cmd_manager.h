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

#ifndef TOCCCLI_CMD_MANAGER_H_INCLUDED
#define TOCCCLI_CMD_MANAGER_H_INCLUDED

#include <string>
#include <vector>

#include <libtocc/front_end/manager.h>

#include "common/cmd_param.h"
#include "actions/action.h"
#include "selectors/selector.h"

namespace tocccli
{

  /*
   * Manages command line.
   */
  class CmdManager
  {
  public:
    /*
     * @param base_path: Absolute path to where Tocc files are stored.
     */
    CmdManager(std::string base_path);

    ~CmdManager();

    /*
     * Parses command line arguments and executes the required actions.
     *
     * @param cmd_parameters: A vector of parameters passed to command line.
     */
    void execute(std::vector<CmdParam> cmd_parameters);

  private:
    libtocc::Manager* libtocc_manager;
    std::vector<Action*> actions;
    std::vector<Selector*> selectors;

    /*
     * Prints usage information on stdout.
     */
    void print_usage();

    /*
     * Prints version information on stdout.
     */
    void print_version();
  };

}

#endif /* TOCCCLI_CMD_MANAGER_H_INCLUDED */
