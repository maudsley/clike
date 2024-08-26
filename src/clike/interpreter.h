#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__

/* apply constant folding to evaluate AST nodes */

#include "ast.h"
#include "binary_evaluator.h"
#include "external_variables.h"

namespace clike {

class interpreter_exception : public std::exception {
public:
};

class interpreter {
public:

  typedef std::shared_ptr<interpreter> ref;

  interpreter(const syntax_tree::ref& ast, const type_system::ref& types) : ast_(ast), type_system_(types) {
  }

  /* expose global constants to the language */
  void set_external_variables(const external_variables::ref &globals) {
    global_scope_ = std::make_shared<scope_container>();
    for (ast_var::ref global_var : globals->all_vars()) {
      global_scope_->define_var(global_var, globals->value(global_var));
    }
  }

  std::vector<location_error> interpreter_errors() {
    return errors_;
  }

  syntax_tree::ref tree() const {
    return ast_;
  }

  ast_expression::ref run(const std::string& function_name, const std::vector<constant_value::ref>& parameters) {
    if (!ast_) {
      return nullptr;
    }

    /* convention is for the caller to prepare the "stack" of the callee. */
    /* this way, after the function returns, the callee scope can still be accessed. */
    /* the caller can copy the return value out of the callee scope before releasing it. */
    scope_.clear();
    scope_.push_back(std::make_shared<scope_container>());

    ast_function::ref function = ast_->find_function_definition(function_name);
    if (!function) {
      std::stringstream error_msg;
      error_msg << "entry point '" << function_name << "' not defined";
      errors_.push_back(location_error(error_msg.str(), location()));
      throw interpreter_exception();
    }

    if (function->parameters_.size() != parameters.size()) {
      std::stringstream error_msg;
      error_msg << "function '" << function_name << "' requires " << function->parameters_.size();
      error_msg << " parameters but " << parameters.size() << " provided";
      errors_.push_back(location_error(error_msg.str(), function->loc()));
      throw interpreter_exception();
    }

    std::vector<ast_expression::ref> arguments;
    for (size_t i = 0; i < parameters.size(); ++i) {
      std::stringstream ss;
      ss << "_arg" << i; /* reserved name for entry point arguments */
      ast_var::ref var = std::make_shared<ast_var>(function->parameters_[i]->type(), ss.str());
      scope_.back()->define_var(var, parameters[i]);
      arguments.push_back(var);
    }

    evaluate_function(function, arguments);

    if (!errors_.empty()) {
      throw interpreter_exception();
    }

    return function->retval_var_;
  }

  void initialize_scope(const ast_scope::ref& scope) {
    for (auto map_item : scope->declarations_) {
      ast_var::ref local_var = std::make_shared<ast_var>(*map_item.second);
      constant_value::ref initial_value;
      if (local_var->is_struct() || local_var->is_array()) {
        initial_value = std::make_shared<constant_struct_array>();
      } else {
        initial_value = type_system_->uninitialized_value(local_var->type_name());
      }
      if (!initial_value) {
        std::stringstream error_msg;
        error_msg << "typed '" << local_var->type_name() << "' not found";
        errors_.push_back(location_error(error_msg.str(), local_var->loc()));
        throw interpreter_exception();
      }
      scope_.back()->define_var(local_var, initial_value);
    }
  }

  void evaluate_function(const ast_function::ref& function, const std::vector<ast_expression::ref>& parameters) {
    if (function->parameters_.size() != parameters.size()) {
      std::stringstream error_msg;
      error_msg << "function parameter count does not match";
      errors_.push_back(location_error(error_msg.str(), function->loc()));
      throw interpreter_exception();
    }

    initialize_scope(function);

    for (size_t i = 0; i < parameters.size(); ++i) {
      ast_expression::ref parameter_var = scope_.back()->find_var(function->parameters_[i]->name());
      if (!parameter_var) {
        std::stringstream error_msg;
        error_msg << "parameter was not declared";
        errors_.push_back(location_error(error_msg.str(), function->parameters_[i]->loc()));
        throw interpreter_exception();
      }
      copy_value(parameter_var, parameters[i], function->loc());
    }

    scope_.back()->set_type(scope_is_closed);

    for (ast_statement::ref statement : function->statements_) {
      ast_statement::ref ret_statement = evaluate_statement(statement);
      if (std::dynamic_pointer_cast<ast_return>(ret_statement)) {
        return;
      } else if (std::dynamic_pointer_cast<ast_continue>(ret_statement)) {
        std::stringstream error_msg;
        error_msg << "invalid use of statement";
        errors_.push_back(location_error(error_msg.str(), ret_statement->loc()));
      } else if (std::dynamic_pointer_cast<ast_break>(ret_statement)) {
        std::stringstream error_msg;
        error_msg << "invalid use of statement";
        errors_.push_back(location_error(error_msg.str(), ret_statement->loc()));
      }
    }

    std::stringstream error_msg;
    error_msg << "function '" << function->name() << "' is missing a return statement";
    errors_.push_back(location_error(error_msg.str(), function->loc()));
  }

