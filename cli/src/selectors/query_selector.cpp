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

#include "selectors/query_selector.h"

#include <utility> // std::pair
#include <sstream>
#include <vector>

#include <libtocc/exprs/query.h>
#include <libtocc/exprs/expr.h>
#include "libtocc/front_end/file_info.h"
#include <utilities/string_utils.h>

#include "common/exceptions/cmd_usage_exceptions.h"


namespace tocccli
{

  /*
   * Forward decelerations.
   */
  libtocc::ConnectiveExpr* extract_next_term(std::vector<std::string>& arguments, int& index);

  /*
   * Holds a list of Expr pointers, and release them when destroys.
   */
  class ExprPointerHolder
  {
  public:
    ExprPointerHolder(libtocc::Expr* pointer_to_hold)
    {
      this->pointers.push_back(pointer_to_hold);
    }

    ~ExprPointerHolder()
    {
      // Deleting all pointers.
      std::vector<libtocc::Expr*>::iterator iterator = this->pointers.begin();
      for (; iterator != this->pointers.end(); iterator++)
      {
        delete *iterator;
      }
    }

    /*
     * Adds a pointer to the holder.
     */
    void add(libtocc::Expr* pointer_to_hold)
    {
      this->pointers.push_back(pointer_to_hold);
    }

  private:
    std::vector<libtocc::Expr*> pointers;
  };

  /*
   * Pointer to function that creates a field.
   */
  typedef libtocc::Expr* (*FieldCreatorFunction)(std::vector<std::string>& arguments, int& index);

  /*
   * Throws a parsing exception, and formats its message in a pretty form.
   *
   * @param arguments: Arguments that had error.
   * @param index: Index should point to the element of `arguments' that
   *    was parsing before the error occur.
   * @param message: Error message.
   */
  void throw_parsing_exception(std::vector<std::string>& arguments, int index, std::string message)
  {
    std::stringstream args_stream;
    std::stringstream error_marker_stream;
    int error_marker_index = 0;

    std::vector<std::string>::iterator iterator = arguments.begin();
    for (; iterator != arguments.end(); ++iterator)
    {
      args_stream << " " << *iterator;

      if (error_marker_index < index)
      {
        std::string spaces(iterator->size(), ' ');
        error_marker_stream << " " << spaces;
        error_marker_index++;
      }
    }

    error_marker_stream << "^";

    throw InvalidParametersError(message + "\n" + args_stream.str() + "\n" + error_marker_stream.str());
  }

  /*
   * Split argument at `index', from `pos' position. Then, keep the first
   * part in `index', and insert the second part in the `arguments' as the
   * element after that.
   */
  void move_arguments_forward(std::vector<std::string>& arguments, int& index,
                              int pos)
  {
    std::string& arg = arguments[index];
    arguments.insert(arguments.begin() + index, arg.substr(0, pos));

    std::string& next_arg = arguments[index + 1];
    next_arg.erase(0, pos);
  }

  /*
   * Checks if `opt' matches the argument at `index'. If it match, it
   * put value related to `opt' (its operand) into `extracted_value'.
   * Returns true if `opt' matches, false otherwise.
   */
  bool try_extract_opt(std::vector<std::string>& arguments, int& index,
                       std::string opt, std::string* extracted_value)
  {
    std::string& arg = arguments[index];

    if (!string_starts_with(arg, opt))
    {
      return false;
    }

    if (arg.compare(opt) != 0)
    {
      // arg contains opt and its value.
      move_arguments_forward(arguments, index, opt.size());
    }

    index++;

    if (index >= arguments.size())
    {
      throw_parsing_exception(arguments, index,
          "Expected an operand after operator, but reached end of string.");
    }

    *extracted_value = arguments[index];

    index++;

    return true;
  }

  /*
   * Creates a tag expression.
   *
   * @param opt: Operator to use.
   * @param value: Value to compare tag to.
   */
  libtocc::Expr* create_tag(std::vector<std::string>& arguments, int& index)
  {
    std::string value;

    if (try_extract_opt(arguments, index, "=", &value))
    {
      // By default, "=" operation will compile to WildCardExpr. So, user
      // can simply invoke a query like "tag = 2014*"

      libtocc::WildCardExpr wild_card_expr(value.c_str());
      return new libtocc::Tag(wild_card_expr);
    }
    if (try_extract_opt(arguments, index, "!=", &value) ||
        try_extract_opt(arguments, index, "~", &value))
    {
      libtocc::WildCardExpr wild_card_expr(value.c_str());
      libtocc::Tag tag_expr(wild_card_expr);
      return new libtocc::Not(tag_expr);
    }

    // Nothing matched.
    throw_parsing_exception(arguments, index,
                            "Invalid operator: " + arguments[index]);
  }

