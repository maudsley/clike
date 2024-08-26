#ifndef __AST_BUILDER_H__
#define __AST_BUILDER_H__

/* build the syntax tree by calling the parser. */

#include "ast.h"
#include "binary_evaluator.h"

namespace clike {

class lexer;
class parser;

class syntax_tree_builder {
public:
  typedef std::shared_ptr<syntax_tree_builder> ref;

  syntax_tree_builder(const type_system::ref& types) : type_system_(types), next_variable_id_(0) {
  }

  /* expose global constants to the language */
  void set_external_variables(const ast_scope::ref &globals) {
    global_scope_ = globals;
  }

  bool parse(const std::string& source_string);

  bool has_errors() const {
    return !errors_.empty();
  }

  std::vector<location_error> parser_errors() {
    return errors_;
  }

  syntax_tree::ref tree() const {
    return ast_;
  }

  void not_implemented(const location& loc) {
    errors_.push_back(location_error("not implemented", loc));
    throw parser_exception();
  }

  ast_scope::ref scope() {
    if (scopes_.empty()) {
      scopes_.push_back(std::make_shared<ast_function>());
    }
    return scopes_.back();
  }

  ast_function::ref scope_function() {
    if (scopes_.empty()) {
      scopes_.push_back(std::make_shared<ast_function>());
    }
    ast_function::ref function = std::dynamic_pointer_cast<ast_function>(scopes_.front());
    if (!function) {
      throw parser_exception(); /* expected function */
    }
    return function;
  }

  ast_var::ref scope_find(const std::string& name) const {
    ast_var::ref var;
    for (size_t i = 0; i < scopes_.size(); ++i) {
      size_t j = scopes_.size() - i - 1; /* reverse iteration: search newest scope first */
      var = scopes_[j]->find(name);
      if (var) {
        break;
      }
    }
    if (!var && global_scope_) {
      var = global_scope_->find(name); /* still not found? check globals */
    }
    return var;
  }

  void struct_declaration(const location& loc, const std::string& name) {
    if (!struct_) {
      struct_ = std::make_shared<ast_type>(std::make_shared<ast_var_struct>(), name);
    }
    if (!ast_) {
      ast_ = std::make_shared<syntax_tree>();
    }
    struct_->set_loc(loc);
    ast_->structures_[struct_->type_name()] = struct_;
  }

  void struct_declaration_end() {
    struct_.reset();
  }

  void function_begin(const location& loc, const std::string& name) {
    ast_function::ref function = scope_function();
    if (!function) {
      throw std::runtime_error("Need function scope for function definition");
    }
    function->set_loc(loc);
    function->name_ = name;
    ast_type::ref return_type = std::make_shared<ast_type>(*current_type());
    return_type->set_const(true); /* prevent assignment to the return var */
    function->retval_var_ = scope_declare_temporary_var(return_type, loc);
    type_specifier_.pop_back();
  }

  void function_end() {
    if (!ast_) {
      ast_ = std::make_shared<syntax_tree>();
    }
    ast_function::ref function = scope_function();
    ast_->functions_[function->name_] = function;
    scopes_.pop_back();
  }

  void scope_begin() {
    scopes_.push_back(std::make_shared<ast_scope>());
  }

  void scope_end() {
    ast_scope::ref temp_scope = scope();
    if (!temp_scope) {
      throw std::runtime_error("Missing scope");
    }
    scopes_.pop_back();
    scope()->statements_.push_back(temp_scope);
  }

  void iteration_begin() {
    scopes_.push_back(std::make_shared<ast_scope>());
  }

  void iteration_statements(const location& loc, const bool cond_expr, const bool inc_expr) {
    ast_loop::ref loop = std::make_shared<ast_loop>();

    if (inc_expr) {
      loop->increment_ = expressions_.back();
      expressions_.pop_back();
    }

    if (cond_expr) {
      loop->condition_first_ = expressions_.back();
      expressions_.pop_back();

      if (!type_system_->is_integral_type(loop->condition_first_->type_name())) {
        std::stringstream error_msg;
        error_msg << "cannot use expression type '" << loop->condition_first_->type_name() << "' as loop condition";
        errors_.push_back(location_error(error_msg.str(), loc));
      }
    }

    scopes_.push_back(loop);
  }

  void iteration_end(const bool condition_first) {
    /* inner scope contains loop "body" */
    ast_loop::ref loop_inner = std::dynamic_pointer_cast<ast_loop>(scope());
    if (!loop_inner) {
      throw std::runtime_error("Need loop scope for iteration statement definition");
    }
    scopes_.pop_back();

    if (!condition_first) { /* do-while loop */
      std::swap(loop_inner->condition_first_, loop_inner->condition_last_);
      /* the do-while statements were placed in the outer scope. move them to the inner scope. */
      std::swap(loop_inner->statements_, scope()->statements_);
    }

    scope()->statements_.push_back(loop_inner);

    /* outer scope contains the loop initialization statement and it's variable declarations */
    ast_scope::ref loop_outer = scope();
    if (!loop_outer) {
      throw std::runtime_error("Need loop scope for iteration statement definition");
    }
    scopes_.pop_back();
    scope()->statements_.push_back(loop_outer);
  }

