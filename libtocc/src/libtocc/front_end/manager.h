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
     * Assigns specified tags to all files in the specified list of files.
     *
     * @param file_ids: Files to assign tags to.
     * @param file_ids_size: size of the `file_ids' array. If set to
     *   zero or less, it will calculated automatically.
     * @param tags: Tags to assign to file.
     */
    void assign_tags(const char* file_ids[],
                     int file_ids_size,
                     const TagsCollection* tags);

    /*
     * Assigns tags to a file.
     *
     * @param file_id: File to assign tags to.
     * @param tags: Tags to assign to file.
     */
    void assign_tags(const char* file_id, const TagsCollection* tags);

    /*
     * Assigns a tag to a file.
     *
     * @param file_id: File to assign tags to.
     * @param tag: Tag to assign to file.
     */
    void assign_tags(const char* file_id, const char* tag);


  private:
    /*
     * Keeps the private data, and hides it from the client.
     */
    class PrivateData;
    PrivateData* private_data;
  };

}

#endif /* LIBTOCC_MANAGER_H_INCLUDED */
