/*
 * This file is part of TOCC. (see <http://www.github.com/aidin36/tocc>)
 * Copyright (C) 2013, 2014, Aidin Gharibnavaz <tocc@aidinhut.com>
 *
 * TOCC is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * TOCC is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 *  along with TOCC.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <string>

#include "engine/files_engine.h"

namespace libtocc
{

  FilesEngine::FilesEngine(Database* database,
                           FileManager* file_manager,
                           TagsEngine* tags_engine)
  {
    this->database = database;
    this->file_manager = file_manager;
    this->tags_engine = tags_engine;
  }

  IntFileInfo FilesEngine::get(std::string file_id)
  {
    return this->database->get(file_id);
  }

  IntFileInfo FilesEngine::copy_file(std::string source_path,
                                     std::string title,
                                     std::string traditional_path)
  {
    std::vector<std::string> empty_tags_list;

    return this->copy_file(source_path,
                           empty_tags_list,
                           title,
                           traditional_path);
  }

  IntFileInfo FilesEngine::copy_file(std::string source_path,
                                     std::vector<std::string> tags,
                                     std::string title,
                                     std::string traditional_path)
  {
    // TODO: Start a new database transaction and at the end commit it.

    IntFileInfo new_file = this->database->create_file(tags, title,
                                                       traditional_path);

    this->file_manager->copy(source_path, new_file.get_id());

    return new_file;
  }

}