  void conditional_begin(const location& loc, const location& cond_loc) {
    ast_conditional_branch::ref branch = std::make_shared<ast_conditional_branch>();
    branch->set_loc(loc);
    branch->condition_ = expressions_.back();
    expressions_.pop_back();

    if (!type_system_->is_integral_type(branch->condition_->type_name())) {
      std::stringstream error_msg;
      error_msg << "cannot use expression type '" << branch->condition_->type_name() << "' as condition";
      errors_.push_back(location_error(error_msg.str(), cond_loc));
    }

    scope()->statements_.push_back(branch);
    scopes_.push_back(std::make_shared<ast_scope>());
  }

  void conditional_else() {
    scopes_.push_back(std::make_shared<ast_scope>());
  }

  void conditional_end(const bool has_else) {
    ast_scope::ref false_path;
    if (has_else) {
      false_path = scopes_.back();
      scopes_.pop_back();
    }
    ast_scope::ref true_path = scopes_.back();
    scopes_.pop_back();

    ast_conditional_branch::ref branch = std::dynamic_pointer_cast<ast_conditional_branch>(scope()->statements_.back());
    if (!branch) {
      throw std::runtime_error("Expected if statement");
    }

    branch->true_path_ = true_path;
    branch->false_path_ = false_path;
  }

  void switch_begin(const location& loc, const location& cond_loc) {
    ast_switch::ref select = std::make_shared<ast_switch>();
    select->set_loc(loc);
    select->expression_ = expressions_.back();
    expressions_.pop_back();

    if (!type_system_->is_integral_type(select->expression_->type_name())) {
      std::stringstream error_msg;
      error_msg << "cannot use expression type '" << select->expression_->type_name() << "' in switch statement";
      errors_.push_back(location_error(error_msg.str(), cond_loc));
    }

    scopes_.push_back(select);
  }

  void switch_end(const location& loc) {
    /* inner scope contains switch statement case labels */
    ast_switch::ref select = std::dynamic_pointer_cast<ast_switch>(scope());
    if (!select) {
      throw std::runtime_error("Missing switch scope");
    }
    if (!select->default_case_) {
      std::stringstream error_msg;
      error_msg << "switch statement does not have a default case";
      errors_.push_back(location_error(error_msg.str(), loc));
    }
    scopes_.pop_back();
    scope()->statements_.push_back(select);
  }

  void case_statement(const location& loc, const location& expr_loc, const bool default_case) {
    ast_expression::ref expr;
    if (!default_case) {
      expr = expressions_.back();
      expressions_.pop_back();
    }
    ast_switch::ref select = std::dynamic_pointer_cast<ast_switch>(scope());
    if (!select) {
      std::stringstream error_msg;
      error_msg << "case statement without switch statement";
      errors_.push_back(location_error(error_msg.str(), loc));
      return;
    }
    if (!default_case) {
      ast_constant::ref constant_expr = std::dynamic_pointer_cast<ast_constant>(expr);
      if (!constant_expr) {
        std::stringstream error_msg;
        error_msg << "switch statement case expression must be a constant";
        errors_.push_back(location_error(error_msg.str(), expr_loc));
      } else {
        size_t value = 0;
        if (!constant_expr->value_->get_numeric_value(&value)) {
          std::stringstream error_msg;
          error_msg << "switch statement case expression must be a constant";
          errors_.push_back(location_error(error_msg.str(), expr_loc));
        }
        if (select->cases_.find(value) != std::end(select->cases_)) {
          std::stringstream error_msg;
          error_msg << "duplicate case statement";
          errors_.push_back(location_error(error_msg.str(), loc));
        }
        select->cases_[value] = select->statements_.size();
      }
    } else {
      select->default_case_ = std::make_shared<size_t>(select->statements_.size());
    }
  }

  void expression_statement() {
    scope()->statements_.push_back(expressions_.back());
    expressions_.pop_back();
    if (!expressions_.empty()) {
      throw std::runtime_error("Expressions remaining");
    }
  }

  ast_type::ref current_type() {
    ast_type::ref type;
    if (type_specifier_.back()->struct_type()) { /* struct object; */
      type = std::make_shared<ast_type>(*type_specifier_.back()); /* can this copy be avoided? */
      if (!var_arrays_.empty() && var_arrays_.back()) { /* struct object x[10]; */
        ast_var_array::ref array = std::make_shared<ast_var_array>(*var_arrays_.back());
        array->element_type_ = std::make_shared<ast_type>(*type_specifier_.back());
        type = std::make_shared<ast_type>(array);
        type->set_const(array->element_type_->is_const()); /* inherit the constness of the element type */
      }
    } else {
      if (!var_arrays_.empty() && var_arrays_.back()) { /* uint64_t x[10]; */
        type = std::make_shared<ast_type>(var_arrays_.back());
        type->set_const(var_arrays_.back()->element_type()->is_const());
      } else { /* uint64_t x; */
        type = std::make_shared<ast_type>(*type_specifier_.back());
      }
    }
    return type;
  }

  ast_var::ref declare_var_error_recovery(const ast_var_struct::ref& context, const ast_type::ref type, const std::string& var_name, const location& loc) {
    std::stringstream error_msg1;
    error_msg1 << "'" << var_name << "' is already declared";
    errors_.push_back(location_error(error_msg1.str(), loc));
    ast_var::ref first_declaration = context->find(var_name);
    if (!first_declaration) {
      throw parser_exception();
    }
    std::stringstream error_msg2;
    error_msg2 << "multiple declarations of '" << var_name << "'";
    errors_.push_back(location_error(error_msg2.str(), first_declaration->loc()));
    return first_declaration;
  }

