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

#include "engine/cmd_manager.h"
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
    std::list<Selector*>::iterator selector_iterator = this->selectors.begin();
    for (; selector_iterator != this->selectors.end(); ++selector_iterator)
    {
      delete *selector_iterator;
    }

    std::list<Action*>::iterator action_iterator = this->actions.begin();
    for (; action_iterator != this->actions.end(); ++action_iterator)
    {
      delete *action_iterator;
    }

    delete this->libtocc_manager;
    this->libtocc_manager = NULL;
  }

  void CmdManager::execute(std::vector<std::vector<std::string> > cmd_parameters)
  {

  }
}
