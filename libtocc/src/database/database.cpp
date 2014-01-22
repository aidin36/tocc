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

#include "database/database.h"
#include "database/scripts.h"
#include "common/database_exceptions.h"

extern "C"
{
#include "unqlite.h"
}

namespace libtocc
{
  /*
   * Compiles and executes a Jx9 script.
   *
   * @param jx9_script: script to execute.
   * @param unqlite_vm: will be filled by virtual machine that is the
   *   result of the execution.
   */
  void execute_jx9(unqlite* db_pointer, std::string jx9_script, unqlite_vm** vm)
  {
    int result = unqlite_compile(db_pointer,
                                 jx9_script.c_str(),
				 jx9_script.length(),
                                 vm);

    if (result != UNQLITE_OK)
    {
      // Something goes wrong. Extracting error log.
      const char* log_buf;
      int log_len;
      unqlite_config(db_pointer, UNQLITE_CONFIG_JX9_ERR_LOG, &log_buf, &log_len);
      
      std::string error_message = "unknown error";
      if (log_len > 0)
      {
	error_message = log_buf;
      }

      throw DatabaseScriptCompilationError(error_message);
    }

    // Executing the script.
    result = unqlite_vm_exec(*vm);

    if (result != UNQLITE_OK)
    {
      throw DatabaseScriptExecutionError("Error executing the script.");
    }

    // Checking if any error occured inside the script.
    unqlite_value* execution_error = unqlite_vm_extract_variable(*vm, "error");
    if (execution_error != NULL)
    {
      // Second variable is a pointer to int, which returns the length of the
      // string. Since we don't need it, we passed null.
      throw DatabaseScriptExecutionError(unqlite_value_to_string(execution_error, NULL));
    }
  }

  Database::Database(std::string database_file)
  {
    int result;

    // Opening the database.
    result = unqlite_open(&this->db_pointer, database_file.c_str(), UNQLITE_OPEN_CREATE);

    if (result != UNQLITE_OK)
    {
      std::string message = "Error openning database file: [";
      message += database_file;
      message += "]";
      throw DatabaseInitializationError(message);
    }

    // Ensuring that collection is available.
    unqlite_vm* vm;
    execute_jx9(this->db_pointer, COLLECTION_CREATION, &vm);

    unqlite_vm_release(vm);
  }

  void Database::add_file(std::string file_id)
  {
    
  }

}