  std::vector<ast_var::ref> declaration_common(const ast_var_struct::ref& context) {
    std::vector<ast_var::ref> declarations;
    while (!direct_declarator_.empty()) { /* uint64_t x,y,z,w; */
      ast_var::ref var = context->declare_var(current_type(), direct_declarator_.back(), var_locations_.back());
      if (!var) {
        var = declare_var_error_recovery(context, current_type(), direct_declarator_.back(), var_locations_.back());
      }
      declarations.push_back(var);
      direct_declarator_.pop_back(); /* shift variable name */
      var_arrays_.pop_back(); /* shift (possibly empty) array info */
      var_locations_.pop_back(); /* shift line number information */
    }
    type_specifier_.pop_back();
    std::reverse(std::begin(declarations), std::end(declarations)); /* we built this vector backwards */
    return declarations;
  }

  void parameter_declaration(const location& loc) {
    ast_function::ref function = scope_function();
    if (!function) {
      errors_.push_back(location_error("need function scope for parameter declaration", loc));
      throw parser_exception();
    }
    std::vector<ast_var::ref> vars = declaration_common(scope());
    function->parameters_.push_back(vars[0]);
  }

  void struct_field_declaration() { /* declaration of a field in a structure */
    while (!direct_declarator_.empty()) { /* uint64_t x,y,z,w; */
      ast_var::ref var = struct_->struct_type()->declare_struct_var(current_type(), direct_declarator_.back(), var_locations_.back());
      direct_declarator_.pop_back(); /* shift variable name */
      var_arrays_.pop_back(); /* shift (possibly empty) array info */
      var_locations_.pop_back(); /* shift line number information */
    }
    type_specifier_.pop_back();
  }

  std::vector<ast_expression::ref> create_initializer_list_assignments(const ast_var::ref& lhs, const ast_expression::ref& rhs, const location& loc) {
    std::vector<ast_expression::ref> assignments;
    ast_initializer_list::ref intializer_list = std::dynamic_pointer_cast<ast_initializer_list>(rhs);
    if (!intializer_list) {
      /* regular scalar assignment */
      assignments.push_back(create_general_assignment(lhs, rhs, loc, true));
    } else { /* process the initializer list */
      if (lhs->is_struct()) {
        std::stringstream error_msg;
        error_msg << "array initialization of '" << lhs->type_name() << "' is not permitted";
        errors_.push_back(location_error(error_msg.str(), loc));
      } else if (lhs->is_array()) {
        ast_var_array::ref array = lhs->type()->array_type();
        if (array->sizes_[0] != intializer_list->args_.size()) {
          std::stringstream error_msg;
          error_msg << "invalid initialization of array of size " << array->sizes_[0] << " with " << intializer_list->args_.size() << " elements";
          errors_.push_back(location_error(error_msg.str(), loc));
        } else { /* initializer list contains correct number of elements for array initialization */
          for (size_t i = 0; i < array->sizes_[0]; ++i) {
            std::stringstream var_name;
            var_name << lhs->name() << "[" << i << "]";
            ast_var::ref array_element;
            if (array->dimensions() == 1) {
              array_element = std::make_shared<ast_var>(array->element_type(), var_name.str());
            } else { /* recursive initialization */
              ast_var_array::ref next_array = std::make_shared<ast_var_array>(*array);
              next_array->sizes_.erase(std::begin(next_array->sizes_));
              ast_type::ref element_type = std::make_shared<ast_type>(next_array);
              array_element = std::make_shared<ast_var>(element_type, var_name.str());
            }
            std::vector<ast_expression::ref> sub_assignments = create_initializer_list_assignments(array_element, intializer_list->args_[i], loc);
            assignments.insert(std::end(assignments), std::begin(sub_assignments), std::end(sub_assignments));
          }
        }
      } else { /* trying to initialize a non-array. */
        std::stringstream error_msg;
        error_msg << "array initialization of '" << lhs->type_name() << "' is not permitted";
        errors_.push_back(location_error(error_msg.str(), loc));
      }
    }
    return assignments;
  }

  void declaration(const location& loc) {
    if (std::dynamic_pointer_cast<ast_switch>(scope())) {
      std::stringstream error_msg;
      error_msg << "declaration not permitted within switch scope";
      errors_.push_back(location_error(error_msg.str(), loc));
    }
    std::vector<ast_var::ref> vars = declaration_common(scope());
    for (size_t i = 0; i < vars.size(); ++i) {
      if (initializer_expressions_[i]) {
        /* an initializer expression could be an initializer_list */
        /* in this case we generate one assignment for each array element */
        ast_scope::ref current_scope = scope();
        std::vector<ast_expression::ref> assignments = create_initializer_list_assignments(vars[i], initializer_expressions_[i], vars[i]->loc());
        current_scope->statements_.insert(std::end(current_scope->statements_), std::begin(assignments), std::end(assignments));
      }
    }
    initializer_expressions_.clear();
  }

