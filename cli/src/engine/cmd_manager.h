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

#ifndef TOCCCLI_CMD_MANAGER_H_INCLUDED
#define TOCCCLI_CMD_MANAGER_H_INCLUDED

#include <string>
#include <list>

#include <libtocc.h>

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
     *   The first element of the internal vector is an option, and the
     *   second one is the value of that option, which is empty string
     *   if no value is passed.
     */
    void execute(std::vector<std::vector<std::string> > cmd_parameters);

  private:
    libtocc::Manager* libtocc_manager;
    std::list<Action*> actions;
    std::list<Selector*> selectors;
  };

}

#endif /* TOCCCLI_CMD_MANAGER_H_INCLUDED */