  /* todo: try to remove early-outs from this function */
  ast_statement::ref evaluate_statement(const ast_statement::ref& statement) {
    if (std::dynamic_pointer_cast<ast_return>(statement)) {
      ast_return::ref ret_statement = std::dynamic_pointer_cast<ast_return>(statement);
      evaluate_expression(ret_statement->expression_);
      return statement;
    } else if (std::dynamic_pointer_cast<ast_continue>(statement)) {
      return statement;
    } else if (std::dynamic_pointer_cast<ast_break>(statement)) {
      return statement;
    } else if (std::dynamic_pointer_cast<ast_loop>(statement)) {
      ast_loop::ref loop = std::dynamic_pointer_cast<ast_loop>(statement);

      while (true) {
        scope_.push_back(std::make_shared<scope_container>());

        if (loop->condition_first_) {
          constant_value::ref cond = read_value(evaluate_expression(loop->condition_first_));
          size_t cond_value = 0;
          if (!cond->get_numeric_value(&cond_value)) {
            std::stringstream error_msg;
            error_msg << "loop condition does not evaluate to integer";
            errors_.push_back(location_error(error_msg.str(), loop->loc()));
            throw interpreter_exception();
          }
          if (!cond_value) {
            scope_.pop_back();
            break;
          }
        }

        initialize_scope(loop);

        ast_statement::ref ret_statement;
        for (ast_statement::ref loop_statement : loop->statements_) {
          ret_statement = evaluate_statement(loop_statement);
          if (ret_statement) {
            break;
          }
        }

        if (std::dynamic_pointer_cast<ast_return>(ret_statement)) {
          return ret_statement;
        }

        if (std::dynamic_pointer_cast<ast_break>(ret_statement)) {
          scope_.pop_back();
          break;
        }

        /* continue */
        if (loop->increment_) {
          evaluate_expression(loop->increment_);
        }

        if (loop->condition_last_) {
          constant_value::ref cond = read_value(evaluate_expression(loop->condition_last_));
          size_t cond_value = 0;
          if (!cond->get_numeric_value(&cond_value)) {
            std::stringstream error_msg;
            error_msg << "loop condition does not evaluate to integer";
            errors_.push_back(location_error(error_msg.str(), loop->loc()));
            throw interpreter_exception();
          }
          if (!cond_value) {
            scope_.pop_back();
            break;
          }
        }

        scope_.pop_back();
      }

    } else if (std::dynamic_pointer_cast<ast_conditional_branch>(statement)) {
      ast_conditional_branch::ref branch = std::dynamic_pointer_cast<ast_conditional_branch>(statement);

      constant_value::ref cond = read_value(evaluate_expression(branch->condition_));
      size_t cond_value = 0;
      if (!cond->get_numeric_value(&cond_value)) {
        std::stringstream error_msg;
        error_msg << "branch condition does not evaluate to integer";
        errors_.push_back(location_error(error_msg.str(), branch->loc()));
        throw interpreter_exception();
      }

      if (cond_value) {
        scope_.push_back(std::make_shared<scope_container>());
        initialize_scope(branch->true_path_);
        for (ast_statement::ref branch_statement : branch->true_path_->statements_) {
          ast_statement::ref ret_statement = evaluate_statement(branch_statement);
          if (ret_statement) {
            if (!std::dynamic_pointer_cast<ast_return>(ret_statement)) {
              scope_.pop_back();
            }
            return ret_statement;
          }
        }
        scope_.pop_back();
      } else if (branch->false_path_) {
        scope_.push_back(std::make_shared<scope_container>());
        initialize_scope(branch->false_path_);
        for (ast_statement::ref branch_statement : branch->false_path_->statements_) {
          ast_statement::ref ret_statement = evaluate_statement(branch_statement);
          if (ret_statement) {
            if (!std::dynamic_pointer_cast<ast_return>(ret_statement)) {
              scope_.pop_back();
            }
            return ret_statement;
          }
        }
        scope_.pop_back();
      }

    } else if (std::dynamic_pointer_cast<ast_switch>(statement)) {

      ast_switch::ref select = std::dynamic_pointer_cast<ast_switch>(statement);

      constant_value::ref expr = read_value(evaluate_expression(select->expression_));
      size_t expr_value = 0;
      if (!expr->get_numeric_value(&expr_value)) {
        std::stringstream error_msg;
        error_msg << "switch condition does not evaluate to integer";
        errors_.push_back(location_error(error_msg.str(), statement->loc()));
        throw interpreter_exception();
      }

      scope_.push_back(std::make_shared<scope_container>());
      initialize_scope(select);

      size_t case_index = 0;

      auto map_item = select->cases_.find(expr_value);
      if (map_item != std::end(select->cases_)) {
        case_index = map_item->second;
      } else {
        case_index = *select->default_case_;
      }

      ast_statement::ref ret_statement;
      for (size_t i = case_index; i < select->statements_.size(); ++i) {
        ret_statement = evaluate_statement(select->statements_[i]);
        if (ret_statement) {
          break; /* return or break */
        }
      }

      if (std::dynamic_pointer_cast<ast_return>(ret_statement)) {
        return ret_statement;
      }

      scope_.pop_back();

    } else if (std::dynamic_pointer_cast<ast_scope>(statement)) {
      /* an anonymous scope with temporary declarations contained in braces */
      ast_scope::ref scope = std::dynamic_pointer_cast<ast_scope>(statement);
      scope_.push_back(std::make_shared<scope_container>());
      initialize_scope(scope);
      for (ast_statement::ref statement : scope->statements_) {
        ast_statement::ref ret_statement = evaluate_statement(statement);
        if (ret_statement) {
          if (!std::dynamic_pointer_cast<ast_return>(ret_statement)) {
            scope_.pop_back();
          }
          return ret_statement;
        }
      }
      scope_.pop_back();
    } else if (std::dynamic_pointer_cast<ast_expression>(statement)) {
      evaluate_expression(std::dynamic_pointer_cast<ast_expression>(statement));
    } else {
      std::stringstream error_msg;
      error_msg << "statement cannot be evaluated";
      errors_.push_back(location_error(error_msg.str(), statement->loc()));
      throw interpreter_exception();
    }
    return nullptr;
  }

