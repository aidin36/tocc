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

#include "libtocc/database/database.h"
#include "libtocc/file_system/file_manager.h"
#include "libtocc/engine/tags_engine.h"
#include "libtocc/engine/files_engine.h"
#include "libtocc/utilities/file_info_converter.h"
#include "libtocc/front_end/manager.h"


namespace libtocc
{

  /*
   * Name of the database file, which should be existed in the root
   * of the path.
   */
  const std::string DATABASE_FILE = "TOCCFILES.DB";

  class Manager::PrivateData
  {
  public:
    PrivateData(Database* database,
                TagsEngine* tags_engine,
                FilesEngine* files_engine,
                FileManager* file_manager)
    {
      this->database = database;
      this->tags_engine = tags_engine;
      this->files_engine = files_engine;
      this->file_manager = file_manager;
    }

    ~PrivateData()
    {
      delete this->database;
      this->database = NULL;
      delete this->tags_engine;
      this->tags_engine = NULL;
      delete this->files_engine;
      this->files_engine = NULL;
      delete this->file_manager;
      this->file_manager = NULL;
    }

    Database* database;
    TagsEngine* tags_engine;
    FilesEngine* files_engine;
    FileManager* file_manager;
  };

  Manager::Manager(const char* base_path)
  {
    std::string database_path(base_path);
    database_path += "/";
    database_path += DATABASE_FILE;

    Database* database = new Database(database_path);
    FileManager* file_manager = new FileManager(base_path);
    TagsEngine* tags_engine = new TagsEngine(database);
    FilesEngine* files_engine = new FilesEngine(database,
                                                file_manager,
                                                tags_engine);

    //Note: FileManager's pointer never used in this class. But kept in the
    //      PrivateData to be release later.

    this->private_data = new PrivateData(database, tags_engine,
                                         files_engine, file_manager);
  }

  Manager::~Manager()
  {
    delete this->private_data;
    this->private_data = NULL;
  }

  FileInfo Manager::get_file_info(const char* file_id)
  {
    IntFileInfo info = this->private_data->database->get(file_id);

    return to_external_file_info(&info, this->private_data->file_manager);
  }

  FileInfo Manager::import_file(const char* source_path,
                                const char* title,
                                const char* traditional_path)
  {
    IntFileInfo new_file_info =
        this->private_data->files_engine->import_file(source_path,
                                                      title, traditional_path);

    return to_external_file_info(&new_file_info, this->private_data->file_manager);
  }

  FileInfo Manager::import_file(const char* source_path,
                                const char* title,
                                const char* traditional_path,
                                const TagsCollection* tags)
  {
    std::vector<std::string> tags_vector = tags_to_vector(tags);

    IntFileInfo new_file_info =
        this->private_data->files_engine->import_file(source_path,
                                                      title,
                                                      traditional_path,
                                                      tags_vector);

    return to_external_file_info(&new_file_info, this->private_data->file_manager);
  }

  void Manager::remove_file(const char* file_id)
  {
    std::vector<std::string> file_ids;
    file_ids.push_back(std::string(file_id));
    this->private_data->files_engine->remove_files(file_ids);
  }

  void Manager::remove_file(FileInfo& file_to_remove)
  {
    std::vector<std::string> file_ids;
    file_ids.push_back(std::string(file_to_remove.get_id()));
    this->private_data->files_engine->remove_files(file_ids);
  }

  void Manager::remove_files(const char* file_ids[], int file_ids_size)
  {
    //Converting file_ids to vector
    std::vector<std::string> file_ids_vector = const_char_array_to_vector(file_ids, file_ids_size);

    //Remove the files
    this->private_data->files_engine->remove_files(file_ids_vector);
  }

  void Manager::remove_files(FileInfoCollection& files_to_remove)
  {
    //Converting the FileInfoCollection to a vector of file ids
    std::vector<std::string> file_ids = file_info_collection_to_vector_ids(files_to_remove);

    //Remove the files
    this->private_data->files_engine->remove_files(file_ids);
  }

  void Manager::assign_tags(const char* file_ids[],
                            int file_ids_size,
                            const TagsCollection* tags)
  {
    if (file_ids_size <= 0)
    {
      file_ids_size = sizeof(file_ids) / sizeof(file_ids[0]);
    }

    // Converting file_ids to vector.
    std::vector<std::string> file_ids_vector;
    for (int i = 0; i < file_ids_size; ++i)
    {
      file_ids_vector.push_back(file_ids[i]);
    }

    // Converting tags to vector.
    std::vector<std::string> tags_vector = tags_to_vector(tags);

    // Calling the engine to do the job.
    this->private_data->tags_engine->assign_tags(file_ids_vector, tags_vector);
  }

  void Manager::assign_tags(const char* file_id, const TagsCollection* tags)
  {
    // Converting tags to vector.
    std::vector<std::string> tags_vector = tags_to_vector(tags);

    this->private_data->tags_engine->assign_tags(file_id, tags_vector);
  }

  void Manager::assign_tags(const char* file_id, const char* tag)
  {
    this->private_data->tags_engine->assign_tags(file_id, tag);
  }

  void Manager::unassign_tag(const char* file_id, const char* tag)
  {
    this->private_data->tags_engine->unassign_tag(std::string(file_id), std::string(tag));
  }

  void Manager::unassign_tags(const char* file_id, const TagsCollection* tags)
  {
    std::vector<std::string> tags_vector = tags_to_vector(tags);
    this->private_data->tags_engine->unassign_tags(std::string(file_id), tags_vector);
  }

  void Manager::unassign_tags(const char* file_ids[], int file_ids_size, const TagsCollection* tags)
  {
    std::vector<std::string> tags_vector = tags_to_vector(tags);
    std::vector<std::string> file_ids_vector = const_char_array_to_vector(file_ids, file_ids_size);
    this->private_data->tags_engine->unassign_tags(file_ids_vector, tags_vector);
  }

  FileInfoCollection Manager::search_files(Query& query)
  {
    std::vector<IntFileInfo> founded_files =
        this->private_data->database->search_files(query);

    return to_external_file_infos(founded_files, this->private_data->file_manager);
  }

  TagStatisticsCollection Manager::get_tags_statistics()
  {
    return this->private_data->tags_engine->get_tags_statistics();
  }

  TagStatisticsCollection Manager::get_tags_statistics(const char* file_ids[], int file_ids_size)
  {
    //Converting file_ids to vector
    std::vector<std::string> vector_file_ids = const_char_array_to_vector(file_ids, file_ids_size);

    return this->private_data->tags_engine->get_tags_statistics(vector_file_ids);
  }

  void Manager::set_titles(const char* file_ids[], int file_ids_size, const char* new_title)
  {
    //Converting file_ids to vector
    std::vector<std::string> vector_file_ids = const_char_array_to_vector(file_ids, file_ids_size);

    this->private_data->files_engine->set_titles(vector_file_ids , new_title);
  }

  void Manager::set_title(const char* file_id, const char* new_title)
  {
    std::vector<std::string> file_ids;
    file_ids.push_back(std::string(file_id));
    this->private_data->files_engine->set_titles(file_ids , new_title);
  }
}
