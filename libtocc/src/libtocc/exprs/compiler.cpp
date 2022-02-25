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

#include "libtocc/exprs/compiler.h"

#include <list>
#include <sstream>

#include "libtocc/common/expr_exceptions.h"
#include "libtocc/exprs/compiled_expr.h"


namespace libtocc
{
  /*
   * For detail about how the compilation works, take a look at the
   * `CompilerStateMachine' diagram in the documentation.
   */

  /*
   * Keeps data of the current state.
   */
  class CompileStateData
  {
  public:
    CompileStateData(CompiledExpr* current_expression,
                     CompiledExpr* next_expression,
                     std::ostringstream* function_header_stream,
                     std::ostringstream* tags_stream,
                     std::ostringstream* fields_stream,
                     std::ostringstream* result)
    {
      this->current_expr = current_expression;
      this->next_expr = next_expression;
      this->result_counter = 1;
      this->function_header_stream = function_header_stream;
      this->tags_stream = tags_stream;
      this->fields_stream = fields_stream;
      this->result = result;
    }

    CompiledExpr* current_expr;
    CompiledExpr* next_expr;
    int result_counter;
    std::list<std::string> groups_stack;
    std::ostringstream* function_header_stream;
    std::ostringstream* tags_stream;
    std::ostringstream* fields_stream;
    std::ostringstream* result;
  };

  namespace compile_states
  {
    /*
     * Defines all the machine's states.
     */
    enum States { GROUP, END_GROUP, GROUP_AFTER_END, GROUP_AFTER_GROUP,
                  FIELD, FIELD_AFTER_GROUP,
                  FINISH};
  }

  void append_expression(CompileStateData& data)
  {
    // Appending initialization of $r variable in header.
    (*data.function_header_stream) << "$r" << data.result_counter << " = ";
    if (data.current_expr->is_negative_expr())
    {
      (*data.function_header_stream) << "true";
    }
    else
    {
      (*data.function_header_stream) << "false";
    }
    (*data.function_header_stream) << "; ";

    // Selecting which stream these codes should be put in.
    std::ostringstream* current_stream = data.fields_stream;
    if (data.current_expr->get_type() == compiled_expr::TAG)
    {
      current_stream = data.tags_stream;

      if (data.tags_stream->tellp() == 0)
      {
        // Start a loop if it wasn't start yet.
        (*data.tags_stream) << " foreach ($record.tags as $tag) {";
      }
    }

    // Making a new if for this field.
    (*current_stream) << " if (" << data.current_expr->get_value();
    (*current_stream) << ") { $r" << data.result_counter;
    (*current_stream) << " = ";

    if (data.current_expr->is_negative_expr())
    {
      (*current_stream) << "false";
    }
    else
    {
      (*current_stream) << "true";
    }

    (*current_stream) << "; }";
  }

  compile_states::States group_state_handler(CompileStateData& data)
  {
    if (data.current_expr->get_type() != compiled_expr::CONNECTIVE)
    {
      throw ExprCompilerError("We're in GROUP state, but current EXPR is not a CONNECTIVE!");
    }

    // Opening a group.
    (*data.result) << " " << data.groups_stack.back() << " (";
    // Pushing this group to stack.
    data.groups_stack.push_back(data.current_expr->get_value());

    if (data.next_expr->get_type() == compiled_expr::CONNECTIVE)
    {
      return compile_states::GROUP_AFTER_GROUP;
    }
    if (data.next_expr->get_type() == compiled_expr::END_CONNECTIVE_GROUP)
    {
      throw ExprCompilerError("An empty connective group detected.");
    }
    else if (data.next_expr->get_type() == compiled_expr::FIELD ||
             data.next_expr->get_type() == compiled_expr::TAG)
    {
      return compile_states::FIELD_AFTER_GROUP;
    }

    // If we reach here, there's nothing else to do.
    return compile_states::FINISH;
  }