  ast_expression::ref evaluate_expression(const ast_expression::ref& initial_expr) {
    std::vector<ast_expression::ref> stack;
    stack.push_back(initial_expr);
    while (!stack.empty()) {
      ast_expression::ref top = stack.back();
      stack.pop_back();

      /* evaluate any sub-expressions first */
      if (!have_all_values(top->sub_expressions())) {
        schedule_expression_evaluation(stack, top);
        continue;
      }

      /* evaluate the expression itself */
      if (std::dynamic_pointer_cast<ast_constant>(top)) {
        ast_constant::ref op = std::dynamic_pointer_cast<ast_constant>(top);
        write_value(top, op->value());
      } else if (std::dynamic_pointer_cast<ast_var>(top)) {
        ast_var::ref scope_var = find_var(std::dynamic_pointer_cast<ast_var>(top)->name());
        if (!scope_var) {
          std::stringstream error_msg;
          error_msg << "use of undeclared variable";
          errors_.push_back(location_error(error_msg.str(), top->loc()));
          throw interpreter_exception();
        }
        write_value(top, read_value(scope_var));
      } else if (std::dynamic_pointer_cast<ast_unary_arith_negate>(top)) {
        ast_unary_arith_negate::ref op = std::dynamic_pointer_cast<ast_unary_arith_negate>(top);
        constant_value::ref value = read_value(op->expression_);
        write_value(op, value->unary_arith_negate());
      } else if (std::dynamic_pointer_cast<ast_unary_bitwise_negate>(top)) {
        ast_unary_bitwise_negate::ref op = std::dynamic_pointer_cast<ast_unary_bitwise_negate>(top);
        constant_value::ref value = read_value(op->expression_);
        write_value(op, value->unary_bitwise_negate());
      } else if (std::dynamic_pointer_cast<ast_unary_logical_negate>(top)) {
        ast_unary_logical_negate::ref op = std::dynamic_pointer_cast<ast_unary_logical_negate>(top);
        constant_value::ref value = read_value(op->expression_);
        write_value(op, value->unary_logical_negate());
      } else if (std::dynamic_pointer_cast<ast_ternary>(top)) {
        ast_ternary::ref op = std::dynamic_pointer_cast<ast_ternary>(top);
        constant_value::ref value = read_value(op->condition_);
        size_t cond_value = 0;
        if (!value->get_numeric_value(&cond_value)) {
          std::stringstream error_msg;
          error_msg << "ternary conditional is not integral";
          errors_.push_back(location_error(error_msg.str(), top->loc()));
          throw interpreter_exception();
        }
        if (cond_value) {
          evaluate_expression(op->true_expression_); /* evaluate the true side of the expression only */
          copy_value(op, op->true_expression_, op->true_expression_->loc());
        } else {
          evaluate_expression(op->false_expression_); /* evaluate the false side of the expression only */
          copy_value(op, op->false_expression_, op->false_expression_->loc());
        }
      } else if (std::dynamic_pointer_cast<ast_binary_logical_or>(top)) {
        ast_binary::ref op = std::dynamic_pointer_cast<ast_binary_logical_or>(top);
        constant_value::ref value = read_value(op->lhs());
        size_t lhs_value = 0;
        if (!value->get_numeric_value(&lhs_value)) {
          std::stringstream error_msg;
          error_msg << "logical operand is not integral";
          errors_.push_back(location_error(error_msg.str(), top->loc()));
          throw interpreter_exception();
        }
        if (!lhs_value) { /* short-circuit evaluation */
          evaluate_expression(op->rhs());
          value = read_value(op->rhs());
        }
        write_value(op, value->unary_logical_value());
      } else if (std::dynamic_pointer_cast<ast_binary_logical_and>(top)) {
        ast_binary::ref op = std::dynamic_pointer_cast<ast_binary_logical_and>(top);
        constant_value::ref value = read_value(op->lhs());
        size_t lhs_value = 0;
        if (!value->get_numeric_value(&lhs_value)) {
          std::stringstream error_msg;
          error_msg << "logical operand is not integral";
          errors_.push_back(location_error(error_msg.str(), top->loc()));
          throw interpreter_exception();
        }
        if (lhs_value) { /* short-circuit evaluation */
          evaluate_expression(op->rhs());
          value = read_value(op->rhs());
        }
        write_value(op, value->unary_logical_value());
      } else if (std::dynamic_pointer_cast<ast_assignment>(top)) {
        ast_binary::ref op = std::dynamic_pointer_cast<ast_assignment>(top);
        copy_value(op->lhs(), op->rhs(), op->loc()); /* side effect */
        copy_value(op, op->lhs(), op->loc()); /* result expr */
      } else if (std::dynamic_pointer_cast<ast_array_subscript>(top)) {
        ast_array_subscript::ref op = std::dynamic_pointer_cast<ast_array_subscript>(top);
        ast_expression::ref var = resolve_var(op);
        write_value(op, read_value(var));
      } else if (std::dynamic_pointer_cast<ast_binary>(top)) { /* all other binary operators */
        ast_binary::ref op = std::dynamic_pointer_cast<ast_binary>(top);
        constant_value::ref lhs_value = read_value(op->lhs());
        constant_value::ref rhs_value = read_value(op->rhs());
        binary_evaluator binary_op(type_system_, op);
        binary_op.evaluate(op->lhs()->type(), lhs_value, op->rhs()->type(), rhs_value);
        if (binary_op.result() != binary_evaluator::result_ok) {
          if (binary_op.result() == binary_evaluator::result_error_zero_divide) {
            std::stringstream error_msg;
            error_msg << "division by zero";
            errors_.push_back(location_error(error_msg.str(), op->loc()));
            throw interpreter_exception();
          } else { /* generic error */
            std::stringstream error_msg;
            error_msg << "failed to evaluate binary operator";
            errors_.push_back(location_error(error_msg.str(), op->loc()));
            throw interpreter_exception();
          }
        }
        write_value(op, binary_op.result_value());
      } else if (std::dynamic_pointer_cast<ast_struct_access>(top)) {
        ast_struct_access::ref op = std::dynamic_pointer_cast<ast_struct_access>(top);
        ast_expression::ref var = resolve_var(top);
        write_value(top, read_value(var));
      } else if (std::dynamic_pointer_cast<ast_sequence>(top)) {
        ast_sequence::ref seq = std::dynamic_pointer_cast<ast_sequence>(top);
        constant_value::ref seq_value = read_value(seq->expressions_.back());
        write_value(seq, seq_value);
      } else if (std::dynamic_pointer_cast<ast_function_call>(top)) {
        ast_function_call::ref call = std::dynamic_pointer_cast<ast_function_call>(top);

        scope_.push_back(std::make_shared<scope_container>());
        const size_t new_scope_index = scope_.size() - 1;

        evaluate_function(call->function_, call->args_);

        scope_[new_scope_index]->set_type(scope_is_open);

        copy_value(call->retval_var_, call->function_->retval_var_, call->loc());

        scope_.erase(std::begin(scope_) + new_scope_index, std::end(scope_));

        copy_value(call, call->retval_var_, call->loc());
      } else if (std::dynamic_pointer_cast<ast_type_constructor>(top)) {
        ast_type_constructor::ref constructor = std::dynamic_pointer_cast<ast_type_constructor>(top);
        std::vector<constant_value::ref> args;
        for (ast_expression::ref arg : constructor->args_) {
          args.push_back(read_value(arg));
        }
        constant_value::ref new_object = type_system_->construct_value(constructor->type_name(), args);
        if (!new_object) { /* report and error recovery */
          std::stringstream error_msg;
          error_msg << "construction of '" << constructor->type_name() << "' not possible with provided arguments";
          errors_.push_back(location_error(error_msg.str(), constructor->loc()));
          new_object = type_system_->uninitialized_value(constructor->type_name());
          if (!new_object) {
            throw interpreter_exception(); /* type checking is handled elsewhere */
          }
        }
        write_value(constructor, new_object);
      } else {
        std::stringstream error_msg;
        error_msg << "expression cannot be evaluated";
        errors_.push_back(location_error(error_msg.str(), top->loc()));
        throw interpreter_exception();
      }
    }
    return initial_expr;
  }

