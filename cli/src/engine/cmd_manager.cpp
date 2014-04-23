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

#include <sstream>

#include <libtocc.h>

#include "engine/cmd_manager.h"
#include "common/exceptions/cmd_usage_exceptions.h"
#include "selectors/id_selector.h"
#include "actions/print_action.h"


namespace tocccli
{

  CmdManager::CmdManager(std::string base_path)
  {
    this->libtocc_manager = new libtocc::Manager(base_path.c_str());

    /*
     * Instantiating all of available selectors.
     */
    this->selectors.push_back(new IDSelector(this->libtocc_manager));

    /*
     * Instantiating all of available actions.
     */
    this->actions.push_back(new PrintAction(this->libtocc_manager));
  }

  CmdManager::~CmdManager()
  {
    std::vector<Selector*>::iterator selector_iterator = this->selectors.begin();
    for (; selector_iterator != this->selectors.end(); ++selector_iterator)
    {
      delete *selector_iterator;
    }

    std::vector<Action*>::iterator action_iterator = this->actions.begin();
    for (; action_iterator != this->actions.end(); ++action_iterator)
    {
      delete *action_iterator;
    }

    delete this->libtocc_manager;
    this->libtocc_manager = NULL;
  }

  void CmdManager::execute(std::vector<CmdParam> cmd_parameters)
  {
    // Keeps files that are selected by Selectors.
    std::vector<libtocc::FileInfo> selected_files;

    // Keeps actions that should be executed later.
    // First element of pair is the action, and second one is the argument
    // passed in the command line.
    std::vector<std::pair<Action*, std::vector<std::string> > > actions_to_execute;

    std::vector<CmdParam>::iterator params_iterator = cmd_parameters.begin();
    for (; params_iterator < cmd_parameters.end(); ++params_iterator)
    {
      if ((*params_iterator).option == "-h" ||
          (*params_iterator).option == "--help")
      {
        if (!(*params_iterator).arguments.empty())
        {
          throw InvalidParametersError("-h or --help don't accept an argument.");
        }

        // Print usage and end.
        print_usage();
        return;
      }
      if ((*params_iterator).option == "-v" ||
          (*params_iterator).option == "--version")
      {
        if (!(*params_iterator).arguments.empty())
        {
          throw InvalidParametersError("-v or --version don't accept an argument.");
        }

        // Print version and end.
        print_version();
        return;
      }

      // Will set to true if any Selector or Action found for this option.
      bool option_handler_found = false;

      // Looking for Selectors and Actions among parameters.
      std::vector<Selector*>::iterator selectors_iterator =
          this->selectors.begin();
      for (; selectors_iterator < this->selectors.end(); ++selectors_iterator)
      {
        if ((*params_iterator).option == (*selectors_iterator)->get_short_form() ||
            (*params_iterator).option == (*selectors_iterator)->get_long_form())
        {
          // Executing the selector.
          std::vector<libtocc::FileInfo> files =
              (*selectors_iterator)->execute((*params_iterator).arguments);
          // Appending elements of `files' to `selected_files'.
          selected_files.insert(selected_files.end(), files.begin(), files.end());

          option_handler_found = true;
          break;
        }
      }

      if (option_handler_found)
      {
        // No need to check actions.
        continue;
      }

      std::vector<Action*>::iterator actions_iterator =
          this->actions.begin();
      for (; actions_iterator < this->actions.end(); ++actions_iterator)
      {
        if ((*params_iterator).option == (*actions_iterator)->get_short_form() ||
            (*params_iterator).option == (*actions_iterator)->get_long_form())
        {
          actions_to_execute.push_back(
              std::make_pair(*actions_iterator, (*params_iterator).arguments));

          option_handler_found = true;
          break;
        }
      }

      if (!option_handler_found)
      {
        // It means that this parameter didn't match any of the known ones.
        throw InvalidParametersError("Unknown option: " + (*params_iterator).option);
      }
    }

    // Now that all selectors executed and we have all the selected files,
    // we're going to run actions on them.
    std::vector<std::pair<Action*, std::vector<std::string> > >::iterator
      actions_iterator = actions_to_execute.begin();
    for (; actions_iterator < actions_to_execute.end(); ++actions_iterator)
    {
      (*actions_iterator).first->execute(selected_files, (*actions_iterator).second);
    }
  }

  void CmdManager::print_usage()
  {

  }

  void CmdManager::print_version()
  {

  }
}
