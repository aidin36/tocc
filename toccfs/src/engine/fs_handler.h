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

#ifndef TOCCFS_FS_HANDLER_H_INCLUDED
#define TOCCFS_FS_HANDLER_H_INCLUDED

#include <string>
#include <vector>

#include <libtocc/front_end/manager.h>
#include <libtocc/front_end/file_info.h>

namespace toccfs
{

  class FSHandler
  {
  public:
    FSHandler(std::string base_path);

    ~FSHandler();

    /*
     * Finds files using the specified path.
     * It converts the path to a Tocc query, and returns files founded
     * using that query.
     */
    std::vector<libtocc::FileInfo> get_by_path(std::string path);

  private:
    libtocc::Manager* libtocc_manager;
  };
}

#endif /* TOCCFS_FS_HANDLER_H_INCLUDED */
