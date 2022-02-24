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


#include <catch.hpp>


#include "libtocc/database/funcs.h"


TEST_CASE("database::wild_card_tests: no wild card match")
{
  REQUIRE(libtocc::wild_card_compare("same thing", "same thing"));
}

TEST_CASE("database::wild_card_tests: simple match 1")
{
  REQUIRE(libtocc::wild_card_compare("ha*", "happy"));
}

TEST_CASE("database::wild_card_tests: simple match 2")
{
  REQUIRE(libtocc::wild_card_compare("ha*y", "happy"));
}

TEST_CASE("database::wild_card_tests: simple match 3")
{
  REQUIRE(libtocc::wild_card_compare("*y", "happy"));
}

TEST_CASE("database::wild_card_tests: two cards match")
{
  REQUIRE(libtocc::wild_card_compare("*ve*cc", "I love tocc"));
}

TEST_CASE("database::wild_card_tests: no wild card un-match")
{
  REQUIRE(!libtocc::wild_card_compare("sad", "happy"));
}

TEST_CASE("database::wild_card_tests: no wild card un-match 2")
{
  REQUIRE(!libtocc::wild_card_compare("random int", "random str"));
}

TEST_CASE("database::wild_card_tests: simple un-match 1")
{
  REQUIRE(!libtocc::wild_card_compare("do*s", "don't match me"));
}

TEST_CASE("database::wild_card_tests: simple un-match 2")
{
  REQUIRE(!libtocc::wild_card_compare("*mass", "don't match me"));
}

TEST_CASE("database::wild_card_tests: simple un-match 3")
{
  REQUIRE(!libtocc::wild_card_compare("don't do*", "don't match me"));
}

TEST_CASE("database::wild_card_tests: empty pattern")
{
  REQUIRE(!libtocc::wild_card_compare("", "don't match me"));
}

TEST_CASE("database::wild_card_tests: empty string")
{
  REQUIRE(!libtocc::wild_card_compare("wild*", ""));
}

TEST_CASE("database::wild_card_tests: NULL pattern")
{
  REQUIRE(!libtocc::wild_card_compare(NULL, "don't match me"));
}

TEST_CASE("database::wild_card_tests: NULL string")
{
  REQUIRE(!libtocc::wild_card_compare("*wild", NULL));
}

TEST_CASE("database::wild_card_tests: NULL NULL")
{
  REQUIRE(!libtocc::wild_card_compare(NULL, NULL));
}
