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

#ifndef LIBTOCC_FILE_MANAGER_H_INCLUDED
#define LIBTOCC_FILE_MANAGER_H_INCLUDED

/*
 * Defines FileManager class.
 */

#include <string>

namespace libtocc
{

  /*
   * A class for managing files on a file system.
   *
   * @note: Methods like create and copy will replace the existing
   *   file without any notify or confirmation. It's because the
   *   engine should check for duplicated before calling these
   *   methods.
   */
  class FileManager
  {
  public:
    /*
     * Constructor.
     * @param base_path: Path to work with. This is the root path of
     *   where it keeps files.
     */
    FileManager(std::string base_path);

    /*
     * Creates a file with the specified ID, and returns a file
     * descriptor.
     * Note that it replace the existing file silently.
     */
    int create(std::string file_id);

    /*
     * Opens the file with the specified ID, and returns its
     * file descriptor.
     */
    int open_file(std::string file_id, char mode);

    /*
     * Removes a file.
     * It silently ignores "file does not exists".
     */
    void remove(std::string file_id);

    /*
     * Copies a file to the specified file ID.
     * Note that It replaces the existing file silently.
     *
     * @param source_path: Absolute path of the file to copy.
     * @param file_id: ID of the file to copy the source to.
     */
    void copy(std::string source_path, std::string file_id);

    /*
     * Gets the path of the file on the Tocc-managed file system.
     */
    std::string get_physical_path(std::string file_id);

  private:
    std::string base_path;

    /*
     * Creates the specified path recursively.
     */
    void ensure_path_exists(std::string path);

    /*
     * Creates the specified path.
     */
    void create_dir(std::string path);

    /*
     * Converts the specified file_id to a directory path.
     */
    std::string id_to_dir_path(std::string id);

    /*
     * Converts the specified file_id to a file path.
     */
    std::string id_to_file_path(std::string id);
  };

};

#endif /* LIBTOCC_FILE_MANAGER_H_INCLUDE */
