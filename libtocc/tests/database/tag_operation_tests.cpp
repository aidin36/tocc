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

#include "libtocc/common/int_file_info.h"
#include "libtocc/database/database.h"

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
