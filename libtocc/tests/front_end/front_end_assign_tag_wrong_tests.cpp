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

#include "front_end/manager.h"
#include "common/database_exceptions.h"

/*
 * Test cases for scenarios that must throw exception.
 */
TEST_CASE("front_end: assign tag wrong tests")
{
  libtocc::Manager manager("/tmp/");

  REQUIRE_THROWS_AS(manager.assign_tags("f89ac3e", "author:Unknown"),
                    libtocc::DatabaseScriptExecutionError);

}
