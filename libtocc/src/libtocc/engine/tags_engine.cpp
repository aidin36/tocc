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

#include "libtocc/engine/tags_engine.h"

namespace libtocc
{

  TagsEngine::TagsEngine(Database* database)
  {
    this->database = database;
  }

  void TagsEngine::assign_tags(std::string file_id,
                               std::vector<std::string> tags)
  {
    this->database->assign_tag(file_id, tags);
  }

  void TagsEngine::assign_tags(std::vector<std::string> file_ids,
                               std::vector<std::string> tags)
  {
    this->database->assign_tag(file_ids, tags);
  }

  void TagsEngine::assign_tags(std::string file_id, std::string tag)
  {
    this->database->assign_tag(file_id, tag);
  }

  void TagsEngine::unassign_tag(const std::string& file_id, const std::string& tag)
  {
    this->database->unassign_tag(file_id, tag);
  }

  void TagsEngine::unassign_tags(const std::string& file_id, const std::vector<std::string>& tags)
  {
    this->database->unassign_tags(file_id, tags);
  }

  void TagsEngine::unassign_tags(const std::vector<std::string>& file_ids, const std::vector<std::string>& tags)
  {
    this->database->unassign_tags(file_ids, tags);
  }

  TagStatisticsCollection TagsEngine::get_tags_statistics()
  {
    return this->database->get_tags_statistics();
  }

}