  void init_declarator(const bool has_initializer_expression) {
    if (has_initializer_expression) {
      /* take one expression to use for the initializer */
      initializer_expressions_.push_back(expressions_.back());
      expressions_.pop_back();
    } else {
      /* must pad out the list for variables without initializers */
      initializer_expressions_.push_back(nullptr);
    }
  }

  void initializer_list_begin(const location& loc) {
    ast_type::ref type = std::make_shared<ast_type>("(initializer-list)");
    type->set_loc(loc);
    ast_initializer_list::ref list = std::make_shared<ast_initializer_list>(type);
    list->set_loc(loc);
    expressions_.push_back(list);
  }

  void initializer_list_element(const location& loc) {
    ast_expression::ref arg = expressions_.back();
    expressions_.pop_back();
    if (std::dynamic_pointer_cast<ast_initializer_list>(expressions_.back())) {
      ast_initializer_list::ref list = std::dynamic_pointer_cast<ast_initializer_list>(expressions_.back());
      list->args_.push_back(arg);
    } else {
      errors_.push_back(location_error("initializer-list element without initializer-list", loc));
      throw parser_exception();
    }
  }

  void direct_declarator(const location& loc, const std::string& name) {
    direct_declarator_.push_back(name);
    var_arrays_.push_back(nullptr); /* one for each var, in case we get array subscript */
    var_locations_.push_back(loc);
  }

  void type_specifier(const location& loc, const std::string& type_name, const bool is_const) {
    ast_type::ref struct_decl;
    if (ast_) {
      struct_decl = ast_->find_struct_declaration(type_name);
    }

    ast_type::ref type;
    if (struct_decl) {
      type = std::make_shared<ast_type>(*struct_decl);
    } else {
      if (type_system_->find_type(type_name)) {
        type = std::make_shared<ast_type>(type_name);
      } else {
        type = std::make_shared<ast_type>(type_system_->default_type_for_error_recovery());

        std::stringstream error_msg;
        error_msg << "'" << type_name << "' was not declared";
        errors_.push_back(location_error(error_msg.str(), loc));
      }
    }

    type->set_const(is_const); /* read-only */

    type->set_loc(loc);
    type_specifier_.push_back(type);
  }

  /* try to interpret the current expression as a numeric constant */
  bool expression_numeric_value(const location& loc, size_t* value) const {
    bool value_ok = false;
    ast_constant::ref constant = std::dynamic_pointer_cast<ast_constant>(expressions_.back());
    if (constant) {
      size_t result_value = 0;
      if (constant->value_->get_numeric_value(&result_value)) {
        if (value) {
          *value = result_value;
          value_ok = true;
        }
      }
    }
    return value_ok;
  }

  void direct_declarator_array_size(const location& loc) {
    const size_t var_index = direct_declarator_.size() - 1;
    if (!var_arrays_[var_index]) {
      var_arrays_[var_index] = std::make_shared<ast_var_array>(type_specifier_.back());
    }

    size_t length = 0;
    if (expression_numeric_value(loc, &length)) {
      if (length != 0) {
        var_arrays_[var_index]->sizes_.push_back(length); /* length OK */
      } else {
        std::stringstream error_msg;
        error_msg << "array size must be non-zero";
        errors_.push_back(location_error(error_msg.str(), loc));

        var_arrays_[var_index]->sizes_.push_back(1); /* default array size for error recovery */
      }
    } else {
      std::stringstream error_msg;
      error_msg << "expression must evaluate to a constant";
      errors_.push_back(location_error(error_msg.str(), loc));

      var_arrays_[var_index]->sizes_.push_back(1); /* default array size for error recovery */
    }

    expressions_.pop_back();
  }

  void primary_expression_identifier(const location& loc, const std::string& name) {
    if (!ast_) {
      ast_ = std::make_shared<syntax_tree>();
    }

    ast_var::ref var = scope_find(name);
    ast_function::ref func = ast_->find_function_definition(name);

    if (var) { /* reference to a variable */
      expressions_.push_back(var);
    } else if (func) { /* reference to a function name */
      ast_function_call::ref call = std::make_shared<ast_function_call>(func);
      call->set_loc(loc);
      call->retval_var_ = scope_declare_temporary_var(func->return_type(), call->loc_);
      if (!call->retval_var_) { /* todo: check other usage of this scope_declare_temporary_var function */
        throw parser_exception(); /* invalid function return type */
      }
      expressions_.push_back(call);
    } else if (type_system_->find_type(name)) { /* reference to a type (a cast/constructor call) */
      ast_type::ref type = std::make_shared<ast_type>(name);
      ast_type_constructor::ref constructor = std::make_shared<ast_type_constructor>(type);
      constructor->set_loc(loc);
      expressions_.push_back(constructor);
    } else { /* invaid use of identifier */
      std::stringstream error_msg;
      error_msg << "'" << name << "' has not been declared";
      errors_.push_back(location_error(error_msg.str(), loc));
      ast_type::ref default_type = std::make_shared<ast_type>(type_system_->default_type_for_error_recovery());
      ast_var::ref var = scope()->declare_var(default_type, name, loc);
      if (!var) {
        throw parser_exception();
      }
      expressions_.push_back(var); /* try to continue */
    }
  }

