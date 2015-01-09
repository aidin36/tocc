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
#include <cstring>
#include <catch.hpp>

#include "libtocc/database/funcs.h"

#include <iostream>

std::string try_regex(const char *regex_str, const char *match_str);

TEST_CASE("database::regex_tests:")
{
  REQUIRE(try_regex("a|b", "a") == "true");
  REQUIRE(try_regex("a|b", "b") == "true");
  REQUIRE(try_regex("a|b", "c") == "false");
  // Use strcmp in the next line instead of == of std::string because
  // using == caused std::bad_alloc to be thrown.
  REQUIRE(strcmp (try_regex("(((xx", "xx").c_str(), "Invalid regular expression: missing )"));
  REQUIRE(try_regex("A.\\d\\d\\d", "Ax934") == "true");
  REQUIRE(try_regex("A.\\d\\d\\d", "Ax9A4") == "false");
  REQUIRE(try_regex("\\\\", "\\") == "true");
}


#include "libtocc.h"

void check_rc(int rc, const char* message)
{
  if (rc != 0)
  {
    std::stringstream outmsg;
    outmsg << message << " return code = " << rc;
    libtocc::RuntimeLogicError runtime_except (outmsg.str().c_str());
    throw runtime_except;
  }
}

static std::string Jx9_output = "";
static int output_consumer(const void *p_output, unsigned int output_len, void *p_user_data /* Unused */)
{
  for (int i=0; i<output_len; ++i)
  {
    Jx9_output += ((const char *) p_output)[i];
  }
  return UNQLITE_OK;
}

std::string try_regex(const char *regex_str, const char *match_str)
{
  try
  {
    const char* jx9_part1 = "$x = ";
    const char* jx9_part2 = "; print \"$x\\n\";";
    Jx9_output = "";
    libtocc::RegexExpr r1(regex_str, 0);
    std::stringstream stream1;
    stream1 << std::string(jx9_part1) << r1.compile(match_str)
       << jx9_part2;
    unqlite* pDb = NULL;
    int rc = unqlite_open(&pDb, NULL, UNQLITE_OPEN_CREATE);
    check_rc (rc, "unqlite_open");
    unqlite_vm* pVm = NULL;
    rc = unqlite_compile(pDb, stream1.str().c_str(), -1, &pVm);
    check_rc (rc, "unqlite_compile");
    r1.create_Jx9_regex_match_function(pVm);
    check_rc (rc, "create regex match function");
    rc = unqlite_vm_config(pVm, UNQLITE_VM_CONFIG_OUTPUT, output_consumer, /* output consumer callback */
      0);
    check_rc (rc, "capture output");
    rc = unqlite_vm_exec(pVm);
    check_rc (rc, "unqlite_vm_exec");
    // trim trailing '\n' from Jx9_output
    if (Jx9_output[Jx9_output.length() - 1] == '\n')
    {
      Jx9_output = Jx9_output.substr(0, Jx9_output.length() -1);
    }
    if (pVm != NULL)
    {
      unqlite_vm_release(pVm);
    }
    if (pDb != NULL)
    {
      unqlite_close(pDb);
    }
    return Jx9_output;
  }
  catch (std::exception &e)
  {
  }
}