  /* traverse the tree down left-hand branches until ast_var or ast_constant is found */
  ast_expression::ref resolve_var(const ast_expression::ref& initial_var) {
    ast_expression::ref node = initial_var;
    std::vector<size_t> indices;
    std::vector<std::string> field_names;
    while (!std::dynamic_pointer_cast<ast_var>(node)) {
      if (std::dynamic_pointer_cast<ast_assignment>(node)) {
        ast_assignment::ref op = std::dynamic_pointer_cast<ast_assignment>(node);
        node = op->lhs(); /* redirect resolution to the left-hand-side of the assignment */
      } else if (std::dynamic_pointer_cast<ast_sequence>(node)) {
        ast_sequence::ref op = std::dynamic_pointer_cast<ast_sequence>(node);
        node = op->expressions_.back(); /* redirect resolution to the right-most element of the sequence */
      } else if (std::dynamic_pointer_cast<ast_array_subscript>(node)) {
        ast_array_subscript::ref op = std::dynamic_pointer_cast<ast_array_subscript>(node);
        constant_value::ref array_index = read_value(op->rhs());
        if (!array_index) {
          std::stringstream error_msg;
          error_msg << "array index does not evaluate to an integer";
          errors_.push_back(location_error(error_msg.str(), initial_var->loc()));
          throw interpreter_exception();
        }
        size_t array_index_value = 0;
        if (!array_index->get_numeric_value(&array_index_value)) {
          std::stringstream error_msg;
          error_msg << "array index is not of integral type";
          errors_.push_back(location_error(error_msg.str(), initial_var->loc()));
          throw interpreter_exception();
        }
        indices.push_back(array_index_value);
        field_names.push_back(std::string()); /* null pad */
        node = op->lhs();
      } else if (std::dynamic_pointer_cast<ast_struct_access>(node)) {
        ast_struct_access::ref op = std::dynamic_pointer_cast<ast_struct_access>(node);
        indices.push_back(0); /* zero pad */
        field_names.push_back(op->field_->name());
        node = op->object_;
      } else if (std::dynamic_pointer_cast<ast_function_call>(node)) {
        ast_function_call::ref op = std::dynamic_pointer_cast<ast_function_call>(node);
        /* ast_function_call retval_var_ is required because we need a concrete value to reference */
        node = op->retval_var_; /* for example: x=func().field or x=func()[i] */
      } else {
        break;
      }
    }

    /* these are added in reverse order */
    std::reverse(std::begin(indices), std::end(indices));
    std::reverse(std::begin(field_names), std::end(field_names));

    ast_var::ref var = std::dynamic_pointer_cast<ast_var>(node);
    if (!var) {
      /* fine, as long as didn't try to use array subscript on an invalid expression */
      if (!indices.empty()) {
        std::stringstream error_msg;
        error_msg << "expression does not evaluate to an array";
        errors_.push_back(location_error(error_msg.str(), node->loc()));
        throw interpreter_exception();
      }
      return node;
    }

    ast_type::ref type = var->type();
    size_t indices_processed = 0;
    size_t array_index_count = 0;
    std::stringstream ss;
    ss << var->name();
    for (size_t i = 0; i < field_names.size(); ++i) { /* sanity check object access and construct object name string */
      if (!field_names[i].empty()) { /* two arrays of equal length. an empty field string means array access instead */
        if (!type->struct_type()) {
          errors_.push_back(location_error("object is not a struct", initial_var->loc()));
          throw interpreter_exception();
        }
        if (type->array_type()) { /* array access takes precedence over struct */
          errors_.push_back(location_error("object is not a struct", initial_var->loc()));
          throw interpreter_exception();
        }
        ast_var::ref field_declaration = type->struct_type()->find(field_names[i]);
        if (!field_declaration) {
          errors_.push_back(location_error("tried to access invalid struct field", initial_var->loc()));
          throw interpreter_exception();
        }
        type = field_declaration->type();
        if (!type) {
          errors_.push_back(location_error("struct member declaration with no type", initial_var->loc()));
          throw interpreter_exception();
        }
        ss << "." << field_names[i];
      } else {
        if (!type->array_type()) { /* this might be OK, if the type is a externally defined array */
          if (type->struct_type()) {
            errors_.push_back(location_error("object is not an array", initial_var->loc()));
            throw interpreter_exception();
          } else {
            break; /* there will be indices left over that should be turned into external object access */
          }
        }
        if (array_index_count >= type->array_type()->sizes_.size()) {
          errors_.push_back(location_error("too many array operators", initial_var->loc()));
          throw interpreter_exception();
        }
        if (indices[i] >= type->array_type()->sizes_[array_index_count]) {
          errors_.push_back(location_error("array access out of bounds", initial_var->loc()));
          throw interpreter_exception();
        }
        array_index_count++;
        if (array_index_count == type->array_type()->sizes_.size()) {
          array_index_count = 0; /* reached the end of this array */
          type = type->array_type()->element_type(); /* possibly a nested type */
        }
        ss << "[" << indices[i] << "]";
      }
      indices_processed++;
    }

    ast_var::ref element_var = find_var(ss.str());
    if (!element_var) {
      std::stringstream error_msg;
      error_msg << "variable '" << ss.str() << "' not found in scope";
      errors_.push_back(location_error(error_msg.str(), initial_var->loc()));
      throw interpreter_exception();
    }

    /* some indices left over */
    indices.erase(std::begin(indices), std::begin(indices) + indices_processed);
    if (!indices.empty()) { /* it's not an array, but trying to access it like an array */
      std::string array_element_type = type_system_->array_type_name(element_var->type_name());
      ast_type::ref element_type = std::make_shared<ast_type>(array_element_type);
      for (size_t i = 1; i < indices.size(); ++i) { /* need to find the final type */
        array_element_type = type_system_->array_type_name(array_element_type);
        element_type = std::make_shared<ast_type>(array_element_type);
      }
      if (element_type) { /* the object array access is handled by the external type system */
        return std::make_shared<ast_var_ptr>(element_type, ss.str(), element_var, indices);
      } else {
        std::stringstream error_msg;
        error_msg << "object '" << element_var->name() << "' of type '" << element_var->type_name() << "' is not array";
        errors_.push_back(location_error(error_msg.str(), initial_var->loc()));
        throw interpreter_exception();
      }
    }

    return element_var;
  }

