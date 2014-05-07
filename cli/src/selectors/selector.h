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

#ifndef TOCCCLI_SELECTOR_HANDLER_H_INCLUDED
#define TOCCCLI_SELECTOR_HANDLER_H_INCLUDED

#include <string>
#include <vector>

#include <libtocc/front_end/file_info.h>

namespace tocccli
{

  /*
   * Base class for handlers of action parameters.
   */
  class Selector
  {
  public:

    virtual ~Selector();

    /*
     * Returns short form of the parameter.
     */
    virtual std::string get_short_form() = 0;

    /*
     * Returns long form of the parameter.
     */
    virtual std::string get_long_form() = 0;

    /*
     * Returns the help text of the parameter.
     * (Full help text, include parameter itself.)
     */
    virtual std::string get_help_text() = 0;

    /*
     * Executes the selector.
     *
     * @param cmd_arguments: Arguments of this option that is passed to
     *   command line.
     *
     * @return: List of founded files.
     */
    virtual std::vector<libtocc::FileInfo> execute(std::vector<std::string> cmd_arguments) = 0;
  };
}

#endif /* TOCCCLI_SELECTOR_HANDLER_H_INCLUDED */
