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

#include "libtocc/database/database.h"

#include <sstream>
#include <fstream>
#include <iostream>

#include "libtocc/database/base23.h"
#include "libtocc/database/scripts.h"
#include "libtocc/database/funcs.h"
#include "libtocc/exprs/compiler.h"
#include "libtocc/common/database_exceptions.h"
#include "libtocc/utilities/file_info_converter.h"
#include "libtocc/utilities/file_utils.h"

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
   * Holds a pointer to Unqlite DB.
   * It closes the DB at the destruction time. Thus, ensures the database
   * is opened and closed safety.
   */
  class UnqliteDBHolder
  {
  public:
    UnqliteDBHolder(unqlite* db_pointer)
    {
      this->db_pointer = db_pointer;
    }

    ~UnqliteDBHolder()
    {
      if (this->db_pointer != NULL)
      {
        unqlite_close(this->db_pointer);
        this->db_pointer = NULL;
      }
    }

  private:
    unqlite* db_pointer;
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

      throw DatabaseScriptCompilationError(error_message.c_str());
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
      throw DatabaseScriptExecutionError(message_stream.str().c_str());
    }

    // Checking if any error occurred inside the script.
    unqlite_value* execution_error = unqlite_vm_extract_variable(vm, "error");

    if (execution_error != NULL)
    {
      // Auto release value.
      UnqliteValueHolder holder(execution_error, vm);

      // Second variable is a pointer to int, which returns the length of the
      // string. Since we don't need it, we passed null.
      std::string error_message(unqlite_value_to_string(execution_error, NULL));
      throw DatabaseScriptLogicalError(error_message.c_str());
    }
  }

  /*
   * Extracts a variable from the specified VM.
   *
   * @param vm: pointer to VM.
   * @param variable_name: Name of the variable to extract.
   *
   * @return: Extracted variable. It will return an empty string
   *   if variable does not exists.
   */
  std::string extract_string_from_vm(unqlite_vm* vm, std::string variable_name)
  {
    unqlite_value* value = unqlite_vm_extract_variable(vm,
                                                       variable_name.c_str());

    if (value == NULL)
    {
      return "";
    }

    // Auto release value.
    UnqliteValueHolder holder(value, vm);

    std::string result(unqlite_value_to_string(value, NULL));

    return result;
  }

  /*
   * Extracts a variable from the specified VM.
   *
   * @param vm: pointer to VM.
   * @param variable_name: Name of the variable to extract.
   *
   * @return: Extracted variable. It will return zero
   *   if variable does not exists.
   */
  unsigned long extract_long_from_vm(unqlite_vm* vm, std::string variable_name)
  {
    unqlite_value* value = unqlite_vm_extract_variable(vm,
                                                       variable_name.c_str());

    if (value == NULL)
    {
      return 0;
    }

    // Auto release value.
    UnqliteValueHolder holder(value, vm);

    return unqlite_value_to_int64(value);
  }

  /*
   * Extracts a boolean from the specified VM.
   *
   * @param vm: pointer to VM.
   * @param variable_name: Name of the variable to extract.
   *
   * @return: Extracted variable. It will return false
   *   if variable does not exists.
   */
  bool extract_boolean_from_vm(unqlite_vm* vm, std::string variable_name)
  {
    unqlite_value* value = unqlite_vm_extract_variable(vm,
                                                       variable_name.c_str());

    if (value == NULL)
    {
      return false;
    }

    // Auto release value.
    UnqliteValueHolder holder(value, vm);

    return unqlite_value_to_bool(value);
  }

  /*
   * Call back for unqlite_array_walk.
   *
   * @param key: key of the array element.
   * @param value: value of the array element.
   * @param vector_to_fill: a pointer to a vector of strings.
   *   Each value will be push to this vector.
   */
  int string_array_walk_callback(unqlite_value* key, unqlite_value* value,
                                 void* vector_to_fill)
  {
    std::string string_value(unqlite_value_to_string(value, NULL));
    ((std::vector<std::string>*)vector_to_fill)->push_back(string_value);

    return UNQLITE_OK;
  }

  IntFileInfo convert_vm_object_to_file_info(unqlite_value* file_object)
  {
    // Extracting keys from object.
    unqlite_value* value_pointer;

    value_pointer = unqlite_array_fetch(file_object, "file_id", -1);
    if (value_pointer == NULL)
    {
      throw DatabaseScriptExecutionError("I found a file object that does not have a 'file_id'! Probably corrupted data.");
    }

    unsigned long file_id = unqlite_value_to_int64(value_pointer);
    IntFileInfo result(to_base23(file_id));

    value_pointer = unqlite_array_fetch(file_object, "title", -1);
    if (value_pointer != NULL)
    {
      result.set_title(unqlite_value_to_string(value_pointer, NULL));
    }

    value_pointer = unqlite_array_fetch(file_object, "traditional_path", -1);
    if (value_pointer != NULL)
    {
      result.set_traditional_path(unqlite_value_to_string(value_pointer, NULL));
    }

    value_pointer = unqlite_array_fetch(file_object, "tags", -1);
    // Note: If we trying to loop over an empty array, strange things may
    // happen. That's why all these checking exists.
    if (value_pointer != NULL &&
        unqlite_value_is_json_array(value_pointer) &&
        unqlite_array_count(value_pointer) > 0)
    {
      // Walking over this array and creating a vector of tags.
      std::vector<std::string> tags_vector;
      unqlite_array_walk(value_pointer,
                         string_array_walk_callback,
                         &tags_vector);
      result.set_tags(tags_vector);
    }

    return result;
  }

  /*
   * Extracts a file object from the VM.
   * It raises exception if specified variable name does not exists
   * in the VM.
   *
   * @param vm: VM to extract variable from.
   * @param variable_name: name of the variable to extract.
   *
   * @return: Instance of IntFileInfo.
   */
  IntFileInfo extract_file_from_vm(unqlite_vm* vm, std::string variable_name)
  {
    // Extracting variable from VM.
    unqlite_value* file_object =
        unqlite_vm_extract_variable(vm, variable_name.c_str());

    if (file_object == NULL)
    {
      std::stringstream message_stream;
      message_stream << "Error when extracting file object from VM: ";
      message_stream << "Variable \"" << variable_name << "\" does not exists.";
      throw DatabaseScriptExecutionError(message_stream.str().c_str());
    }

    // Auto release value.
    UnqliteValueHolder holder(file_object, vm);

    return convert_vm_object_to_file_info(file_object);
  }

  /*
   * Call back for unqlite_array_walk.
   *
   * @param key: key of the array element.
   * @param value: value of the array element.
   * @param vector_to_fill: a pointer to a vector of IntFileInfo.
   *   Each extracted value will be pushed to this vector.
   */
  int files_array_walk_callback(unqlite_value* key, unqlite_value* value,
                                void* vector_to_fill)
  {
    ((std::vector<IntFileInfo>*)vector_to_fill)->push_back(
        convert_vm_object_to_file_info(value));

    return UNQLITE_OK;
  }

  /*
   * Extracts a list of files from the Unqlite VM.
   *
   * @param vm: VM to extract variable from.
   * @param variable_name: Name of the variable in Jx9 that contains
   *   list of files.
   *
   * @return: Vector of extracted files.
   */
  std::vector<IntFileInfo> extract_files_list_from_vm(unqlite_vm* vm,
                                                      std::string variable_name)
  {
    // Extracting variable from VM.
    unqlite_value* files_array =
        unqlite_vm_extract_variable(vm, variable_name.c_str());

    if (files_array == NULL)
    {
      std::stringstream message_stream;
      message_stream << "Error when extracting files array from VM: ";
      message_stream << "Variable \"" << variable_name << "\" does not exists.";
      throw DatabaseScriptExecutionError(message_stream.str().c_str());
    }

    // Auto release value.
    UnqliteValueHolder holder(files_array, vm);

    // Checking health of the variable.
    if (!unqlite_value_is_json_array(files_array))
    {
      std::stringstream message_stream;
      message_stream << "In `extract_files_list_from_vm': ";
      message_stream << "Extracted variable was not an array. ";
      message_stream << "Variable name: \"" << variable_name << "\"";
      throw DatabaseScriptExecutionError(message_stream.str().c_str());
    }

    std::vector<IntFileInfo> result;

    if (unqlite_array_count(files_array) <= 0)
    {
      // Returning an empty vector: Nothing is found.
      return result;
    }

    // Walking over the array.
    unqlite_array_walk(files_array,
                       files_array_walk_callback,
                       &result);

    return result;
  }

  /*
   * Call back for unqlite_array_walk. Used in extract_tag_statistics_from_vm.
   *
   * @param key: key of the array element.
   * @param value: value of the array element.
   * @param vector_to_fill: a pointer to a TagStatisticsCollection to fill
   *   array's elements into.
   */
  int statistics_array_walk_callback(unqlite_value* key, unqlite_value* value,
                                     void* collection)
  {
    // Casting key and value to their true types.
    const char* tag = unqlite_value_to_string(key, NULL);
    int assigned_files = unqlite_value_to_int(value);

    // Adding new statistics to the collection.
    TagStatistics statistics(tag, assigned_files);
    ((TagStatisticsCollection*)collection)->add_statistics(statistics);

    return UNQLITE_OK;
  }


  TagStatisticsCollection extract_tag_statistics_from_vm(unqlite_vm* vm,
                                                         std::string variable_name)
  {
    // Extracting variable from VM.
    unqlite_value* statistics_object =
        unqlite_vm_extract_variable(vm, variable_name.c_str());

    if (statistics_object == NULL)
    {
      std::stringstream message_stream;
      message_stream << "Error when extracting tag statistics from VM: ";
      message_stream << "Variable \"" << variable_name << "\" does not exists.";
      throw DatabaseScriptExecutionError(message_stream.str().c_str());
    }

    // Auto release value.
    UnqliteValueHolder holder(statistics_object, vm);

    // Checking health of the variable.
    if (!unqlite_value_is_json_array(statistics_object))
    {
      std::stringstream message_stream;
      message_stream << "In `extract_tag_statistics_from_vm': ";
      message_stream << "Extracted variable was not an array. ";
      message_stream << "Variable name: \"" << variable_name << "\"";
      throw DatabaseScriptExecutionError(message_stream.str().c_str());
    }

    int array_count = unqlite_array_count(statistics_object);
    if (array_count == 0)
    {
      // Returning an empty result.
      TagStatisticsCollection result;
      return result;
    }

    // Creating a new collection, pre-reserving size.
    TagStatisticsCollection result(array_count);

    // Walking over the array and filling the collection.
    unqlite_array_walk(statistics_object,
                       statistics_array_walk_callback,
                       &result);

    return result;
  }

  /*
   * Registers a string in the Jx9 script.
   *
   * @param vm: pointer to VM to register value in.
   * @param variable_name: Name of the variable to register.
   * @param value: Value of the variable.
   */
  void register_variable_in_vm(unqlite_vm* vm,
                               const std::string& variable_name,
                               std::string value)
  {
    // Creating a new scalar.
    unqlite_value* scalar = unqlite_vm_new_scalar(vm);

    if (scalar == NULL)
    {
      throw DatabaseScriptExecutionError("Error creating a Scalar for VM");
    }

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

      throw DatabaseScriptExecutionError(message_stream.str().c_str());
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

      throw DatabaseScriptExecutionError(message_stream.str().c_str());
    }
  }

  /*
   * Registers an unsigned long in the Jx9 script.
   *
   * @param vm: pointer to VM to register value in.
   * @param variable_name: Name of the variable to register.
   * @param value: Value of the variable.
   */
  void register_variable_in_vm(unqlite_vm* vm,
                               const std::string& variable_name,
                               unsigned long value)
  {
    // Creating a new scalar.
    unqlite_value* scalar = unqlite_vm_new_scalar(vm);

    if (scalar == NULL)
    {
      throw DatabaseScriptExecutionError("Error creating a Scalar for VM");
    }

    // Auto release the value.
    UnqliteValueHolder holder(scalar, vm);

    // Fill the scalar.
    int result = unqlite_value_int64(scalar, value);

    if (result != UNQLITE_OK)
    {
      std::ostringstream message_stream;
      message_stream << "Error filling a Scalar with unsigned long value. ";
      message_stream << " Error No: " << result;
      message_stream << " Value: " << value;

      throw DatabaseScriptExecutionError(message_stream.str().c_str());
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

      throw DatabaseScriptExecutionError(message_stream.str().c_str());
    }
  }

  /*
   * Registers an array in the Jx9 script.
   *
   * @param vm: pointer to VM to register value in.
   * @param variable_name: Name of the variable to register.
   * @param value: Value of the variable.
   */
  void register_variable_in_vm(unqlite_vm* vm,
                               const std::string& variable_name,
                               std::vector<std::string> value)
  {
    // Creating a new array.
    unqlite_value* array = unqlite_vm_new_array(vm);
    // Auto release the array.
    UnqliteValueHolder array_holder(array, vm);

    // Creating a new scalar.
    unqlite_value* scalar = unqlite_vm_new_scalar(vm);

    if (scalar == NULL)
    {
      throw DatabaseScriptExecutionError("Error creating a Scalar for VM");
    }

    // Auto release the value.
    UnqliteValueHolder scalar_holder(scalar, vm);

    int result = 0;

    std::vector<std::string>::iterator iterator = value.begin();
    for (; iterator != value.end(); ++iterator)
    {
      // re-fill the scalar with new value.
      result = unqlite_value_reset_string_cursor(scalar);
      if (result != UNQLITE_OK)
      {
        std::ostringstream message_stream;
        message_stream << "Error reseting the scalar. ";
        message_stream << " Error No: " << result;

        throw DatabaseScriptExecutionError(message_stream.str().c_str());
      }

      result = unqlite_value_string(scalar, (*iterator).c_str(), (*iterator).length());
      if (result != UNQLITE_OK)
      {
        std::ostringstream message_stream;
        message_stream << "Error setting string to scalar. ";
        message_stream << " Error No: " << result;
        message_stream << ", Value: " << *iterator;

        throw DatabaseScriptExecutionError(message_stream.str().c_str());
      }

      // Append scalar to the array.
      result = unqlite_array_add_elem(array, NULL, scalar);
      if (result != UNQLITE_OK)
      {
        std::ostringstream message_stream;
        message_stream << "Error appending value to array. ";
        message_stream << " Error No: " << result;
        message_stream << ", Value: " << *iterator;

        throw DatabaseScriptExecutionError(message_stream.str().c_str());
      }
    }

    // Registering the variable.
    result = unqlite_vm_config(vm,
                               UNQLITE_VM_CONFIG_CREATE_VAR,
                               variable_name.c_str(),
                               array);

    if (result != UNQLITE_OK)
    {
      std::ostringstream message_stream;
      message_stream << "Error while registering an array in script.";
      message_stream << "Error No: " << result;
      message_stream << " Variable Name: " << variable_name;
      message_stream << " Variable Value: " << array;

      throw DatabaseScriptExecutionError(message_stream.str().c_str());
    }
  }

  /*
   * Registers an array in the Jx9 script.
   *
   * @param vm: pointer to VM to register value in.
   * @param variable_name: Name of the variable to register.
   * @param value: Value of the variable.
   */
  void register_variable_in_vm(unqlite_vm* vm,
                               const std::string& variable_name,
                               std::vector<unsigned long> value)
  {
    // Creating a new array.
    unqlite_value* array = unqlite_vm_new_array(vm);
    // Auto release the array.
    UnqliteValueHolder array_holder(array, vm);

    // Creating a new scalar.
    unqlite_value* scalar = unqlite_vm_new_scalar(vm);

    if (scalar == NULL)
    {
      throw DatabaseScriptExecutionError("Error creating a Scalar for VM");
    }

    // Auto release the value.
    UnqliteValueHolder scalar_holder(scalar, vm);

    int result = 0;

    std::vector<unsigned long>::iterator iterator = value.begin();
    for (; iterator != value.end(); ++iterator)
    {
      result = unqlite_value_int64(scalar, *iterator);
      if (result != UNQLITE_OK)
      {
        std::ostringstream message_stream;
        message_stream << "Error setting unsigned long to scalar. ";
        message_stream << " Error No: " << result;
        message_stream << ", Value: " << *iterator;

        throw DatabaseScriptExecutionError(message_stream.str().c_str());
      }

      // Append scalar to the array.
      result = unqlite_array_add_elem(array, NULL, scalar);
      if (result != UNQLITE_OK)
      {
        std::ostringstream message_stream;
        message_stream << "Error appending value to array. ";
        message_stream << " Error No: " << result;
        message_stream << ", Value: " << *iterator;

        throw DatabaseScriptExecutionError(message_stream.str().c_str());
      }
    }

    // Registering the variable.
    result = unqlite_vm_config(vm,
                               UNQLITE_VM_CONFIG_CREATE_VAR,
                               variable_name.c_str(),
                               array);

    if (result != UNQLITE_OK)
    {
      std::ostringstream message_stream;
      message_stream << "Error while registering an array in script.";
      message_stream << "Error No: " << result;
      message_stream << " Variable Name: " << variable_name;
      message_stream << " Variable Value: " << array;

      throw DatabaseScriptExecutionError(message_stream.str().c_str());
    }
  }

  /*
   * Registers available functions in Unqlite Virtual Machine.
   */
  void register_funcs_in_vm(unqlite_vm* vm)
  {
    int result = unqlite_create_function(vm,
                                         "wild_card_compare",
                                         wild_card_compare_unqlite_func,
                                         NULL);
    if (result != 0)
    {
      std::stringstream error_message;
      error_message << "Could not register `wild_card_compare' function.";
      error_message << " Error number: ";
      error_message << result;
      throw DatabaseScriptCompilationError(error_message.str().c_str());
    }
  }