  compile_states::States end_group_state_handler(CompileStateData& data)
  {
    if (data.current_expr->get_type() != compiled_expr::END_CONNECTIVE_GROUP)
    {
      throw ExprCompilerError("We're in END_GROUP state, but current EXPR is not a END_CONNECTIVE_GROUP!");
    }

    // Popping last group from stack
    data.groups_stack.pop_back();
    // Closing the group.
    (*data.result) << " )";

    if (data.next_expr->get_type() == compiled_expr::CONNECTIVE)
    {
      return compile_states::GROUP_AFTER_END;
    }
    if (data.next_expr->get_type() == compiled_expr::END_CONNECTIVE_GROUP)
    {
      return compile_states::END_GROUP;
    }
    else if (data.next_expr->get_type() == compiled_expr::FIELD ||
             data.next_expr->get_type() == compiled_expr::TAG)
    {
      return compile_states::FIELD;
    }

    // If we reach here, there's nothing else to do.
    return compile_states::FINISH;
  }

  compile_states::States group_after_end_state_handler(CompileStateData& data)
  {
    if (data.current_expr->get_type() != compiled_expr::CONNECTIVE)
    {
      throw ExprCompilerError("We're in GROUP_AFTER_END state, but current EXPR is not a CONNECTIVE!");
    }

    // Opening a group after current one.
    (*data.result) << " " << data.groups_stack.back() << " (";
    // Pushing group to stack
    data.groups_stack.push_back(data.current_expr->get_value());

    if (data.next_expr->get_type() == compiled_expr::CONNECTIVE)
    {
      return compile_states::GROUP_AFTER_GROUP;
    }
    if (data.next_expr->get_type() == compiled_expr::END_CONNECTIVE_GROUP)
    {
      throw ExprCompilerError("An empty connective group detected.");
    }
    else if (data.next_expr->get_type() == compiled_expr::FIELD ||
             data.next_expr->get_type() == compiled_expr::TAG)
    {
      return compile_states::FIELD_AFTER_GROUP;
    }

    // If we reach here, there's nothing else to do.
    return compile_states::FINISH;
  }

  compile_states::States group_after_group_state_handler(CompileStateData& data)
  {
    if (data.current_expr->get_type() != compiled_expr::CONNECTIVE)
    {
      throw ExprCompilerError("We're in GROUP_AFTER_GROUP state, but current EXPR is not a CONNECTIVE!");
    }

    // Opening a group after current one.
    (*data.result) << " (";
    // Pushing group to stack
    data.groups_stack.push_back(data.current_expr->get_value());

    if (data.next_expr->get_type() == compiled_expr::CONNECTIVE)
    {
      return compile_states::GROUP_AFTER_GROUP;
    }
    if (data.next_expr->get_type() == compiled_expr::END_CONNECTIVE_GROUP)
    {
      throw ExprCompilerError("An empty connective group detected.");
    }
    else if (data.next_expr->get_type() == compiled_expr::FIELD ||
             data.next_expr->get_type() == compiled_expr::TAG)
    {
      return compile_states::FIELD_AFTER_GROUP;
    }

    // If we reach here, there's nothing else to do.
    return compile_states::FINISH;
  }

  compile_states::States field_state_handler(CompileStateData& data)
  {
    if (data.current_expr->get_type() != compiled_expr::FIELD &&
        data.current_expr->get_type() != compiled_expr::TAG)
    {
      throw ExprCompilerError("We're in FIELD state, but current EXPR is not a FIELD or TAG!");
    }

    // Creating a new `if' for this field.
    append_expression(data);
    // Appending a new result.
    (*data.result) << " " << data.groups_stack.back() << " $r" << data.result_counter;
    // Increasing result counter.
    data.result_counter++;

    if (data.next_expr->get_type() == compiled_expr::CONNECTIVE)
    {
      return compile_states::GROUP;
    }
    if (data.next_expr->get_type() == compiled_expr::END_CONNECTIVE_GROUP)
    {
      return compile_states::END_GROUP;
    }
    else if (data.next_expr->get_type() == compiled_expr::FIELD ||
             data.next_expr->get_type() == compiled_expr::TAG)
    {
      return compile_states::FIELD;
    }

    // If we reach here, there's nothing else to do.
    return compile_states::FINISH;
  }

