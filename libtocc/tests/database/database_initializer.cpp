/*
 * This file is part of Tocc. (see <https://tocc.aidinhut.com>)
 * Copyright (C) 2013, 2014, Aidin Gharibnavaz <tocc@aidinhut.com>
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

#include <iostream>
#include <catch.hpp>
#include "testdb_path.hpp"
#define CATCH_CONFIG_MAIN

#include "libtocc/database/database.h"

std::string testdb_path(const std::string &filename)
{
#ifdef _MSC_VER
    return std::string("c:\\temp\\tocctests\\") + std::string(filename);
#else
    return std::string("/tmp/tocctests/") + std::string(filename);
#endif
}

/* Database initializer test moved to database_basic_tests.cpp by
 * Dick Thiebaud on 2/8/22 because it has to be in the same file
 * as other database tests or, under Windows, it is not executed
 * before the other tests.
*/