#include <iostream>
  Database::Database(std::string database_file)
  {
    this->database_file = database_file;
 }

  Database::~Database()
  {
  }

  unqlite* Database::open_db(bool readonly)
  {
    // Checking if the database file exists.
    // Unqlite don't check if file really exists, in `unqlite_open' function.
    std::ifstream db_file_stream(this->database_file.c_str());
    if (!db_file_stream.good())
    {
      db_file_stream.close();
      std::string message(std::string("No database found in the base path specified: [") + this->database_file + std::string ("]"));
      message += " Make sure the path is correct, and it's initialized.";
      throw DatabaseInitializationError(message.c_str());
    }
    db_file_stream.close();

    unqlite* db_pointer;

    // Opening flags.
    unsigned int opening_flags = UNQLITE_OPEN_READONLY;
    if (!readonly)
    {
      opening_flags = UNQLITE_OPEN_READWRITE;
    }

    // Opening the database file.
    int result =
      unqlite_open(&db_pointer, this->database_file.c_str(), opening_flags);

    if (result != UNQLITE_OK)
    {
      std::stringstream message_stream;
      message_stream << "Error opening database file: [";
      message_stream << this->database_file;
      message_stream << "] Error code: ";
      message_stream << result;
      throw DatabaseInitializationError(message_stream.str().c_str());
    }

    return db_pointer;
  }

  void Database::initialize()
  {
    std::string message("Invalid path detected, please specify a valid path");

    if(is_path_parent_exists(database_file) == false)
    {
      throw DatabaseInitializationError(message.c_str());
    }
    // Checking if the database file already exists.
    std::ifstream db_file_stream(this->database_file.c_str());
   if (db_file_stream)
    {
      db_file_stream.close();

      std::string message("Specified path is already initialized.");
      message += " Initialize should only run once in every path.";
      throw DatabaseInitializationError(message.c_str());
    }
    // Opening the database.
    int result;
    unqlite* db_pointer;
    result = unqlite_open(&db_pointer, this->database_file.c_str(), UNQLITE_OPEN_CREATE);
    UnqliteDBHolder db_holder(db_pointer);
    if (result != UNQLITE_OK)
    {
      std::stringstream message_stream;
      message_stream << "Error opening database file: [";
      message_stream << this->database_file;
      message_stream << "] Error code: ";
      message_stream << result;
      throw DatabaseInitializationError(message_stream.str().c_str());
    }

    // Ensuring that collection is available, by executing a Jx9 script.
    unqlite_vm* vm;
    // Auto release the pointer.
    VMPointerHolder holder(&vm);

    // Compiling and executing the Jx9 script.
    compile_jx9(db_pointer, COLLECTION_CREATION_SCRIPT, &vm);
    execute_vm(vm);
  }

  IntFileInfo Database::create_file(std::string title,
                                    std::string traditional_path)
  {
    // Empty tag list.
    std::vector<std::string> empty_tags;
    return this->create_file(empty_tags,
                             title,
                             traditional_path);
  }

  IntFileInfo Database::create_file(std::vector<std::string> tags,
                                    std::string title,
                                    std::string traditional_path)

  {
    // Opening database in write mode.
    unqlite* db_pointer = open_db(false);
    UnqliteDBHolder db_holder(db_pointer);

    unqlite_vm* vm;
    // Auto release the pointer.
    VMPointerHolder holder(&vm);

    // Compiling the script (Which fills VM)
    compile_jx9(db_pointer, CREATE_FILE_SCRIPT, &vm);

    std::string variable_tags("tags");
    std::string variable_title("title");
    std::string variable_traditional_path("traditional_path");
    register_variable_in_vm(vm, variable_tags, tags);
    register_variable_in_vm(vm, variable_title, title);
    register_variable_in_vm(vm, variable_traditional_path, traditional_path);

    execute_vm(vm);
    return extract_file_from_vm(vm, "result");
  }

  void Database::remove_files(const std::vector<std::string>& file_ids, std::vector<IntFileInfo>& founded_files)
  {
    // Openning database in write mode.
    unqlite* db_pointer = open_db(false);
    UnqliteDBHolder db_holder(db_pointer);

    unqlite_vm* vm;
    VMPointerHolder vm_holder(&vm);

    //Executing script
    compile_jx9(db_pointer, REMOVE_FILES_SCRIPT, &vm);

    //Convert string ids to base23
    std::vector<unsigned long> converted_ids;
    std::vector<std::string>::const_iterator iterator = file_ids.begin();
    for(; iterator != file_ids.end(); ++iterator)
    {
      converted_ids.push_back(from_base23(*iterator));
    }

    //Register the converted_ids in VM
    std::string variable_file_ids("file_ids");
    register_variable_in_vm(vm, variable_file_ids, converted_ids);

    execute_vm(vm);

    std::string founded_files_variable("founded_files");
    founded_files = extract_files_list_from_vm(vm, founded_files_variable);
  }

  IntFileInfo Database::get(std::string file_id)
  {
    unqlite* db_pointer = open_db();
    UnqliteDBHolder db_holder(db_pointer);

    unqlite_vm* vm;
    // Auto release the pointer.
    VMPointerHolder holder(&vm);

    // Compiling the script.
    compile_jx9(db_pointer, GET_FILE_SCRIPT, &vm);

    std::string variable_file_id("file_id");
    std::string variable_orig_file_id("orig_file_id");
    register_variable_in_vm(vm, variable_file_id, from_base23(file_id));
    register_variable_in_vm(vm, variable_orig_file_id, file_id);

    execute_vm(vm);

    return extract_file_from_vm(vm, "result");
  }

  IntFileInfo Database::get_by_traditional_path(std::string traditional_path)
  {
    unqlite* db_pointer = open_db();
    UnqliteDBHolder db_holder(db_pointer);

    unqlite_vm* vm;
    // Auto release the pointer.
    VMPointerHolder holder(&vm);

    // Compiling the script.
    compile_jx9(db_pointer, GET_FILE_BY_TRADITIONAL_PATH_SCRIPT, &vm);

    std::string variable_traditional_path("traditional_path");
    register_variable_in_vm(vm, variable_traditional_path, traditional_path);

    execute_vm(vm);

    return extract_file_from_vm(vm, "result");
  }

  void Database::assign_tag(std::string file_id, std::string tag)
  {
    std::vector<std::string> file_ids;
    file_ids.push_back(file_id);
    std::vector<std::string> tags;
    tags.push_back(tag);

    assign_tag(file_ids, tags);
  }

  void Database::assign_tag(std::string file_id,
                            std::vector<std::string> tags)
  {
    std::vector<std::string> file_ids;
    file_ids.push_back(file_id);

    assign_tag(file_ids, tags);
  }

  void Database::assign_tag(std::vector<std::string> file_ids,
                            std::vector<std::string> tags)
  {
    // Opening database in write mode.
    unqlite* db_pointer = open_db(false);
    UnqliteDBHolder db_holder(db_pointer);

    unqlite_vm* vm;
    // Auto release the pointer.
    VMPointerHolder holder(&vm);

    // Compiling the script (Which fills VM)
    compile_jx9(db_pointer, ASSIGN_TAGS_SCRIPT, &vm);

    // Converting IDs.
    std::vector<unsigned long> converted_ids;
    std::vector<std::string>::iterator iterator = file_ids.begin();
    for(; iterator != file_ids.end(); ++iterator)
    {
      converted_ids.push_back(from_base23(*iterator));
    }

    // Registering variables in VM
    std::string variable_file_ids("file_ids");
    std::string variable_tags_to_assign("tags_to_assign");
    register_variable_in_vm(vm, variable_file_ids, converted_ids);
    register_variable_in_vm(vm, variable_tags_to_assign, tags);


    // Executing VM
    execute_vm(vm);
  }

  void Database::unassign_tags(const std::string& file_id, const std::vector<std::string>& tags)
  {
    std::vector<std::string> file_ids;
    file_ids.push_back(file_id);

    unassign_tags(file_ids, tags);
  }

  void Database::unassign_tag(const std::string& file_id, const std::string& tag)
  {
    std::vector<std::string> file_ids;
    std::vector<std::string> file_tags;

    file_ids.push_back(file_id);
    file_tags.push_back(tag);
    unassign_tags(file_ids, file_tags);
  }

  void Database::unassign_tags(const std::vector<std::string>& file_ids, const std::vector<std::string>& tags)
  {
    // Opening database in write mode.
    unqlite* db_pointer = open_db(false);
    UnqliteDBHolder db_holder(db_pointer);

    unqlite_vm* vm;
    // Auto release the pointer.
    VMPointerHolder holder(&vm);

    // Compiling the script (Which fills VM)
    compile_jx9(db_pointer, UNASSIGN_TAGS_SCRIPT, &vm);

    std::vector<unsigned long> converted_ids = string_vector_to_ulong_vector(file_ids);

    // Registering variables in VM
    std::string variable_file_id("file_ids");
    std::string variable_tag_to_unassign("tags_to_unassign");
    register_variable_in_vm(vm, variable_file_id, converted_ids);
    register_variable_in_vm(vm, variable_tag_to_unassign, tags);

    // Executing VM
    execute_vm(vm);
  }


  std::vector<IntFileInfo> Database::search_files(Query& query)
  {
    std::string result_variable_name = "fetched_records";

    // Compiling the query to a Jx9.
    QueryCompiler compiler;
    std::string jx9_script = compiler.compile(query, result_variable_name);

    unqlite* db_pointer = open_db();
    UnqliteDBHolder db_holder(db_pointer);

    unqlite_vm* vm;
    // Auto release the pointer.
    VMPointerHolder holder(&vm);

    // Compiling Jx9
    compile_jx9(db_pointer, jx9_script, &vm);

    // Registers external functions.
    register_funcs_in_vm(vm);

    // Executing vm.
    execute_vm(vm);

    return extract_files_list_from_vm(vm, result_variable_name);
  }

  TagStatisticsCollection Database::get_tags_statistics()
  {
    std::vector<std::string> empty_vector;
    return get_tags_statistics(empty_vector);
  }

  TagStatisticsCollection Database::get_tags_statistics(const std::vector<std::string>& file_ids)
  {
    unqlite* db_pointer = open_db();
    UnqliteDBHolder db_holder(db_pointer);

    unqlite_vm* vm;
    // Auto release the pointer.
    VMPointerHolder holder(&vm);

    // Compiling Jx9
    compile_jx9(db_pointer, COLLECT_TAGS_STATISTICS, &vm);

    std::string variable_name("file_ids");
    if (!file_ids.empty())
    {
      // Converting IDs.
      std::vector<unsigned long> converted_ids;
      std::vector<std::string>::const_iterator iterator = file_ids.begin();
      for(; iterator != file_ids.end(); ++iterator)
      {
        converted_ids.push_back(from_base23(*iterator));
      }

      register_variable_in_vm(vm, variable_name, converted_ids);
    }

    // Executing vm.
    execute_vm(vm);

    return extract_tag_statistics_from_vm(vm, "statistics");
  }

  void Database::set_titles(const std::vector<std::string>& file_ids, const std::string& new_title)
  {
    // Opening database in write mode.
    unqlite* db_pointer = open_db(false);
    UnqliteDBHolder db_holder(db_pointer);

    unqlite_vm* vm;
    VMPointerHolder vm_holder(&vm);

    //Executing set_title script
    compile_jx9(db_pointer, SET_TITLE_SCRIPT, &vm);

    // Converting IDs.
    std::vector<unsigned long> converted_ids;
    std::vector<std::string>::const_iterator iterator = file_ids.begin();
    for(; iterator != file_ids.end(); ++iterator)
    {
      converted_ids.push_back(from_base23(*iterator));
    }

   //Register the variables in VM
   std::string variable_file_id("file_ids");
   std::string variable_new_title("new_title");
   register_variable_in_vm(vm, variable_file_id, converted_ids);
   register_variable_in_vm(vm, variable_new_title, new_title);

   //Execute script
   execute_vm(vm);
  }
}
