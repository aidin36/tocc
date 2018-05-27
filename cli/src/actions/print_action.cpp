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

#include "actions/print_action.h"

#include <iostream>

#include "common/exceptions/cmd_usage_exceptions.h"


namespace tocccli
{

  /*
   * Prints out files without any special formatting.
   */
  void simple_print(std::vector<libtocc::FileInfo>& files)
  {
    std::vector<libtocc::FileInfo>::iterator iterator = files.begin();
    for (; iterator != files.end(); ++iterator)
    {
      std::cout << (*iterator).get_title() << "\t";
    }
    std::cout << std::endl;
  }

  namespace make_template_states
  {
    /*
     * States of converting arguments into templates.
     * Used in `make_template' method.
     */
    enum States { NONE, OPEN_BRACE, FILE_FIELD, CLOSE_BRACE };
  }

  /*
   * Defines elements of the Template.
   */
  class TemplateElement
  {
  public:
    TemplateElement()
    {
    }

    virtual ~TemplateElement()
    {
    }

    virtual std::string get(libtocc::FileInfo& file_info) = 0;
  };

  /*
   * Defines a string element inside template.
   */
  class StringTemplateElement : public TemplateElement
  {
  public:
    StringTemplateElement(std::string element)
    {
      this->element = element;
    }

    std::string get(libtocc::FileInfo& file_info)
    {
      return element;
    }

  private:
    std::string element;
  };

  /*
   * Defines a file's field element inside the template.
   */
  class FieldTemplateElement : public TemplateElement
  {
  public:
    FieldTemplateElement(std::string element)
    {
      this->element = element;
    }

    std::string get(libtocc::FileInfo& file_info)
    {
      if (this->element == "id")
      {
        return file_info.get_id();
      }
      else if (this->element == "title")
      {
        return file_info.get_title();
      }
      else if (this->element == "physical_path")
      {
        return file_info.get_physical_path();
      }
      else if (this->element == "traditional_path")
      {
        return file_info.get_traditional_path();
      }
      else if (this->element == "tags")
      {
        std::string result = "[";
        libtocc::TagsCollection tags = file_info.get_tags();

        libtocc::TagsCollection::Iterator iterator(&tags);
        for (; !iterator.is_finished(); iterator.next())
        {
          result += iterator.get();
          result += ", ";
        }

        // Removing last comma.
        result = result.substr(0, result.length() - 2);
        result += "]";
        return result;
      }

      std::string error_message = "Invalid `--print' argument: Don't know anything about [";
      error_message += this->element;
      error_message += "] field.";
      throw InvalidParametersError(error_message);
    }

  private:
    std::string element;
  };

  /*
   * Holds an instance of the template, and free it at the destruction.
   * This class is used to ensure that template is freed in every case.
   */
  class TemplateHolder
  {
  public:
    TemplateHolder(std::vector<TemplateElement*>* template_pointer)
    {
      this->template_pointer = template_pointer;
    }

    ~TemplateHolder()
    {
      // Deleting evey elements inside the vector.
      std::vector<TemplateElement*>::iterator iterator = this->template_pointer->begin();
      for (; iterator != this->template_pointer->end(); iterator++)
      {
        delete *iterator;
      }
    }

  private:
    std::vector<TemplateElement*>* template_pointer;
  };

  /*
   * Makes a template from the specified cmd arguments.
   * This template will be filled with file information later.
   */
  std::vector<TemplateElement*> make_template(std::vector<std::string>& cmd_arguments)
  {
    make_template_states::States state = make_template_states::NONE;
    std::vector<TemplateElement*> result;
    std::string current_element;

    std::vector<std::string>::iterator args_iterator = cmd_arguments.begin();
    for (; args_iterator != cmd_arguments.end(); args_iterator++)
    {
      std::string::iterator chars_iterator = args_iterator->begin();
      for (; chars_iterator != args_iterator->end(); chars_iterator++)
      {

        if (state == make_template_states::NONE)
        {
          if (*chars_iterator == '{')
          {
            state = make_template_states::OPEN_BRACE;
          }
          else if (*chars_iterator == '}')
          {
            state = make_template_states::CLOSE_BRACE;
          }
          else
          {
            current_element += *chars_iterator;
          }
        }

        else if (state == make_template_states::OPEN_BRACE)
        {
          if (*chars_iterator == '{')
          {
            // This brace is escaped.
            current_element += "{";
            state = make_template_states::NONE;
          }
          else if (*chars_iterator == '}')
          {
            throw InvalidParametersError("Empty braces detected in `--print' arguments.");
          }
          else
          {
            // This is one of the fields.
            // First, pushing normal text to result.
            result.push_back(new StringTemplateElement(current_element));
            // Then, Re-setting current element.
            current_element = *chars_iterator;
            // Setting state.
            state = make_template_states::FILE_FIELD;
          }
        }

        else if (state == make_template_states::FILE_FIELD)
        {
          if (*chars_iterator == '}')
          {
            // End of field.
            // Creating and pushing a field element.
            result.push_back(new FieldTemplateElement(current_element));
            // Re-setting current element.
            current_element = "";
            // Setting state.
            state = make_template_states::NONE;
          }
          else
          {
            current_element += *chars_iterator;
          }
        }

        else if (state == make_template_states::CLOSE_BRACE)
        {
          if (*chars_iterator != '}')
          {
            // This is a lonely close brace, and have to be a escaped brace.
            throw InvalidParametersError("A closed brace without any opened one detected in `--print' arguments.");
          }
          current_element += "}";
          state = make_template_states::NONE;
        }
      }

      // Arguments are split by spaces. We want these spaces appear
      // in the output.
      current_element += " ";
    }

    if (state != make_template_states::NONE)
    {
      throw InvalidParametersError("Invalid `--print' arguments: unexpected end of line while parsing");
    }

    // Pushing last element.
    result.push_back(new StringTemplateElement(current_element));

    return result;
  }

  /*
   * Prints out files according the the format that user specified.
   */
  void formatted_print(std::vector<libtocc::FileInfo>& files,
                       std::vector<std::string>& cmd_arguments)
  {
    // Creating a template from the specified arguments.
    std::vector<TemplateElement*> printing_template = make_template(cmd_arguments);
    // Auto releasing template.
    TemplateHolder holder(&printing_template);

    // Printing out files according to template.
    std::vector<libtocc::FileInfo>::iterator files_iterator = files.begin();
    for (; files_iterator != files.end(); files_iterator++)
    {
      std::vector<TemplateElement*>::iterator template_iteartor = printing_template.begin();
      for (; template_iteartor != printing_template.end(); template_iteartor++)
      {
        std::cout << (*template_iteartor)->get(*files_iterator);
      }

      std::cout << std::endl;
    }
  }

  PrintAction::PrintAction(libtocc::Manager* manager)
  {
    this->libtocc_manager = manager;
  }

  PrintAction::~PrintAction()
  {
  }

  std::string PrintAction::get_short_form()
  {
    return "-p";
  }

  std::string PrintAction::get_long_form()
  {
    return "--print";
  }

  std::string PrintAction::get_help_text()
  {
    return "-p, --print\tPrints founded files on output.";
  }

  void PrintAction::execute(std::vector<libtocc::FileInfo> files,
                            std::vector<std::string> cmd_arguments)
  {
    if (cmd_arguments.empty())
    {
      simple_print(files);
    }
    else
    {
      formatted_print(files, cmd_arguments);
    }
  }
}
