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

#ifndef TOCCCLI_ID_SELECTOR_H_INCLUDED
#define TOCCCLI_ID_SELECTOR_H_INCLUDED

#include <string>
#include <vector>

#include <libtocc.h>

#include "selectors/selector.h"


namespace tocccli
{

  /*
   * Selects a file by its ID.
   */
  class IDSelector : public Selector
  {
  public:
    IDSelector(libtocc::Manager* manager);

    virtual ~IDSelector();

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
     * Executes the selector.
     *
     * @param cmd_value: Value of this parameter that is passed from
     *   command line.
     *
     * @return: List of founded files.
     */
    virtual std::vector<libtocc::FileInfo> execute(std::string cmd_value);

  private:
    libtocc::Manager* libtocc_manager;
  };
}

#endif /* TOCCCLI_ID_SELECTOR_H_INCLUDED */