  enum scope_type {
    scope_is_open, /* enable visibility of vars outside of scope */
    scope_is_closed /* block visibility */
  };

  class scope_container {
  public:
    typedef std::shared_ptr<scope_container> ref;
    scope_container() : type_(scope_is_open) {
    }

    scope_type type() const {
      return type_;
    }

    void set_type(const scope_type type) {
      type_ = type;
    }

    void define_var(const ast_var::ref& var, const constant_value::ref& initial_value) {
      scope_[var->name()] = var;
      write_value(var, initial_value);
    }

    bool have_value(const ast_expression::ref& expr) const {
      return (values_.find(expr) != std::end(values_));
    }

    ast_var::ref find_var(const std::string& name) {
      auto map_item = scope_.find(name);
      if (map_item == std::end(scope_)) {
        return nullptr;
      } else {
        return map_item->second;
      }
    }

    void write_value(const ast_expression::ref& expr, const constant_value::ref& value) {
      ast_var_ptr::ref ptr = std::dynamic_pointer_cast<ast_var_ptr>(expr);
      if (!ptr) {
        values_[expr] = value; /* normal direct access behaviour */
      } else { /* have a pointer */
        auto map_item = values_.find(ptr->object()); /* lookup the container for this array element */
        if (map_item == std::end(values_)) {
          throw interpreter_exception();
        } else {
          map_item->second->write_array_element(ptr->indices(), value);
        }
      }
    }

