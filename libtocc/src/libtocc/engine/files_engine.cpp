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

#include <string>

#include "libtocc/engine/files_engine.h"
#include"libtocc/utilities/file_utils.h"

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

  IntFileInfo FilesEngine::import_file(std::string source_path,
                                       std::string title,
                                       std::string traditional_path)
  {
    std::vector<std::string> empty_tags_list;

    return this->import_file(source_path,
                             title,
                             traditional_path,
                             empty_tags_list);
  }

  IntFileInfo FilesEngine::import_file(std::string source_path,
                                       std::string title,
                                       std::string traditional_path,
                                       std::vector<std::string> tags)
  {
    if(title.empty())
	title = get_filename_from_path(source_path);

    IntFileInfo new_file = this->database->create_file(tags, title,
                                                       traditional_path);

    this->file_manager->copy(source_path, new_file.get_id());

    return new_file;
  }

}
