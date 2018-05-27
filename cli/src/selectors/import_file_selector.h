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

#ifndef TOCCCLI_COPY_FILE_SELECTOR_H_INCLUDED
#define TOCCCLI_COPY_FILE_SELECTOR_H_INCLUDED

#include <libtocc/front_end/file_info.h>
#include <libtocc/front_end/manager.h>

#include "selectors/selector.h"


namespace tocccli
{

  /*
   * Imports a file to the Tocc managed file system.
   */
  class ImportFileSelector : public Selector
  {

    /*
     * Note: This class defined as a Selector rather than Action, because
     * usually user want to import a file, and do an action on it (import the
     * file and at the same time assign a tag to it). So ID of the newly
     * imported file should be among those that will passes to the actions.
     */

  public:
    ImportFileSelector(libtocc::Manager* manager);

    ~ImportFileSelector();

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
     * @param cmd_arguments: Arguments of this option that is passed to
     *   command line.
     *
     * @return: List of founded files.
     */
    virtual std::vector<libtocc::FileInfo> execute(std::vector<std::string> cmd_arguments);

  private:
    libtocc::Manager* libtocc_manager;
  };

}

#endif /* TOCCCLI_COPY_FILE_SELECTOR_H_INCLUDED */