    constant_value::ref read_value(const ast_expression::ref& expr) const {
      auto map_item = values_.find(expr);
      if (map_item == std::end(values_)) {
        return nullptr; /* handle the error in a more specific way in the caller */
      } else {
        return map_item->second; /* normal direct access behaviour */
      }
    }

    std::map<std::string, ast_var::ref> scope_;
    std::map<ast_expression::ref, constant_value::ref> values_;
    scope_type type_;
  };

  bool have_value(const ast_expression::ref& expr) const {
    for (size_t i = 0; i < scope_.size(); ++i) {
      size_t j = scope_.size() - i - 1;
      if (scope_[j]->have_value(expr)) {
        return true;
      }
      if (scope_[j]->type() == scope_is_closed) {
        break; /* cannot search outside function scope */
      }
    }
    return false;
  }

  bool have_all_values(const std::vector<ast_expression::ref>& expressions) const {
    bool have_all = true;
    for (const ast_expression::ref& expr : expressions) {
      if (!have_value(expr)) {
        have_all = false;
        break;
      }
    }
    return have_all;
  }

  void schedule_expression_evaluation(std::vector<ast_expression::ref>& stack, const ast_expression::ref& expr) {
    stack.push_back(expr); /* revisit the expression itself */
    std::vector<ast_expression::ref> sub_expressions = expr->sub_expressions();
    std::reverse(std::begin(sub_expressions), std::end(sub_expressions)); /* we process the last (highest precedence) stack item first */
    stack.insert(std::end(stack), std::begin(sub_expressions), std::end(sub_expressions)); /* visit these child expressions */
  }

