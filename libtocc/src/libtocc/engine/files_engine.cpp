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
    {
      title = get_filename_from_path(source_path);
    }

    IntFileInfo new_file = this->database->create_file(tags, title,
                                                       traditional_path);

    this->file_manager->copy(source_path, new_file.get_id());

    return new_file;
  }

  void FilesEngine::remove_files(const std::vector<std::string>& files_to_remove)
  {
    std::vector<IntFileInfo> founded_files;

    this->database->remove_files(files_to_remove, founded_files);

    //Delete the founded files
    for(int i = 0; i < founded_files.size(); i++)
    {
      const std::string& file_id = std::string(founded_files[i].get_id());
      this->file_manager->remove(file_id.c_str());
    }
  }

  void FilesEngine::set_title(const char* file_id, const char* new_title)
  {
    this->database->set_title(std::string(file_id), std::string(new_title));
  }
}
