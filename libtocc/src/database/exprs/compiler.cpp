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

#include <list>
#include <sstream>

#include "common/expr_exceptions.h"
#include "database/exprs/compiler.h"
#include "database/exprs/compiled_expr.h"

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
                     std::ostringstream* tags_stream,
                     std::ostringstream* fields_stream,
                     std::ostringstream* result)
    {
      this->current_expr = current_expression;
      this->next_expr = next_expression;
      this->result_counter = 1;
      this->tags_stream = tags_stream;
      this->fields_stream = fields_stream;
      this->result = result;
    }

    CompiledExpr* current_expr;
    CompiledExpr* next_expr;
    int result_counter;
    std::list<std::string> groups_stack;
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
    if (data.current_expr->get_type() == compiled_expr::TAG)
    {
      // Start a loop if it wasn't start yet.
      if (data.tags_stream->tellp() == 0)
      {
        (*data.tags_stream) << " foreach ($record.tags as $tag) {";
      }

      // Making a new if for this tag.
      (*data.tags_stream) << " if (" << data.current_expr->get_value();
      (*data.tags_stream) << ") { $r" << data.result_counter;
      (*data.tags_stream) << " = true; }";
    }

    else if (data.current_expr->get_type() == compiled_expr::FIELD)
    {
      (*data.fields_stream) << " if (" << data.current_expr->get_value();
      (*data.fields_stream) << ") { $r" << data.result_counter;
      (*data.fields_stream) << " = true; }";
    }
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

  std::string QueryCompiler::compile(Query& query_to_compile)
  {
    ConnectiveExpr* expression_to_compile = query_to_compile.get_expr();

    // The final script.
    std::string script;

    // Keeps condition of tags.
    std::ostringstream tags_stream;

    // Keeps condition of other fields.
    std::ostringstream fields_stream;

    // Keeps sequence of `$r'.
    std::ostringstream result;

    compile_states::States current_state = compile_states::GROUP_AFTER_GROUP;

    // Compiling expressions to CompiledExprs.
    std::list<CompiledExpr> compiled_list = expression_to_compile->compile();

    // Iterating over CompiledExprs to create a Jx9 script.
    std::list<CompiledExpr>::iterator iterator = compiled_list.begin();
    CompiledExpr* first_element = &*iterator;
    ++iterator;
    CompiledExpr* second_element = &*iterator;
    // Initializing data.
    CompileStateData data(first_element, second_element,
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

    // Finalizing the script.
    script += "$filter_func = function($record) { ";
    script += " " + tags_stream.str() +" }";
    script += " " + fields_stream.str();
    script += " return " + result.str() + ";";
    script += " }; $fetched_records = db_fetch_all('files', $filter_func);";

    return script;
  }

};
