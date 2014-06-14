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

#ifndef LIBTOCC_MANAGER_H_INCLUDED
#define LIBTOCC_MANAGER_H_INCLUDED

#include "libtocc/front_end/file_info.h"
#include "libtocc/front_end/tag_statistics.h"
#include "libtocc/exprs/query.h"


namespace libtocc
{
  /*
   * The front end of the libtocc.
   */
  class Manager
  {
  public:
    /*
     * @param base_path: Base path of where tocc files kept.
     *   It should be an absolute path.
     */
    Manager(const char* base_path);

    ~Manager();

    /*
     * Gets information of a file.
     *
     * @param file_id: ID of the file to get.
     *
     * @return: Infomration of the file.
     *
     * @throw: DatabaseScriptLogicalError if file not found.
     */
    FileInfo get_file_info(const char* file_id);

    /*
     * Imports a file from the path to the Tocc managed file system.
     *
     * @param source_path: Path to the source file.
     * @param title: (optional) title of the file.
     * @param traditional_path: (optional) traditional path of the file.
     *
     * @return: Information of the newly created file.
     */
    FileInfo import_file(const char* source_path,
                         const char* title="",
                         const char* traditional_path="");

    /*
     * Imports a file from the path to the Tocc managed file system.
     *
     * @param source_path: Path to the source file.
     * @param title: title of the file.
     * @param traditional_path: traditional path of the file.
     *   (Can be empty string.)
     * @param tags: Tags to assign to the file.
     *
     * @return: Information of the newly created file.
     */
    FileInfo import_file(const char* source_path,
                         const char* title,
                         const char* traditional_path,
                         const TagsCollection* tags);

    /*
     * Deletes a file from the database and Tocc managed file system.
     *
     * @param file_id: the id of the file to delete.
     */
    void remove_file(const char* file_id);

     /*
     * Deletes an array of file ids from the database and Tocc managed file system.
     *
     * @param file_ids: an array of the ids of the files to delete.
     * @param file_ids_size : the size of the array of the file ids
     */
    void remove_files(const char* file_ids[], int file_ids_size);

     /*
     * Deletes a file from the database and Tocc managed file system.
     *
     * @param file_to_remove: the informations related to the file to delete.
     */
    void remove_file(FileInfo& file_to_remove);

     /*
     * Deletes a collection of FileInfos from the database and Tocc managed file system.
     *
     * @param files_to_remove: collection of the files to remove.
     */
    void remove_files(FileInfoCollection& files_to_remove);

    /*
     * Assigns specified tags to all files in the specified list of files.
     *
     * @param file_ids: Files to assign tags to.
     * @param file_ids_size: size of the `file_ids' array. If set to
     *   zero or less, it will calculated automatically.
     * @param tags: Tags to assign to file.
     *
     * @note: It won't throw any exception if no file found with these IDs.
     */
    void assign_tags(const char* file_ids[],
                     int file_ids_size,
                     const TagsCollection* tags);

    /*
     * Assigns tags to a file.
     *
     * @param file_id: File to assign tags to.
     * @param tags: Tags to assign to file.
     *
     * @note: It won't throw any exception if no file found with this ID.
     */
    void assign_tags(const char* file_id, const TagsCollection* tags);

    /*
     * Assigns a tag to a file.
     *
     * @param file_id: File to assign tags to.
     * @param tag: Tag to assign to file.
     *
     * @note: It won't throw any exception if no file found with this ID.
     */
    void assign_tags(const char* file_id, const char* tag);

    /*
     * Search files according to the specified query.
     *
     * @param query: Query to execute.
     *
     * @return: Collection of founded file. If nothing found,
     *   an empty collection will return.
     */
    FileInfoCollection search_files(Query& query);

    /*
     * Collects statistics (how many files assigned to each tag) and
     * returns it.
     */
    TagStatisticsCollection get_tags_statistics();

    /*
     * Sets a new title to a file
     * @param file_id : the id of the file
     * @param new_title : the new file's title
     */
    void set_title(const char* file_id, const char* new_title);

  private:
    /*
     * Keeps the private data, and hides it from the client.
     */
    class PrivateData;
    PrivateData* private_data;
  };

}

#endif /* LIBTOCC_MANAGER_H_INCLUDED */
