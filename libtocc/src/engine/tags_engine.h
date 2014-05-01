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

#ifndef LIBTOCC_TAG_MANAGER_H_INCLUDED
#define LIBTOCC_TAG_MANAGER_H_INCLUDED

#include <string>
#include <vector>

#include "database/database.h"

namespace libtocc
{

  /*
   * Provides operations for working with Tags.
   */
  class TagsEngine
  {
  public:
    /*
     * @param database: Instance of the database to work with.
     */
    TagsEngine(Database* database);

    /*
     * Assigns specified tags to all files in the specified list of files.
     *
     * @param file_ids: Files to assign tags to.
     * @param tags: Tags to assign to file.
     */
    void assign_tags(std::vector<std::string> file_ids,
                     std::vector<std::string> tags);

    /*
     * Assigns tags to a file.
     *
     * @param file_id: File to assign tags to.
     * @param tags: Tags to assign to file.
     */
    void assign_tags(std::string file_id, std::vector<std::string> tags);

    /*
     * Assigns a tag to a file.
     *
     * @param file_id: File to assign tags to.
     * @param tag: Tag to assign to file.
     */
    void assign_tags(std::string file_id, std::string tag);

  private:
    /*
     * Instance of the database to work with.
     */
    Database* database;
  };

}

#endif /* LIBTOCC_TAG_MANAGER_H_INCLUDED */
