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

#include <catch.hpp>
#include <vector>
#include <string>

#include "libtocc/database/database.h"
#include "libtocc/engine/tags_engine.h"

TEST_CASE("engine: tags engine tests")
{
  // Creating instance of engine.
  libtocc::Database db("/tmp/tocctests/tocc.test.db");
  libtocc::TagsEngine tags_engine(&db);

  // Assigning some tags.
  std::vector<std::string> new_tags;
  new_tags.push_back("author: Mr.Pen");
  new_tags.push_back("type: pdf");
  tags_engine.assign_tags("0000001", new_tags);

}