  ast_var::ref find_var(const std::string& var_name) const {
    ast_var::ref var;
    for (size_t i = 0; i < scope_.size(); ++i) {
      size_t j = scope_.size() - i - 1;
      var = scope_[j]->find_var(var_name);
      if (var || (scope_[j]->type() == scope_is_closed)) {
        break; /* cannot search outside function scope */
      }
    }
    if (!var && global_scope_) {
      var = global_scope_->find_var(var_name); /* still not found? check globals */
    }
    return var;
  }

  void write_value(const ast_expression::ref& expr, const constant_value::ref& value) {
    if (!value) {
      errors_.push_back(location_error("empty value during write operation", expr->loc()));
      throw interpreter_exception();
    }
    ast_expression::ref dest_expr = expr;
    ast_var_ptr::ref ptr = std::dynamic_pointer_cast<ast_var_ptr>(expr);
    if (ptr) { /* redirect the write to the pointer target */
      dest_expr = ptr->object();
    }
    scope_container::ref dest_scope = scope_.back(); /* write to the inner-most scope by default */
    for (size_t i = 0; i < scope_.size(); ++i) {
      size_t j = scope_.size() - i - 1;
      if (scope_[j]->have_value(dest_expr)) {
        dest_scope = scope_[j];
        break;
      }
      if (scope_[j]->type() == scope_is_closed) {
        break; /* cannot search outside function scope */
      }
    }
    dest_scope->write_value(expr, value);
  }

  constant_value::ref read_value(const ast_expression::ref& expr) const {
    ast_expression::ref src_expr = expr;
    ast_var_ptr::ref ptr = std::dynamic_pointer_cast<ast_var_ptr>(expr);
    if (ptr) { /* redirect the read to the pointer target */
      src_expr = ptr->object();
    }
    constant_value::ref value;
    for (size_t i = 0; i < scope_.size(); ++i) {
      size_t j = scope_.size() - i - 1;
      value = scope_[j]->read_value(src_expr);
      if (value || (scope_[j]->type() == scope_is_closed)) {
        break; /* cannot search outside function scope */
      }
    }
    if (ptr) { /* redirect read to an array element */
      value = value->read_array_element(ptr->indices());
    }
    if (!value && global_scope_) {
      value = global_scope_->read_value(expr); /* still not found? check globals */
    }
    return value;
  }

