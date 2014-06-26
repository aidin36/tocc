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

#include "engine/fs_handler.h"

namespace toccfs
{

  FSHandler::FSHandler(std::string base_path)
  {
    this->libtocc_manager = new libtocc::Manager(base_path.c_str());
  }

  FSHandler::~FSHandler()
  {
    delete this->libtocc_manager;
  }

  std::vector<libtocc::FileInfo> FSHandler::get_by_path(std::string path)
  {
    //XXX: Temporary code.
    std::vector<libtocc::FileInfo> result;
    result.push_back(this->libtocc_manager->get_file_info("0000001"));
    return result;
  }
}
