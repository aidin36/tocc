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

#include <sstream>

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
   * Holds a pointer of Unqlite VM.
   * The purpose is to ensure that pointer is released properly.
   * When the instance of this class destroy, it will release
   * the pointer.
   */
  class VMPointerHolder
  {
  public:
    VMPointerHolder(unqlite_vm** vm_pointer)
    {
      this->vm_pointer = vm_pointer;
    }

    ~VMPointerHolder()
    {
      unqlite_vm_release(*this->vm_pointer);
    }

  private:
    unqlite_vm** vm_pointer;
  };

  /*
   * Holds a pointer to a Unqlite Value.
   * The purpose is to ensure that pointer is released properly.
   * When the instance of this class destroy, it will release
   * the pointer.
   */
  class UnqliteValueHolder
  {
  public:
    /*
     * @param value_pointer: Pointer to hold and then release.
     * @param vm: Pointer to the VM that created the value.
     *   This is require to release the pointer.
     */
    UnqliteValueHolder(unqlite_value* value_pointer, unqlite_vm* vm)
    {
      this->value_pointer = value_pointer;
      this->vm = vm;
    }

    ~UnqliteValueHolder()
    {
      unqlite_vm_release_value(this->vm, this->value_pointer);
    }

  private:
    unqlite_value* value_pointer;
    unqlite_vm* vm;
  };

  /*
   * Compiles a Jx9 script.
   *
   * @param jx9_script: script to execute.
   * @param unqlite_vm: will be filled by Virtual Machine that is the
   *   result of the compilation.
   */
  void compile_jx9(unqlite* db_pointer, std::string jx9_script, unqlite_vm** vm)
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
  }

  /*
   * Executes the Virtual Machine.
   *
   * @param vm: VM pointer. This should be first pass to the compile_jx9
   *   method to be filled.
   */
  void execute_vm(unqlite_vm* vm)
  {
    // Executing the vm.
    int result = unqlite_vm_exec(vm);

    if (result != UNQLITE_OK)
    {
      std::ostringstream message_stream;
      message_stream << "Error executing the script. Error No: " << result;
      throw DatabaseScriptExecutionError(message_stream.str());
    }

    // Checking if any error occurred inside the script.
    unqlite_value* execution_error = unqlite_vm_extract_variable(vm, "error");
    if (execution_error != NULL)
    {
      // Second variable is a pointer to int, which returns the length of the
      // string. Since we don't need it, we passed null.
      throw DatabaseScriptExecutionError(
          unqlite_value_to_string(execution_error, NULL));
    }
  }

  /*
   * Registers a string in the Jx9 script.
   *
   * @param vm: pointer to VM to register value in.
   * @param variable_name: Name of the variable to register.
   * @param value: Value of the variable.
   */
  void register_string(unqlite_vm* vm,
                       std::string variable_name,
                       std::string value)
  {
    // Creating a new scalar.
    unqlite_value* scalar = unqlite_vm_new_scalar(vm);
    // Auto release the value.
    UnqliteValueHolder holder(scalar, vm);

    // Fill the scalar.
    int result = unqlite_value_string(scalar, value.c_str(), value.length());

    if (result != UNQLITE_OK)
    {
      std::ostringstream message_stream;
      message_stream << "Error filling a Scalar with string value. ";
      message_stream << " Error No: " << result;
      message_stream << " Value: " << value;

      throw DatabaseScriptExecutionError(message_stream.str());
    }

    // Registering the variable.
    result = unqlite_vm_config(vm,
                               UNQLITE_VM_CONFIG_CREATE_VAR,
                               variable_name.c_str(),
                               scalar);

    if (result != UNQLITE_OK)
    {
      std::ostringstream message_stream;
      message_stream << "Error while registering a variable in script.";
      message_stream << "Error No: " << result;
      message_stream << " Variable Name: " << variable_name;
      message_stream << " Variable Value: " << value;

      throw DatabaseScriptExecutionError(message_stream.str());
    }
  }

  /*
   * Registers an array in the Jx9 script.
   *
   * @param vm: pointer to VM to register value in.
   * @param variable_name: Name of the variable to register.
   * @param value: Value of the variable.
   */
  void register_array(unqlite_vm* vm,
                      std::string variable_name,
                      std::list<std::string> value)
  {
    // Creating a new array.
    unqlite_value* array = unqlite_vm_new_array(vm);
    // Auto release the array.
    UnqliteValueHolder array_holder(array, vm);
    // Creating a new scalar.
    unqlite_value* scalar = unqlite_vm_new_scalar(vm);
    // Auto release the value.
    UnqliteValueHolder scalar_holder(scalar, vm);

    int result = 0;

    std::list<std::string>::iterator iterator = value.begin();
    for (; iterator != value.end(); ++iterator)
    {
      // re-fill the scalar with new value.
      result = unqlite_value_reset_string_cursor(scalar);
      if (result != UNQLITE_OK)
      {
        std::ostringstream message_stream;
        message_stream << "Error reseting the scalar. ";
        message_stream << " Error No: " << result;

        throw DatabaseScriptExecutionError(message_stream.str());
      }

      result = unqlite_value_string(scalar, (*iterator).c_str(), (*iterator).length());
      if (result != UNQLITE_OK)
      {
        std::ostringstream message_stream;
        message_stream << "Error reseting setting string to scalar. ";
        message_stream << " Error No: " << result;
        message_stream << ", Value: " << *iterator;

        throw DatabaseScriptExecutionError(message_stream.str());
      }

      // Append scalar to the array.
      result = unqlite_array_add_elem(array, NULL, scalar);
      if (result != UNQLITE_OK)
      {
        std::ostringstream message_stream;
        message_stream << "Error appending value to array. ";
        message_stream << " Error No: " << result;
        message_stream << ", Value: " << *iterator;

        throw DatabaseScriptExecutionError(message_stream.str());
      }
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

    // Ensuring that collection is available, by executing a Jx9 script.
    unqlite_vm* vm;
    // Auto release the pointer.
    VMPointerHolder holder(&vm);

    // Compiling and executing the Jx9 script.
    compile_jx9(this->db_pointer, COLLECTION_CREATION_SCRIPT, &vm);
    execute_vm(vm);
  }

  Database::~Database()
  {
    // Closing the database file.
    unqlite_close(this->db_pointer);
  }

  void Database::add_file(std::string file_id)
  {
  }

  void Database::assign_tag(std::string file_id, std::string tag)
  {
    std::list<std::string> file_ids;
    file_ids.push_back(file_id);
    std::list<std::string> tags;
    tags.push_back(tag);

    assign_tag(file_ids, tags);
  }

  void Database::assign_tag(std::string file_id,
                            std::list<std::string> tags)
  {
    std::list<std::string> file_ids;
    file_ids.push_back(file_id);

    assign_tag(file_ids, tags);
  }

  void Database::assign_tag(std::list<std::string> file_ids,
                            std::list<std::string> tags)
  {
    unqlite_vm* vm;
    // Auto release the pointer.
    VMPointerHolder holder(&vm);

    // Compiling the script (Which fills VM)
    compile_jx9(this->db_pointer, ASSIGN_TAGS_SCRIPT, &vm);

    // Registering variables in VM
    register_array(vm, "file_ids", file_ids);
    register_array(vm, "tags_to_assign", tags);

    // Executing VM
    execute_vm(vm);
  }

  void Database::unassign_tag(std::string file_id, std::string tag)
  {
    unqlite_vm* vm;
    // Auto release the pointer.
    VMPointerHolder holder(&vm);

    // Compiling the script (Which fills VM)
    compile_jx9(this->db_pointer, UNASSIGN_TAGS_SCRIPT, &vm);

    // Registering variables in VM
    register_string(vm, "file_id", file_id);
    register_string(vm, "tag_to_unassign", tag);

    // Executing VM
    execute_vm(vm);
  }

}