  /*
   * Creates a title expression.
   */
  libtocc::Expr* create_title(std::vector<std::string>& arguments, int& index)
  {
    std::string value;

    if (try_extract_opt(arguments, index, "=", &value))
    {
      // By default, "=" operation will compile to WildCardExpr. So, user
      // can simply invoke a query like "tag = 2014*"

      libtocc::WildCardExpr wild_card_expr(value.c_str());
      return new libtocc::Title(wild_card_expr);
    }

    if (try_extract_opt(arguments, index, "!=", &value) ||
        try_extract_opt(arguments, index, "~", &value))
    {
      libtocc::WildCardExpr wild_card_expr(value.c_str());
      libtocc::Title title_expr(wild_card_expr);
      return new libtocc::Not(title_expr);
    }

    // Nothing matched.
    throw_parsing_exception(arguments, index,
                            "Invalid operator: " + arguments[index]);
  }

  /*
   * Returns the creator function of the specified field name.
   * It will return NULL if no function found.
   */
  FieldCreatorFunction get_field_creator(std::vector<std::string>& arguments,
                                         int& index)
  {
    std::string& arg = arguments[index];

    std::string field_str = "tag";
    if (string_starts_with(arg, field_str))
    {
      if (arg.compare(field_str) != 0)
      {
        // If "tag" is only part of the argument (e.g. "tag=..."),
        // we parse `arg', remove "tag" from its start, and keep the rest.
        move_arguments_forward(arguments, index, 3);
      }

      index++;
      return create_tag;
    }

    field_str = "title";
    if (string_starts_with(arg, field_str))
    {
      if (arg.compare(field_str) != 0)
      {
        move_arguments_forward(arguments, index, 5);
      }

      index++;

      return create_title;
    }

    // If none of the above matches.
    return NULL;
  }

  /*
   * Parse a term between two parenthesizes and returns its equivalent
   * expression.
   * It's move the `index' forward to the element after the last closed
   * parenthesize.
   */
  libtocc::Expr* extract_parenthesizes(std::vector<std::string>& arguments, int& index)
  {
    // Assuming that whole arguments inside these parenthesizes is one term.
    std::vector<std::string> internal_term;

    // Keeps the first argument.
    // Note: I kept an individual variable for it, because I don't want to
    // edit the original variable. Original variable used later for producing
    // error message.
    std::string first_argument;

    if (arguments[index] == "(")
    {
      // If it's only a parenthesize, simply ignore it.
      index++;
      first_argument = arguments[index];
      index++;
    }
    else
    {
      // Removing the first character (the parenthesize).
      first_argument = arguments[index];
      first_argument.erase(0, 1);
      index++;
    }

    if (first_argument == ")")
    {
      throw_parsing_exception(arguments, index,
          "Empty parenthesize detected.");
    }

    // Looping through the arguments to find where parenthesize closed.
    int opened_parenthesize = 1;
    internal_term.push_back(first_argument);
    while (opened_parenthesize > 0)
    {
      if (index >= arguments.size())
      {
        throw_parsing_exception(arguments, index - 1,
            "Invalid number of parenthesizes: Reached end of string while looking for a close parenthesize.");
      }

      if (*arguments[index].rbegin() == ')')
      {
        opened_parenthesize--;
      }
      else if (*arguments[index].begin() == '(')
      {
        opened_parenthesize++;
      }

      internal_term.push_back(arguments[index]);
      index++;
    }

    if (internal_term.back() == ")")
    {
      // It's a simple closed parenthesize. Simply ignore it.
      internal_term.pop_back();
    }
    else
    {
      // Removing last character of last term. (The close parenthesize at the
      // end of the term.)
      std::string last_term = internal_term.back().substr(0, internal_term.back().size() - 1);
      internal_term.pop_back();
      internal_term.push_back(last_term);
    }

    int internal_index = 0;
    return extract_next_term(internal_term, internal_index);
  }

  /*
   * Parses the next element in the arguments list, and convert it to an
   * operand.
   * It moves the `index' forward to point to the next element after the
   * operand.
   */
  libtocc::Expr* extract_next_operand(std::vector<std::string>& arguments, int& index)
  {
    if (arguments[index].compare(0, 1, "(") == 0)
    {
      // The whole thing between parenthesizes is the operand.
      return extract_parenthesizes(arguments, index);
    }

    /*
     * We expect three words: field, operator and value to compare.
     */

    // First, the field.
    // Getting the field creator function.
    FieldCreatorFunction field_creator_function =
        get_field_creator(arguments, index);
    if (field_creator_function == NULL)
    {
      throw_parsing_exception(arguments, index,
          "Unknown field: Expected one of 'tag', 'title', etc, found: " + arguments[index]);
    }

    if (index >= arguments.size())
    {
      throw_parsing_exception(arguments, index,
                              "Reached end of string while looking for an operator.");
    }

    // Next, the operator and its operand.
    // Field creator function will extract these two itself.
    return field_creator_function(arguments, index);
  }