  void function_call_parameter(const location& loc) {
    ast_expression::ref arg = expressions_.back();
    expressions_.pop_back();
    if (std::dynamic_pointer_cast<ast_function_call>(expressions_.back())) {
      /* each parameter gets assigned to a temporary var with a unique name in the global scope */
      /* then the temporary gets passed into the function and this enables passing structs by-value */
      ast_function_call::ref call = std::dynamic_pointer_cast<ast_function_call>(expressions_.back());
      ast_type::ref arg_type = arg->type();
      if (call->args_.size() < call->function_->parameters_.size()) {
        /* this is the correct type. parameter count check is in function_call_parameters_end */
        arg_type = call->function_->parameters_[call->args_.size()]->type();
      }
      ast_var::ref temp = scope_declare_temporary_var(arg_type, arg->loc());
      ast_assignment::ref arg_and_copy = create_general_assignment(temp, arg, loc, true); /* const override */
      call->args_.push_back(arg_and_copy);
    } else if (std::dynamic_pointer_cast<ast_type_constructor>(expressions_.back())) {
      ast_type_constructor::ref constructor = std::dynamic_pointer_cast<ast_type_constructor>(expressions_.back());
      //ast_var::ref temp = scope_declare_temporary_var(arg->type(), arg->loc());
      //ast_assignment::ref arg_and_copy = create_assignment(temp, arg, loc); /* todo: is this necessary? */
      constructor->args_.push_back(arg); /* assuming that the above is not necessary. avoid the assignment for now */
    } else {
      errors_.push_back(location_error("function argument without call", loc));
      throw parser_exception();
    }
  }

  void function_call_parameters_end(const location& loc) {
    if (std::dynamic_pointer_cast<ast_function_call>(expressions_.back())) {
      ast_function_call::ref call = std::dynamic_pointer_cast<ast_function_call>(expressions_.back());
      if (call->args_.size() != call->function_->parameters_.size()) {
        std::stringstream error_msg;
        error_msg << "function '" << call->function_->name() << "' expects " << call->function_->parameters_.size();
        error_msg << " arguments but " << call->args_.size() << " provided";
        errors_.push_back(location_error(error_msg.str(), loc));
      }
    } else if (std::dynamic_pointer_cast<ast_type_constructor>(expressions_.back())) {
      ast_type_constructor::ref constructor = std::dynamic_pointer_cast<ast_type_constructor>(expressions_.back());
      std::vector<constant_value::ref> representatives;
      for (size_t i = 0; i < constructor->args_.size(); ++i) {
        representatives.push_back(type_system_->representative_value(constructor->args_[i]->type_name()));
      }
      constant_value::ref constructor_result = type_system_->construct_value(constructor->type_name(), representatives);
      if (!constructor_result) {
        std::stringstream error_msg;
        error_msg << "construction of type '" << constructor->type_name() << "' not possible with provided arguments";
        errors_.push_back(location_error(error_msg.str(), loc));
      }
    } else {
      errors_.push_back(location_error("expected function call", loc));
      throw parser_exception();
    }
  }

  ast_constant::ref make_constant(const location& loc, const digit_vector& value) {
    type_factory::ref factory = type_system_->find_type(type_system_->literal_type_name());
    literal_type_factory::ref integer_factory = std::dynamic_pointer_cast<literal_type_factory>(factory);

    integer integer_literal(value, integer_factory->modulus_);
    constant_value_literal::ref integer_constant = std::make_shared<constant_value_literal>(integer_literal);

    ast_type::ref literal_type = std::make_shared<ast_type>(type_system_->literal_type_name());
    literal_type->set_loc(loc);

    ast_constant::ref constant = std::make_shared<ast_constant>(literal_type, integer_constant);
    constant->set_loc(loc);
    return constant;
  }

  /* integer literals with u or U suffix */
  ast_constant::ref primary_expression_constant_unsigned(const location& loc, const std::string& value) {
    digit_vector integer_digits;
    if (!parse_integer(&integer_digits, value)) {
      throw std::runtime_error("Bad literal");
    }
    constant_value::ref literal;
    ast_type::ref type = std::make_shared<ast_type>("uint64_t");
    if (integer_digits.empty()) {
      literal = std::make_shared<constant_value_builtin<uint64_t>>(0);
    } else { /* truncate */
      literal = std::make_shared<constant_value_builtin<uint64_t>>(integer_digits.at(0));
    }
    ast_constant::ref constant = std::make_shared<ast_constant>(type, literal);
    constant->set_loc(loc);
    return constant;
  }

  /* integer literals with l or L suffix */
  ast_constant::ref primary_expression_constant_signed(const location& loc, const std::string& value) {
    digit_vector integer_digits;
    if (!parse_integer(&integer_digits, value)) {
      throw std::runtime_error("Bad literal");
    }
    constant_value::ref literal;
    ast_type::ref type = std::make_shared<ast_type>("int64_t");
    if (integer_digits.empty()) {
      literal = std::make_shared<constant_value_builtin<int64_t>>(0);
    } else { /* truncate */
      literal = std::make_shared<constant_value_builtin<int64_t>>(integer_digits.at(0));
    }
    ast_constant::ref constant = std::make_shared<ast_constant>(type, literal);
    constant->set_loc(loc);
    return constant;
  }

