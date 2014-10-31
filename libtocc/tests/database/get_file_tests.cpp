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
#include <exception>
#include "libtocc/database/database.h"
#include "libtocc/common/file_system_exceptions.h"
#include "libtocc/common/database_exceptions.h"

TEST_CASE("database: get file tests")
{
  std::string invalid_id_msg =  "ID must be seven characters and only contain 0-9 and a-m.";
  // Creating the database.
  libtocc::Database db("/tmp/tocctests/tocc.test.db");

  // Getting a not-existing file.
  std::string msg = "";
  
  // Test message for id with invalid character.
  try {
    db.get("ffr98a0");
  }
  catch (const libtocc::InvalidArgumentError& e)
  {
    msg = e.what();
  }  
  REQUIRE (msg == libtocc::invalid_id_msg); 
  
  // Test message for id with wrong length.
  msg = "";
  try {
    db.get("000001");
  }
  catch (const libtocc::InvalidArgumentError& e)
  {
    msg = e.what();
  }
  REQUIRE (msg == libtocc::invalid_id_msg); 
 
  // Test message for valid id notfound.
  msg = "";
  try {
    db.get("ffa98a0");
  }
  catch (libtocc::DatabaseScriptLogicalError& e)
  {
    msg = e.what();
  }
  REQUIRE (msg == "File ffa98a0 does not exist.");
}
