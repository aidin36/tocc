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

#include "libtocc/database/database.h"
#include "libtocc/front_end/tag_statistics.h"


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


    /*
     * Unassigns a tag from a file
     *
     * @param file_id: File to unassign tag from.
     * @param tag: Tag to unassign from file.
     */
    void unassign_tag(const std::string& file_id, const std::string& tag);

    /*
     * Unassign the list of tags from all the specified files in the list
     *
     * @param file_ids: a list of the ids of the files to unassign tags from
     * @param tags: a list of tags to unassign from the files.
     */
    void unassign_tags(const std::vector<std::string>& file_ids, const std::vector<std::string>& tags);

    /* Unassign the list of tags from the specified file
     *
     * @param file_id: ID of the file to unassign tag from.
     * @param tags : a list of tags to unassign from the file.
     */
    void unassign_tags(const std::string& file_id, const std::vector<std::string>& tags);

    /*
     * Collects statistics (how many files assigned to each tag) and
     * returns it.
     */
    TagStatisticsCollection get_tags_statistics();

  private:
    /*
     * Instance of the database to work with.
     */
    Database* database;
  };

}

#endif /* LIBTOCC_TAG_MANAGER_H_INCLUDED */