  /* combination of read_value followed by write_value that handles structures and arrays */
  void copy_value(const ast_expression::ref& dest_expr, const ast_expression::ref& src_expr, const location& loc) {
    ast_expression::ref dest_resolved = resolve_var(dest_expr);
    ast_expression::ref src_resolved = resolve_var(src_expr);

    constant_value::ref src_value = read_value(src_resolved);

    /* incompatible types? try to cast implicitly */
    if (dest_expr->type_name() != src_expr->type_name()) {
      src_value = type_system_->implicit_cast_value(dest_expr->type_name(), src_value);
      if (!src_value) {
        errors_.push_back(location_error("failed to cast during assignment", loc));
        throw interpreter_exception();
      }
    }

    /* handle external type assignment */
    ast_var_ptr::ref dest_ptr = std::dynamic_pointer_cast<ast_var_ptr>(dest_resolved);
    if (dest_ptr) {
      write_value(dest_resolved, src_value);
      if (dest_expr != dest_resolved) {
        write_value(dest_expr, src_value);
      }
      return;
    }

    /* scalar assignment to expr */
    ast_var::ref dest_var = std::dynamic_pointer_cast<ast_var>(dest_resolved);
    if (!dest_var) {
      write_value(dest_resolved, src_value);
      if (dest_expr != dest_resolved) {
        write_value(dest_expr, src_value);
      }
      return;
    }

    ast_type::ref dest_type = dest_var->type();
    ast_type::ref src_type = src_expr->type();

    if (dest_var->is_array()) {
      ast_var::ref src_var = std::dynamic_pointer_cast<ast_var>(src_resolved);
      if (!src_var) {
        errors_.push_back(location_error("right of assignment is not a valid array", loc));
        throw interpreter_exception();
      }
      if (!src_expr->is_array()) {
        errors_.push_back(location_error("tried to assign non-array type to array type", loc));
        throw interpreter_exception();
      }
      if (src_type->array_type()->element_type()->type_name() != dest_type->array_type()->element_type()->type_name()) {
        errors_.push_back(location_error("array element type error during assignment", loc));
        throw interpreter_exception();
      }
      if (src_type->array_type()->dimensions() != dest_type->array_type()->dimensions()) {
        errors_.push_back(location_error("found different array dimensions during assignment",loc));
        throw interpreter_exception();
      }
      if (src_type->array_type()->sizes_[0] != dest_type->array_type()->sizes_[0]) {
        errors_.push_back(location_error("found different array lengths during assignment", loc));
        throw interpreter_exception();
      }
      for (size_t i = 0; i < dest_type->array_type()->sizes_[0]; ++i) {
        std::stringstream src_name;
        src_name << src_var->name() << "[" << i << "]";
        ast_var::ref src_element = find_var(src_name.str());
        if (!src_element) {
          errors_.push_back(location_error("source array element not found during assignment", loc));
          throw interpreter_exception();
        }
        std::stringstream dest_name;
        dest_name << dest_var->name() << "[" << i << "]";
        ast_var::ref dest_element = find_var(dest_name.str());
        if (!dest_element) {
          errors_.push_back(location_error("destination array element not found during assignment", loc));
          throw interpreter_exception();
        }
        copy_value(dest_element, src_element, loc);
      }
    } else if (dest_var->is_struct()) {
      ast_var::ref src_var = std::dynamic_pointer_cast<ast_var>(src_resolved);
      if (!src_var) {
        errors_.push_back(location_error("assignment RHS is not a valid struct", loc));
        throw interpreter_exception();
      }
      for (auto map_item : dest_type->struct_type()->declarations_) {
        std::stringstream src_name;
        src_name << src_var->name() << "." << map_item.second->name();
        ast_var::ref src_element = find_var(src_name.str());
        if (!src_element) {
          errors_.push_back(location_error("source struct field not found during assignment", loc));
          throw interpreter_exception();
        }
        std::stringstream dest_name;
        dest_name << dest_var->name() << "." << map_item.second->name();
        ast_var::ref dest_element = find_var(dest_name.str());
        if (!dest_element) {
          errors_.push_back(location_error("destination struct field not found during assignment", loc));
          throw interpreter_exception();
        }
        copy_value(dest_element, src_element, loc);
      }
    }

    /* scalar assignment to var */
    write_value(dest_resolved, src_value);
    if (dest_expr != dest_resolved) {
      write_value(dest_expr, src_value);
    }
  }

private:

  std::vector<scope_container::ref> scope_;
  scope_container::ref global_scope_;

  syntax_tree::ref ast_;

  type_system::ref type_system_;

  std::vector<location_error> errors_;

};

} /* namespace */

#endif /* __INTERPRETER_H__ */