  /*
   * Makes a connector form the specified string.
   *
   * @param connector_string: Connector in the string form.
   * @param operand: Operand to add into the connector.
   */
  libtocc::ConnectiveExpr* make_connector(std::string connector_string,
                                          libtocc::Expr* operand)
  {
    if (connector_string == "and")
    {
      if (operand->get_type() == libtocc::expr_type::CONNECTIVE)
      {
        return new libtocc::And((libtocc::ConnectiveExpr&)*operand);
      }
      else
      {
        return new libtocc::And((libtocc::FieldExpr&)*operand);
      }
    }

    if (connector_string == "or")
    {
      if (operand->get_type() == libtocc::expr_type::CONNECTIVE)
      {
        return new libtocc::Or((libtocc::ConnectiveExpr&)*operand);
      }
      else
      {
        return new libtocc::Or((libtocc::FieldExpr&)*operand);
      }
    }

    // None of the above.
    throw InvalidParametersError("Unknown connector: Expected one of 'and', 'or', etc, found: " + connector_string);
  }

  /*
   * Parses the arguments, extracts and parse the next term in it.
   *
   * @param arguments: Arguments to be parsed.
   * @param index: Should points to where the next term begin. This method moves
   *   the index to the element after the term.
   *
   * @return: Equivalent expression of the term.
   */
  libtocc::ConnectiveExpr* extract_next_term(std::vector<std::string>& arguments, int& index)
  {
    std::pair<std::string, libtocc::ConnectiveExpr*> last_connector;
    libtocc::ConnectiveExpr* result;

    // The first argument must be an operand.
    libtocc::Expr* first_operand = extract_next_operand(arguments, index);
    // Auto releasing pointer.
    ExprPointerHolder expr_pointer_holder(first_operand);

    if (index >= arguments.size())
    {
      // This term only had one operand. We add it to the default connector.
      return make_connector("and", first_operand);
    }

    // Next one should be a connector.
    // Everything comes next will be added to this connector. So this is the
    // result (root connector) of this method.
    result = make_connector(arguments[index], first_operand);
    last_connector =
        std::make_pair(arguments[index],
                       result);
    index++;

    // Then, one operand and one operator, until the end.
    while (true)
    {
      if (index >= arguments.size())
      {
        throw InvalidParametersError("Expected an operand, but reached end of file.");
      }

      libtocc::Expr* operand = extract_next_operand(arguments, index);
      // Auto release this pointer.
      expr_pointer_holder.add(operand);

      if (index >= arguments.size())
      {
        // End of the string. Adding the operand to the previous operator.
        if (operand->get_type() == libtocc::expr_type::CONNECTIVE)
        {
          last_connector.second->add((libtocc::ConnectiveExpr&)*operand);
        }
        else
        {
          last_connector.second->add((libtocc::FieldExpr&)*operand);
        }

        // Ending the loop.
        break;
      }

      if (arguments[index] == last_connector.first)
      {
        // It's same as the previous operator. No need to create a new one.
        if (operand->get_type() == libtocc::expr_type::CONNECTIVE)
        {
          last_connector.second->add((libtocc::ConnectiveExpr&)*operand);
        }
        else
        {
          last_connector.second->add((libtocc::FieldExpr&)*operand);
        }
        index++;
      }
      else
      {
        // Making a new connector and add it to the previous one.
        libtocc::ConnectiveExpr* new_connector = make_connector(arguments[index], operand);
        // Auto release pointer.
        expr_pointer_holder.add(new_connector);

        last_connector.second->add((libtocc::ConnectiveExpr&)*new_connector);
        last_connector =
            std::make_pair(arguments[index],
                           new_connector);
      }
    }

    return result;
  }

  QuerySelector::QuerySelector(libtocc::Manager* manager)
  {
    this->libtocc_manager = manager;
  }

  QuerySelector::~QuerySelector()
  {
  }

  std::string QuerySelector::get_short_form()
  {
    return "-q";
  }

  std::string QuerySelector::get_long_form()
  {
    return "--query";
  }

  std::string QuerySelector::get_help_text()
  {
    return "-q, --query=QUERY\tQuery files using the built-in query language.\n"\
           "                 \tSee the documentations for usage.";
  }

  std::vector<libtocc::FileInfo> QuerySelector::execute(std::vector<std::string> cmd_arguments)
  {
    if (cmd_arguments.size() == 0)
    {
      throw InvalidParametersError("--query must have at least one argument.");
    }

    int index = 0;

    libtocc::ConnectiveExpr* main_expr = extract_next_term(cmd_arguments, index);
    // Auto releasing pointer.
    ExprPointerHolder holder(main_expr);

    libtocc::Query query(*main_expr);

    libtocc::FileInfoCollection founded_files = this->libtocc_manager->search_files(query);

    // Converting collection to vector.
    std::vector<libtocc::FileInfo> result;
    libtocc::FileInfoCollection::Iterator iterator(&founded_files);
    for (; !iterator.is_finished(); iterator.next())
    {
      result.push_back(*iterator.get());
    }

    return result;
  }

}