  void primary_expression_constant_suffix(const location& loc, const std::string& value) {
    ast_constant::ref constant;
    const std::string suffix = value.substr(value.length() - 1);
    if ((suffix == "U") || (suffix == "u")) { /* signed */
      constant = primary_expression_constant_unsigned(loc, value.substr(0, value.length() - 1));
    } else if ((suffix == "L") || (suffix == "l")) { /* unsigned */
      constant = primary_expression_constant_signed(loc, value.substr(0, value.length() - 1));
    } else {
      digit_vector integer_digits;
      if (!parse_integer(&integer_digits, value)) {
        throw std::runtime_error("Bad literal");
      }
      constant = make_constant(loc, integer_digits);
    }
    expressions_.push_back(constant);
  }

  void postfix_array_index(const location& loc) {
    ast_expression::ref rhs = expressions_.back();
    expressions_.pop_back();
    ast_expression::ref lhs = expressions_.back();
    expressions_.pop_back();

    if (!type_system_->is_integral_type(rhs->type_name())) {
      std::stringstream error_msg;
      error_msg << "cannot use expression type '" << rhs->type_name() << "' as array index";
      errors_.push_back(location_error(error_msg.str(), loc));
    }

    ast_type::ref dereference_type = lhs->type();
    if (!dereference_type->array_type()) {
        /* could still be OK, if it's an external array */
        std::string element_type = type_system_->array_type_name(lhs->type()->type_name());
        if (!element_type.empty()) {
          dereference_type = std::make_shared<ast_type>(element_type);
          dereference_type->set_const(false);
        } else {
          errors_.push_back(location_error("left of array index is not of array type", loc));
          dereference_type = lhs->type();
        }
    } else {
      /* reduce the dimension of the array */
      ast_var_array::ref array = std::make_shared<ast_var_array>(*dereference_type->array_type());
      array->sizes_.erase(std::begin(array->sizes_));
      if (array->sizes_.empty()) {
        /* maximum dereference reached */
        dereference_type = array->element_type();
      } else {
        dereference_type = std::make_shared<ast_type>(array);
      }
    }
    expressions_.push_back(std::make_shared<ast_array_subscript>(dereference_type, lhs, rhs));
  }

  void postfix_dot_identifier(const location& loc, const std::string& field_name) {
    ast_expression::ref expr = expressions_.back();
    expressions_.pop_back();

    ast_var_struct::ref struct_type = expr->type()->struct_type();
    if (!struct_type) {
      std::stringstream error_msg;
      error_msg << "'" << expr->type()->type_name() << "' has no field named '" << field_name << "'";
      errors_.push_back(location_error(error_msg.str(), loc));
      expressions_.push_back(expr); /* try to continue */
    } else {
      ast_var::ref field = struct_type->find(field_name);
      if (!field) {
        std::stringstream error_msg;
        error_msg << "'" << expr->type_name() << "' has no field named '" << field_name << "'";
        errors_.push_back(location_error(error_msg.str(), loc));
        expressions_.push_back(expr); /* try to continue */
      } else {
        ast_struct_access::ref op = std::make_shared<ast_struct_access>(expr, field);
        expressions_.push_back(op);
      }
    }
  }

  template <typename T> void postfix_operator(const location& loc) {
    /* x++  =>  (tmp=x, x=x+1, tmp) */
    ast_expression::ref x = expressions_.back();
    expressions_.pop_back();
    ast_type::ref tmp_type = std::make_shared<ast_type>(*x->type());
    tmp_type->set_const(true);
    ast_var::ref tmp = scope_declare_temporary_var(tmp_type, x->loc());
    ast_assignment::ref tmp_assign = create_general_assignment(tmp, x, loc, true); /* const override for initialization */
    ast_constant::ref one = make_constant(loc, {1});
    ast_expression::ref x_op_one = make_binary_operator<T>(loc, x, one);
    ast_assignment::ref x_op = create_assignment(x, x_op_one, loc);
    ast_sequence::ref seq = std::make_shared<ast_sequence>(tmp_type);
    seq->set_loc(loc);
    seq->expressions_.push_back(tmp_assign);
    seq->expressions_.push_back(x_op);
    seq->expressions_.push_back(tmp);
    expressions_.push_back(seq);
  }

  void assignment_operator(const location& loc) {
    ast_expression::ref rhs = expressions_.back();
    expressions_.pop_back();
    ast_expression::ref lhs = expressions_.back();
    expressions_.pop_back();
    ast_assignment::ref op = create_assignment(lhs, rhs, loc);
    expressions_.push_back(op);
  }

  template <typename T> void assignment_expression(const location& loc) {
    ast_expression::ref rhs = expressions_.back();
    expressions_.pop_back();
    ast_expression::ref lhs = expressions_.back();
    expressions_.pop_back();
    ast_expression::ref op = make_binary_operator<T>(loc, lhs, rhs);
    ast_assignment::ref result = create_assignment(lhs, op, loc);
    expressions_.push_back(result);
  }

  ast_assignment::ref create_assignment(const ast_expression::ref& lhs, const ast_expression::ref& rhs, const location& loc) {
    /* default behaviour is not to override const. */
    /* const override is permitted during initialization. */
    return create_general_assignment(lhs, rhs, loc, false);
  }

