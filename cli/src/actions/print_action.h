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

#ifndef TOCCCLI_PRINT_ACTION_H_INCLUDED
#define TOCCCLI_PRINT_ACTION_H_INCLUDED

#include <string>
#include <vector>

#include <libtocc.h>

#include "common/cmd_param.h"
#include "actions/action.h"


namespace tocccli
{

  /*
   * This action prints a file on the output when executes.
   */
  class PrintAction : public Action
  {
  public:
    PrintAction(libtocc::Manager* manager);

    virtual ~PrintAction();

    /*
     * Returns short form of the parameter.
     */
    virtual std::string get_short_form();

    /*
     * Returns long form of the parameter.
     */
    virtual std::string get_long_form();

    /*
     * Returns the help text of the parameter.
     * (Full help text, include parameter itself.)
     */
    virtual std::string get_help_text();

    /*
     * Executes the action.
     *
     * @param files: Files to do the action on.
     * @param cmd_arguments: Arguments of this parameter that is passed to
     *   command line.
     */
    virtual void execute(std::vector<libtocc::FileInfo> files, std::vector<std::string> cmd_arguments);

  private:
    libtocc::Manager* libtocc_manager;
  };
}

#endif /* TOCCCLI_PRINT_ACTION_H_INCLUDED */
