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

#ifndef LIBTOCC_FILES_ENGINE_H_INCLUDED
#define LIBTOCC_FILES_ENGINE_H_INCLUDED

#include <string>
#include <vector>

#include "libtocc/common/int_file_info.h"
#include "libtocc/database/database.h"
#include "libtocc/file_system/file_manager.h"
#include "libtocc/engine/tags_engine.h"

namespace libtocc
{

  /*
   * Provides operations for working with files.
   */
  class FilesEngine
  {
  public:

    FilesEngine(Database* database,
                FileManager* file_manager,
                TagsEngine* tags_engine);

    /*
     * Gets information of a file.
     * It raises exception if file does not exists.
     *
     * @param file_id: ID of the file to get its information.
     *
     * @return: Information of the file.
     */
    IntFileInfo get(std::string file_id);

    /*
     * Imports a file from the path to the Tocc managed file system.
     *
     * @param source_path: Path to the source file.
     * @param title: (optional) title of the file.
     * @param traditional_path: (optional) traditional path of the file.
     *
     * @return: Information of the newly created file.
     */
    IntFileInfo import_file(std::string source_path,
                            std::string title="",
                            std::string traditional_path="");

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
    IntFileInfo import_file(std::string source_path,
                            std::string title,
                            std::string traditional_path,
                            std::vector<std::string> tags);
 
    /*
    * Sets a new title to a file
    *@param file_id : the id of the file
    *@param new_title : the new file's title
    */
    void set_title(const char* file_id, const char* new_title);

  private:
    Database* database;
    FileManager* file_manager;
    TagsEngine* tags_engine;
  };

}

#endif /* LIBTOCC_FILES_ENGINE_H_INCLUDED */