  ast_assignment::ref create_general_assignment(const ast_expression::ref& lhs, const ast_expression::ref& rhs, const location& loc, const bool const_override) {
   bool assignment_ok = false;
   ast_assignment::ref op;
    if (lhs->is_struct() || lhs->is_array() || rhs->is_struct() || rhs->is_array()) {
      if (lhs->type_name() == rhs->type_name()) {
        assignment_ok = true;
      } /* continue building the tree even when there is a type error */
      op = std::make_shared<ast_struct_array_assignment>(lhs->type(), lhs, rhs); /* generate a deep copy */
      op->set_loc(loc);
    } else { /* scalar assignment */
      if (lhs->type_name() == rhs->type_name()) {
        assignment_ok = true; /* no cast required */
      } else {
        constant_value::ref rhs_value = type_system_->representative_value(rhs->type_name());
        constant_value::ref result_value = type_system_->implicit_cast_value(lhs->type_name(), rhs_value);
        if (!!result_value) {
          assignment_ok = true; /* a cast is possible */
        }
      }
      op = std::make_shared<ast_assignment>(lhs->type(), lhs, rhs); /* normal scalar assignment */
      op->set_loc(loc);
    }
    if (assignment_ok) {
      if (!const_override && lhs->type()->is_const()) {
        std::stringstream error_msg;
        error_msg << "left of assignment is constant";
        errors_.push_back(location_error(error_msg.str(), loc));
        assignment_ok = false;
      }
    } else {
      /* is it possible to explicitly cast? if so, give better error message */
      constant_value::ref rhs_value = type_system_->representative_value(rhs->type_name());
      constant_value::ref result_value = type_system_->construct_value(lhs->type_name(), {rhs_value});
      if (!!result_value) {
        std::stringstream error_msg;
        error_msg << "cannot convert '" << rhs->type_name() << "' to '" << lhs->type_name() << "' without cast";
        errors_.push_back(location_error(error_msg.str(), loc));
      } else {
        std::stringstream error_msg;
        error_msg << "cannot convert '" << rhs->type_name() << "' to '" << lhs->type_name() << "'";
        errors_.push_back(location_error(error_msg.str(), loc));
      }
    }
    return op;
  }

  template <typename T> void prefix_operator(const location& loc) {
    /* x++  =>  (x=x+1) */
    ast_expression::ref x = expressions_.back();
    expressions_.pop_back();
    ast_constant::ref one = make_constant(loc, {1});
    ast_expression::ref x_op_one = make_binary_operator<T>(loc, x, one);
    ast_assignment::ref x_op = create_assignment(x, x_op_one, loc);
    x_op->set_loc(loc);
    expressions_.push_back(x_op);
  }

  template <typename T> void unary_operator(const location& loc) {
    ast_expression::ref expr = expressions_.back();
    expressions_.pop_back();

    bool constant_fold = false;
    constant_value::ref value;
    if (std::dynamic_pointer_cast<ast_constant>(expr)) {
      value = std::dynamic_pointer_cast<ast_constant>(expr)->value_;
      constant_fold = true; /* substitute expression with result constant */
    } else { /* use non-zero "representative" values */
      value = type_system_->representative_value(expr->type_name());
    }

    std::shared_ptr<T> op = std::make_shared<T>(nullptr, expr);
    constant_value::ref result_value = op->evaluate(value);

    ast_type::ref result_type;
    if (typeid(*value) == typeid(*result_value)) {
      /* preserve the input type */
      result_type = std::make_shared<ast_type>(*expr->type());
    } else if (std::dynamic_pointer_cast<constant_value_boolean>(result_value)) {
      /* logical negation returns a boolean */
      result_type = std::make_shared<ast_type>(type_system_->boolean_type_name());
    } else if (std::dynamic_pointer_cast<constant_value_builtin<int64_t>>(result_value)) {
      /* when operations are applied to a literal it becomes this builtin type */
      result_type = std::make_shared<ast_type>(type_system_->literal_promotion_type_name());
    } else {
      std::stringstream error_msg;
      error_msg << "invalid type '" << expr->type_name() << "' in unary operator expression";
      errors_.push_back(location_error(error_msg.str(), loc));
      result_type = std::make_shared<ast_type>(type_system_->default_type_for_error_recovery());
    }

    result_type->set_const(true); /* result must be read-only */

    ast_expression::ref result_expr;
    if (constant_fold) {
      result_expr = std::make_shared<ast_constant>(result_type, result_value);
    } else {
      result_expr = std::make_shared<T>(result_type, expr);
    }

    result_expr->set_loc(loc);
    expressions_.push_back(result_expr);
  }

  void ternary_operator(const location& loc) {
    ast_expression::ref false_expression = expressions_.back();
    expressions_.pop_back();
    ast_expression::ref true_expression = expressions_.back();
    expressions_.pop_back();
    ast_expression::ref condition = expressions_.back();
    expressions_.pop_back();

    if (!type_system_->is_integral_type(condition->type_name())) {
      std::stringstream error_msg;
      error_msg << "invalid type '" << condition->type_name() << "' in ternary conditional expression";
      errors_.push_back(location_error(error_msg.str(), loc));
    }

    ast_type::ref expression_type = true_expression->type();
    if (true_expression->type_name() != false_expression->type_name()) {
      std::stringstream error_msg;
      error_msg << "incompatible types '" << true_expression->type_name() << "' and '" << false_expression->type_name() << "' in ternary conditional expression";
      errors_.push_back(location_error(error_msg.str(), loc));
      expression_type = std::make_shared<ast_type>(type_system_->default_type_for_error_recovery());
    }

    ast_ternary::ref ternary = std::make_shared<ast_ternary>(expression_type);
    ternary->condition_ = condition;
    ternary->true_expression_ = true_expression;
    ternary->false_expression_ = false_expression;

    expressions_.push_back(ternary);
  }