  compile_states::States field_after_group_state_handler(CompileStateData& data)
  {
    if (data.current_expr->get_type() != compiled_expr::FIELD &&
        data.current_expr->get_type() != compiled_expr::TAG)
    {
      throw ExprCompilerError("We're in FIELD_AFTER_GROUP state, but current EXPR is not a FIELD or TAG!");
    }

    // Creating a new `if' for this field.
    append_expression(data);
    // Appending a new result.
    (*data.result) << " $r" << data.result_counter;
    // Increasing result counter.
    data.result_counter++;

    if (data.next_expr->get_type() == compiled_expr::CONNECTIVE)
    {
      return compile_states::GROUP;
    }
    if (data.next_expr->get_type() == compiled_expr::END_CONNECTIVE_GROUP)
    {
      return compile_states::END_GROUP;
    }
    else if (data.next_expr->get_type() == compiled_expr::FIELD ||
             data.next_expr->get_type() == compiled_expr::TAG)
    {
      return compile_states::FIELD;
    }

    // If we reach here, there's nothing else to do.
    return compile_states::FINISH;
  }
  /*
   * Pointer to state handler functions.
   */
  typedef compile_states::States state_handler_func(CompileStateData& data);

  /*
   * This maps each state to a state handler.
   */
  state_handler_func* const state_table[6] =
  {
      group_state_handler,
      end_group_state_handler,
      group_after_end_state_handler,
      group_after_group_state_handler,
      field_state_handler,
      field_after_group_state_handler
  };

  std::string QueryCompiler::compile(Query& query_to_compile, std::string result_var_name)
  {
    ConnectiveExpr* expression_to_compile = query_to_compile.get_expr();

    // The final script.
    std::string script;

    // Keeps first lines of the function (mainly, result variables initialization).
    std::ostringstream function_header_stream;

    // Keeps condition of tags.
    std::ostringstream tags_stream;

    // Keeps condition of other fields.
    std::ostringstream fields_stream;

    // Keeps sequence of `$r'.
    std::ostringstream result;

    compile_states::States current_state = compile_states::GROUP_AFTER_GROUP;

    // Compiling expressions to CompiledExprs.
    std::list<CompiledExpr> compiled_list =
        expression_to_compile->compile().list;

    // Iterating over CompiledExprs to create a Jx9 script.
    std::list<CompiledExpr>::iterator iterator = compiled_list.begin();
    CompiledExpr* first_element = &*iterator;
    ++iterator;
    CompiledExpr* second_element = &*iterator;
    // Initializing data.
    CompileStateData data(first_element, second_element,
                          &function_header_stream,
                          &tags_stream, &fields_stream, &result);
    ++iterator;

    for (;iterator != compiled_list.end(); ++iterator)
    {
      current_state = state_table[current_state](data);

      data.current_expr = &*data.next_expr;
      data.next_expr = &*iterator;
    }

    // Last two elements in the list.
    current_state = state_table[current_state](data);
    // The last element.
    data.current_expr = &*data.next_expr;
    CompiledExpr nope_element = CompiledExpr(compiled_expr::NOPE, "");
    data.next_expr = &nope_element;
    current_state = state_table[current_state](data);

    // Creating filter function.
    script += "$filter_func = function($record) { ";

    // Header of the function.
    if (function_header_stream.tellp() != 0)
    {
      script += function_header_stream.str();
    }

    // Appending tags conditions, if there's any.
    if (tags_stream.tellp() != 0)
    {
      script += " " + tags_stream.str() +" }";
    }

    script += " " + fields_stream.str();
    script += " return " + result.str() + ";";
    script += " }; ";

    // Applying filter on database's records, and putting the result in the
    // result variable.
    script += "$" + result_var_name + " = db_fetch_all('files', $filter_func);";

    return script;
  }

};
