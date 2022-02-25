/*
 * This file is part of Tocc. (see <https://tocc.aidinhut.com>)
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

#ifndef LIBTOCC_DATABASE_H_INCLUDED
#define LIBTOCC_DATABASE_H_INCLUDED
//#define DATABASE_FILE "TOCCFILE"
#include <string>
#include <vector>
static const std::string DATABASE_FILE = "TOCCFILE";

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
     * Initializes the database file.
     * It should be called once for every new database file.
     * It throws exception if the database file is already initialized.
     */
    void initialize();

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
     *
     * @param file_id: ID of the file to get.
     *
     * @return: Information of the founded file.
     *
     * @throw DatabaseScriptLogicalError: if file not found.
     */
    IntFileInfo get(std::string file_id);

    /*
     * Gets a file by its traditional path.
     *
     * @param traditional_path: Traditional path to search for.
     *
     * @return: Information of the founded file.
     *
     * @throw DatabaseScriptLogicalError: if file not found.
     */
    IntFileInfo get_by_traditional_path(std::string traditional_path);

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
    * Unassigns the specified tags from a file
    */
   void unassign_tags(const std::string& file_id, const std::vector<std::string>& tags);

    /*
     * Unassigns the specified tags from each file
     */
    void unassign_tags(const std::vector<std::string>& files_ids, const std::vector<std::string>& tags);

    /*
     * Unassign a tag from a file.
     */
    void unassign_tag(const std::string& file_id, const std::string& tag);

    /*
     * Searching the files by executing the specified query.
     */
    std::vector<IntFileInfo> search_files(Query& query);

    /*
     * Collects statistics (how many files assigned to each tag) and
     * returns it.
     */
    TagStatisticsCollection get_tags_statistics();

    /*
     * Collects statistics of a list of files.
     * It returns list of tags assigned to these files, and how many files
     * is associated to each tag.
     *
     * @param file_ids: Files to get their statistics.
     */
    TagStatisticsCollection get_tags_statistics(const std::vector<std::string>& file_ids);

    /*
    * Sets a new title to a group of files
    * @param file_id : a vector of file ids to set title to
    * @param new_title : the new file's title
    */
    void set_titles(const std::vector<std::string>& file_ids, const std::string& new_title);


  private:
    std::string database_file;

    /*
     * Returns handler of opened UnQlite DB.
     *
     * @param readonly: If set to true, it opens the database in
     *   read-only mode (default).
     */
    unqlite* open_db(bool readonly=true);
  };

};

#endif /* LIBTOCC_DATABASE_H_INCLUDED */