  template <typename T> ast_expression::ref make_binary_operator(const location& loc, const ast_expression::ref& lhs, const ast_expression::ref& rhs) {
    bool constant_fold = false;
    constant_value::ref lhs_value;
    constant_value::ref rhs_value;
    if (std::dynamic_pointer_cast<ast_constant>(lhs) && std::dynamic_pointer_cast<ast_constant>(rhs)) {
      lhs_value = std::dynamic_pointer_cast<ast_constant>(lhs)->value_;
      rhs_value = std::dynamic_pointer_cast<ast_constant>(rhs)->value_;
      constant_fold = true; /* substitute expression with result constant */
    } else { /* use non-zero "representative" values */
      lhs_value = type_system_->representative_value(lhs->type_name());
      rhs_value = type_system_->representative_value(rhs->type_name());
    }

    /* cast if necessary and work out the return type */
    binary_evaluator binary_op(type_system_, std::make_shared<T>(nullptr, lhs, rhs));
    binary_op.evaluate(lhs->type(), lhs_value, rhs->type(), rhs_value);

    ast_type::ref result_type;
    if (binary_op.result() != binary_evaluator::result_ok) {
      errors_.push_back(binary_op.error_message(loc));
      result_type = std::make_shared<ast_type>(type_system_->default_type_for_error_recovery());
    } else {
      result_type = binary_op.result_type();
    }

    ast_expression::ref result_expr;
    if (constant_fold) {
      result_expr = std::make_shared<ast_constant>(result_type, binary_op.result_value());
    } else {
      result_expr = std::make_shared<T>(result_type, lhs, rhs);
    }
    result_expr->set_loc(loc);
    return result_expr;
  }

  template <typename T> void binary_operator(const location& loc) {
    ast_expression::ref rhs = expressions_.back();
    expressions_.pop_back();
    ast_expression::ref lhs = expressions_.back();
    expressions_.pop_back();
    ast_expression::ref op = make_binary_operator<T>(loc, lhs, rhs);
    expressions_.push_back(op);
  }

  void continue_statement(const location& loc) {
    bool is_valid = false;
    for (ast_scope::ref scope : scopes_) {
      if (std::dynamic_pointer_cast<ast_loop>(scope)) {
        is_valid = true;
        break;
      }
    }

    if (!is_valid) {
      std::stringstream error_msg;
      error_msg << "statement is not valid without loop scope";
      errors_.push_back(location_error(error_msg.str(), loc));
    }

    ast_continue::ref statement = std::make_shared<ast_continue>();
    statement->set_loc(loc);
    scope()->statements_.push_back(statement);
  }

  void break_statement(const location& loc) {
    bool is_valid = false;
    for (ast_scope::ref scope : scopes_) {
      if (std::dynamic_pointer_cast<ast_loop>(scope)) {
        is_valid = true;
        break;
      } else if (std::dynamic_pointer_cast<ast_switch>(scope)) {
        is_valid = true;
        break;
      }
    }

    if (!is_valid) {
      std::stringstream error_msg;
      error_msg << "statement is not valid in this scope";
      errors_.push_back(location_error(error_msg.str(), loc));
    }

    ast_break::ref statement = std::make_shared<ast_break>();
    statement->set_loc(loc);
    scope()->statements_.push_back(statement);
  }

  void return_statement(const location& loc, const location& expr_loc) {
    ast_function::ref function = scope_function();
    if (!function) {
      throw parser_exception(); /* need function scope */
    }

    /* we assign to a dedicated return-value var in the function body. */
    /* this way we get automatic type checking for the expression being returned */
    ast_assignment::ref ret_copy = create_general_assignment(function->retval_var_, expressions_.back(), expr_loc, true); /* const override */
    expressions_.pop_back();

    ast_return::ref ret = std::make_shared<ast_return>(ret_copy);
    ret->set_loc(loc);
    scope()->statements_.push_back(ret);
  }

  ast_var::ref scope_declare_temporary_var(const ast_type::ref type, const location& loc) {
    std::stringstream ss;
    ss << "_tmp" << next_variable_id_++;
    return scope()->declare_var(type, ss.str(), loc);
  }

  void report_parser_error(const location& loc, const std::string& message) {
    errors_.push_back(location_error(message, loc));
  }

private:

  syntax_tree::ref ast_;
  std::vector<location_error> errors_;

  type_system::ref type_system_;

  std::shared_ptr<lexer> lexer_;
  std::shared_ptr<parser> parser_;

  /* parser state */
  size_t next_variable_id_;
  ast_type::ref struct_;
  std::vector<ast_type::ref> type_specifier_;
  std::vector<std::string> direct_declarator_;
  std::vector<location> var_locations_;
  std::vector<ast_var_array::ref> var_arrays_;
  std::vector<ast_expression::ref> initializer_expressions_;
  std::vector<ast_expression::ref> expressions_;
  std::vector<ast_scope::ref> scopes_;
  ast_scope::ref global_scope_;

};

} /* namespace */

#endif /* __AST_BUILDER_H__ */
