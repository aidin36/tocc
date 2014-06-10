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

#ifndef LIBTOCC_DATABASE_H_INCLUDED
#define LIBTOCC_DATABASE_H_INCLUDED

#include <string>
#include <vector>

#include "libtocc/exprs/query.h"
#include "libtocc/common/int_file_info.h"
#include "libtocc/front_end/tag_statistics.h"

// Forward declaration of unqlite. So I don't have to include the
// unqlite.h in my header, so it will be hidden from the others
// who include this header.
struct unqlite;

namespace libtocc
{

  /*
   * NOTE: Each instance of this class holds a handler of the database file
   * specified in constructor. So, you can't have two instances of this
   * class with the same database file. (Unqlite locks the database file
   * and will raise an exception if file opens twice.)
   */
  class Database
  {
  public:
    /*
     * Constructor.
     * @param database_file: database to work with.
     */
    Database(std::string database_file);

    ~Database();

    /*
     * Creates a new file in database.
     *
     * @param title: title of the file.
     * @param traditional_path: traditional path of the file.
     *
     * @return: newly created file.
     */
    IntFileInfo create_file(std::string title="",
                            std::string traditional_path="");

    /*
     * Creates a new file in database.
     *
     * @param tags: tags to assign to file.
     * @param title: title of the file.
     * @param traditional_path: traditional path of the file.
     *
     * @return: newly created file.
     */
    IntFileInfo create_file(std::vector<std::string> tags,
                            std::string title="",
                            std::string traditional_path="");

    /*
     * Removes files from database.
     *
     * @param file_ids: the ids of the files to remove.
     * @param OUT: the founded files(among the files passed in file_ids) in the database
     *
     */
    void remove_files(const std::vector<std::string>& file_ids, std::vector<IntFileInfo>& founded_files);

    /*
     * Gets a file by its ID.
     * Raises exception if file not found.
     *
     * @param file_id: ID of the file to get.
     *
     * @return: Information of the founded file.
     */
    IntFileInfo get(std::string file_id);

    /*
     * Assigns specified tags to each specified file.
     */
    void assign_tag(std::vector<std::string> file_ids,
                    std::vector<std::string> tags);

    /*
     * Assigns specified tags to the file.
     */
    void assign_tag(std::string file_id,
                    std::vector<std::string> tags);

    /*
     * Assigns a tag to a file.
     */
    void assign_tag(std::string file_id, std::string tag);

    /*
     * Unassign a tag from a file.
     */
    void unassign_tag(std::string file_id, std::string tag);

    /*
     * Searching the files by executing the specified query.
     */
    std::vector<IntFileInfo> search_files(Query& query);

    /*
     * Collects statistics (how many files assigned to each tag) and
     * returns it.
     */
    TagStatisticsCollection get_tags_statistics();

  private:
    /*
     * Database handler.
     */
    unqlite* db_pointer;

  };

};

#endif /* LIBTOCC_DATABASE_H_INCLUDED */
