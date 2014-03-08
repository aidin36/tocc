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

#include <catch.hpp>

#include "common/int_file_info.h"
#include "database/database.h"

TEST_CASE("database: tag operation tests")
{
  libtocc::Database db("/tmp/tocc.test.db");

  // Assigning a single tag.
  db.assign_tag("0000001", "unique_book");

  // Checking if it's OK.
  libtocc::IntFileInfo file_info = db.get("0000001");
  REQUIRE(file_info.get_tags().size() >= 1);
  REQUIRE(file_info.get_tags().back() == "unique_book");
}
