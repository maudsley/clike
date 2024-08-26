#ifndef __AST_H__
#define __AST_H__

/* the AST representation of the c-like code for use with the interpreter */

#include "ast_type.h"
#include "type_system.h"
#include "constant_value.h"
#include "constant_value_integer.h"
#include "integer.h"
#include "integer_parser.h"
#include "location_error.h"
#include <string>
#include <sstream>
#include <memory>
#include <map>

namespace clike {

class parser_exception : public std::exception {
public:
};

enum ast_storage {
  STORAGE_NOT_IMPLEMENTED
};

class ast_node {
public:
  typedef std::shared_ptr<ast_node> ref;
  virtual ~ast_node() {}
  location loc() const {
    return loc_;
  }
  void set_loc(const location& loc) {
    loc_ = loc;
  }
  location loc_;
};

class ast_statement : public ast_node { /* ends in a semi-colon */
public:
  typedef std::shared_ptr<ast_statement> ref;
};

class ast_expression : public ast_statement { /* evaluates to a variable (with a type) */
public:
  typedef std::shared_ptr<ast_expression> ref;
  ast_expression(const ast_type::ref& type) : type_(type)  {
  }
  virtual std::vector<ast_expression::ref> sub_expressions() const { /* override */
    return {}; /* return a list of child nodes of this expression */
  }
  ast_type::ref type() const {
    return type_;
  }
  std::string type_name() const {
    return type_->type_name();
  }
  bool is_struct() const {
    return !!type_->struct_type();
  }
  bool is_array() const {
    return !!type_->array_type();
  }
  ast_type::ref type_;
};

class ast_constant : public ast_expression {
public:
  typedef std::shared_ptr<ast_constant> ref;
  ast_constant(const ast_type::ref type, const constant_value::ref value) : ast_expression(type), value_(value) {
  }
  constant_value::ref value() const {
    return value_;
  }
  constant_value::ref value_;
};

class ast_var : public ast_expression {
public:
  typedef std::shared_ptr<ast_var> ref;
  ast_var(const ast_type::ref type, const std::string& name) : ast_expression(type), name_(name) {
  }
  std::string name() const {
    return name_;
  }
  std::string name_;
};

class ast_var_ptr : public ast_var { /* proxy for array access handled by type system object */
public:
  typedef std::shared_ptr<ast_var_ptr> ref;
  ast_var_ptr(const ast_type::ref type, const std::string& name, const ast_var::ref& object, const std::vector<size_t>& indices)
  : ast_var(type, name), object_(object), indices_(indices) {
  }
  ast_var::ref object() const {
    return object_;
  }
  std::vector<size_t> indices() const {
    return indices_;
  }
  ast_var::ref object_;
  std::vector<size_t> indices_;
};

class ast_var_array {
public:
  typedef std::shared_ptr<ast_var_array> ref;
  ast_var_array(const ast_type::ref element_type) : element_type_(element_type) {
  }
  std::string array_type_name() const { /* todo: implement this properly */
    std::stringstream ss;
    ss << element_type_->type_name();
    for (size_t i = 0; i < sizes_.size(); ++i) {
      ss << "[" << sizes_[i] << "]";
    }
    return ss.str();
  }
  ast_type::ref element_type() const {
    return element_type_;
  }
  size_t dimensions() const {
    return sizes_.size();
  }
  ast_type::ref element_type_;
  std::vector<size_t> sizes_;
};

class ast_sequence : public ast_expression {
public:
  typedef std::shared_ptr<ast_sequence> ref;
  ast_sequence(const ast_type::ref type) : ast_expression(type) {
  }
  std::vector<ast_expression::ref> sub_expressions() const override {
    return expressions_; /* left-to-right */
  }
  std::vector<ast_expression::ref> expressions_;
};

class ast_unary : public ast_expression {
public:
  typedef std::shared_ptr<ast_unary> ref;
  ast_unary(const ast_type::ref type, const ast_expression::ref expr) : ast_expression(type), expression_(expr) {
  }
  std::vector<ast_expression::ref> sub_expressions() const override {
    return {expression_};
  }
  virtual constant_value::ref evaluate(const constant_value::ref& value) const {
    throw std::runtime_error("Unary operator evaluate not implemented");
  }
  ast_expression::ref expression_;
};

class ast_unary_arith_negate : public ast_unary {
public:
  typedef std::shared_ptr<ast_unary_arith_negate> ref;
  ast_unary_arith_negate(const ast_type::ref type, const ast_expression::ref expr) : ast_unary(type, expr) {
  }
  constant_value::ref evaluate(const constant_value::ref& value) const override {
    return value->unary_arith_negate();
  }
};

class ast_unary_bitwise_negate : public ast_unary {
public:
  typedef std::shared_ptr<ast_unary_bitwise_negate> ref;
  ast_unary_bitwise_negate(const ast_type::ref type, const ast_expression::ref expr) : ast_unary(type, expr) {
  }
  constant_value::ref evaluate(const constant_value::ref& value) const override {
    return value->unary_bitwise_negate();
  }
};

class ast_unary_logical_negate : public ast_unary {
public:
  typedef std::shared_ptr<ast_unary_logical_negate> ref;
  ast_unary_logical_negate(const ast_type::ref type, const ast_expression::ref expr) : ast_unary(type, expr) {
  }
  constant_value::ref evaluate(const constant_value::ref& value) const override {
    return value->unary_logical_negate();
  }
};

class ast_ternary : public ast_expression {
public:
  typedef std::shared_ptr<ast_ternary> ref;
  ast_ternary(const ast_type::ref& type) : ast_expression(type) {
  }
  std::vector<ast_expression::ref> sub_expressions() const override {
    return {condition_}; /* sub-expressions evaluation depends on the condition */
  }
  ast_expression::ref condition_;
  ast_expression::ref true_expression_; /* only evaluate if the condition is true */
  ast_expression::ref false_expression_; /* only evaluate if the condition is false */
};

class ast_binary : public ast_expression {
public:
  typedef std::shared_ptr<ast_binary> ref;
  ast_binary(const ast_type::ref& type) : ast_expression(type) {
  }
  ast_binary(const ast_type::ref& type, const ast_expression::ref& lhs, const ast_expression::ref& rhs) : ast_expression(type), lhs_(lhs), rhs_(rhs) {
  }
  std::vector<ast_expression::ref> sub_expressions() const override {
    return {lhs_, rhs_}; /* all binary operators are left-to-right by default unless overriden */
  }
  ast_expression::ref lhs() const {
    return lhs_;
  }
  ast_expression::ref rhs() const {
    return rhs_;
  }
  virtual constant_value::ref evaluate(const constant_value::ref& lhs, const constant_value::ref& rhs) const {
    throw std::runtime_error("Binary operator evaluate not implemented");
  }
  ast_expression::ref lhs_;
  ast_expression::ref rhs_;
};

class ast_assignment : public ast_binary {
public:
  typedef std::shared_ptr<ast_assignment> ref;
  ast_assignment(const ast_type::ref& type, const ast_expression::ref& lhs, const ast_expression::ref& rhs) : ast_binary(type, lhs, rhs) {
  }
  std::vector<ast_expression::ref> sub_expressions() const override {
    return {rhs_, lhs_}; /* assignment is right-to-left */
  }
  constant_value::ref evaluate(const constant_value::ref& lhs, const constant_value::ref& rhs) const override {
    return lhs; /* we use this for type resolution only. the expression has the type of the LHS. */
  }
};

class ast_struct_array_assignment : public ast_assignment {
public:
  /* instead of generating an assignment statement for each element of a struct or an array */
  /* we generate this node which causes the interpreter to carry out the individual element assignments */
  typedef std::shared_ptr<ast_struct_array_assignment> ref;
  ast_struct_array_assignment(const ast_type::ref& type, const ast_expression::ref& lhs, const ast_expression::ref& rhs) : ast_assignment(type, lhs, rhs) {
  }
};

class ast_array_subscript : public ast_binary {
public:
  typedef std::shared_ptr<ast_array_subscript> ref;
  ast_array_subscript(const ast_type::ref& type, const ast_expression::ref& lhs, const ast_expression::ref& rhs) : ast_binary(type, lhs, rhs) {
  }
  std::vector<ast_expression::ref> sub_expressions() const override {
    return {lhs_, rhs_}; /* left-to-right */
  }
};

class ast_struct_access : public ast_expression {
public:
  typedef std::shared_ptr<ast_struct_access> ref;
  ast_struct_access(const ast_expression::ref& object, const ast_var::ref& field)
  : ast_expression(field->type()), object_(object), field_(field) {
  }
  std::vector<ast_expression::ref> sub_expressions() const override {
    return {object_}; /* the field is always a var, not a sub-expression, so not need to evaluate it */
  }
  ast_expression::ref object_;
  ast_var::ref field_;
};

class ast_binary_logical_or : public ast_binary {
public:
  typedef std::shared_ptr<ast_binary_logical_or> ref;
  ast_binary_logical_or(const ast_type::ref& type, const ast_expression::ref& lhs, const ast_expression::ref& rhs) : ast_binary(type, lhs, rhs) {
  }
  std::vector<ast_expression::ref> sub_expressions() const override {
    return {lhs_}; /* evaluation of RHS depends on the value of the LHS expression (short-circuit evaluation) */
  }
  constant_value::ref evaluate(const constant_value::ref& lhs, const constant_value::ref& rhs) const override {
    return lhs->logical_or(rhs);
  }
};

class ast_binary_logical_and : public ast_binary {
public:
  typedef std::shared_ptr<ast_binary_logical_and> ref;
  ast_binary_logical_and(const ast_type::ref& type, const ast_expression::ref& lhs, const ast_expression::ref& rhs) : ast_binary(type, lhs, rhs) {
  }
  std::vector<ast_expression::ref> sub_expressions() const override {
    return {lhs_}; /* evaluation of RHS depends on the value of the LHS expression (short-circuit evaluation) */
  }
  constant_value::ref evaluate(const constant_value::ref& lhs, const constant_value::ref& rhs) const override {
    return lhs->logical_and(rhs);
  }
};

class ast_binary_bitwise_or : public ast_binary {
public:
  typedef std::shared_ptr<ast_binary_bitwise_or> ref;
  ast_binary_bitwise_or(const ast_type::ref& type, const ast_expression::ref& lhs, const ast_expression::ref& rhs) : ast_binary(type, lhs, rhs) {
  }
  constant_value::ref evaluate(const constant_value::ref& lhs, const constant_value::ref& rhs) const override {
    return lhs->bitwise_or(rhs);
  }
};

class ast_binary_bitwise_xor : public ast_binary {
public:
  typedef std::shared_ptr<ast_binary_bitwise_xor> ref;
  ast_binary_bitwise_xor(const ast_type::ref& type, const ast_expression::ref& lhs, const ast_expression::ref& rhs) : ast_binary(type, lhs, rhs) {
  }
  constant_value::ref evaluate(const constant_value::ref& lhs, const constant_value::ref& rhs) const override {
    return lhs->bitwise_xor(rhs);
  }
};

class ast_binary_bitwise_and : public ast_binary {
public:
  typedef std::shared_ptr<ast_binary_bitwise_and> ref;
  ast_binary_bitwise_and(const ast_type::ref& type, const ast_expression::ref& lhs, const ast_expression::ref& rhs) : ast_binary(type, lhs, rhs) {
  }
  constant_value::ref evaluate(const constant_value::ref& lhs, const constant_value::ref& rhs) const override {
    return lhs->bitwise_and(rhs);
  }
};

class ast_binary_inequality_eq : public ast_binary {
public:
  typedef std::shared_ptr<ast_binary_inequality_eq> ref;
  ast_binary_inequality_eq(const ast_type::ref& type, const ast_expression::ref& lhs, const ast_expression::ref& rhs) : ast_binary(type, lhs, rhs) {
  }
  constant_value::ref evaluate(const constant_value::ref& lhs, const constant_value::ref& rhs) const override {
    return lhs->inequality_eq(rhs);
  }
};

class ast_binary_inequality_neq : public ast_binary {
public:
  typedef std::shared_ptr<ast_binary_inequality_neq> ref;
  ast_binary_inequality_neq(const ast_type::ref& type, const ast_expression::ref& lhs, const ast_expression::ref& rhs) : ast_binary(type, lhs, rhs) {
  }
  constant_value::ref evaluate(const constant_value::ref& lhs, const constant_value::ref& rhs) const override {
    return lhs->inequality_neq(rhs);
  }
};

class ast_binary_inequality_lt : public ast_binary {
public:
  typedef std::shared_ptr<ast_binary_inequality_lt> ref;
  ast_binary_inequality_lt(const ast_type::ref& type, const ast_expression::ref& lhs, const ast_expression::ref& rhs) : ast_binary(type, lhs, rhs) {
  }
  constant_value::ref evaluate(const constant_value::ref& lhs, const constant_value::ref& rhs) const override {
    return lhs->inequality_lt(rhs);
  }
};

class ast_binary_inequality_gt : public ast_binary {
public:
  typedef std::shared_ptr<ast_binary_inequality_gt> ref;
  ast_binary_inequality_gt(const ast_type::ref& type, const ast_expression::ref& lhs, const ast_expression::ref& rhs) : ast_binary(type, lhs, rhs) {
  }
  constant_value::ref evaluate(const constant_value::ref& lhs, const constant_value::ref& rhs) const override {
    return lhs->inequality_gt(rhs);
  }
};

class ast_binary_inequality_lte : public ast_binary {
public:
  typedef std::shared_ptr<ast_binary_inequality_lte> ref;
  ast_binary_inequality_lte(const ast_type::ref& type, const ast_expression::ref& lhs, const ast_expression::ref& rhs) : ast_binary(type, lhs, rhs) {
  }
  constant_value::ref evaluate(const constant_value::ref& lhs, const constant_value::ref& rhs) const override {
    return lhs->inequality_lte(rhs);
  }
};

class ast_binary_inequality_gte : public ast_binary {
public:
  typedef std::shared_ptr<ast_binary_inequality_gte> ref;
  ast_binary_inequality_gte(const ast_type::ref& type, const ast_expression::ref& lhs, const ast_expression::ref& rhs) : ast_binary(type, lhs, rhs) {
  }
  constant_value::ref evaluate(const constant_value::ref& lhs, const constant_value::ref& rhs) const override {
    return lhs->inequality_gte(rhs);
  }
};

class ast_binary_bitwise_shl : public ast_binary {
public:
  typedef std::shared_ptr<ast_binary_bitwise_shl> ref;
  ast_binary_bitwise_shl(const ast_type::ref& type, const ast_expression::ref& lhs, const ast_expression::ref& rhs) : ast_binary(type, lhs, rhs) {
  }
  constant_value::ref evaluate(const constant_value::ref& lhs, const constant_value::ref& rhs) const override {
    return lhs->bitwise_shl(rhs);
  }
};

class ast_binary_bitwise_shr : public ast_binary {
public:
  typedef std::shared_ptr<ast_binary_bitwise_shr> ref;
  ast_binary_bitwise_shr(const ast_type::ref& type, const ast_expression::ref& lhs, const ast_expression::ref& rhs) : ast_binary(type, lhs, rhs) {
  }
  constant_value::ref evaluate(const constant_value::ref& lhs, const constant_value::ref& rhs) const override {
    return lhs->bitwise_shr(rhs);
  }
};

class ast_binary_arith_add : public ast_binary {
public:
  typedef std::shared_ptr<ast_binary_arith_add> ref;
  ast_binary_arith_add(const ast_type::ref& type, const ast_expression::ref& lhs, const ast_expression::ref& rhs) : ast_binary(type, lhs, rhs) {
  }
  constant_value::ref evaluate(const constant_value::ref& lhs, const constant_value::ref& rhs) const override {
    return lhs->arith_add(rhs);
  }
};

class ast_binary_arith_sub : public ast_binary {
public:
  typedef std::shared_ptr<ast_binary_arith_sub> ref;
  ast_binary_arith_sub(const ast_type::ref& type, const ast_expression::ref& lhs, const ast_expression::ref& rhs) : ast_binary(type, lhs, rhs) {
  }
  constant_value::ref evaluate(const constant_value::ref& lhs, const constant_value::ref& rhs) const override {
    return lhs->arith_sub(rhs);
  }
};

class ast_binary_arith_mul : public ast_binary {
public:
  typedef std::shared_ptr<ast_binary_arith_mul> ref;
  ast_binary_arith_mul(const ast_type::ref& type, const ast_expression::ref& lhs, const ast_expression::ref& rhs) : ast_binary(type, lhs, rhs) {
  }
  constant_value::ref evaluate(const constant_value::ref& lhs, const constant_value::ref& rhs) const override {
    return lhs->arith_mul(rhs);
  }
};

class ast_binary_arith_div : public ast_binary {
public:
  typedef std::shared_ptr<ast_binary_arith_div> ref;
  ast_binary_arith_div(const ast_type::ref& type, const ast_expression::ref& lhs, const ast_expression::ref& rhs) : ast_binary(type, lhs, rhs) {
  }
  constant_value::ref evaluate(const constant_value::ref& lhs, const constant_value::ref& rhs) const override {
    return lhs->arith_div(rhs);
  }
};

class ast_binary_arith_mod : public ast_binary {
public:
  typedef std::shared_ptr<ast_binary_arith_mod> ref;
  ast_binary_arith_mod(const ast_type::ref& type, const ast_expression::ref& lhs, const ast_expression::ref& rhs) : ast_binary(type, lhs, rhs) {
  }
  constant_value::ref evaluate(const constant_value::ref& lhs, const constant_value::ref& rhs) const override {
    return lhs->arith_mod(rhs);
  }
};

class ast_continue : public ast_statement {
public:
  typedef std::shared_ptr<ast_continue> ref;
};

class ast_break : public ast_statement {
public:
  typedef std::shared_ptr<ast_break> ref;
};

class ast_return : public ast_statement {
public:
  typedef std::shared_ptr<ast_return> ref;
  ast_return(const ast_expression::ref& expr) : expression_(expr) {
  }
  ast_expression::ref expression_;
};

class ast_var_struct : public ast_statement {
public:
  typedef std::shared_ptr<ast_var_struct> ref;
  ast_var_struct() {
  }
  bool is_declared(const std::string& name) const {
    return declarations_.find(name) != std::end(declarations_);
  }

  ast_var::ref declare_struct_var(const ast_type::ref type, const std::string& var_name, const location& loc) {
    auto first_declaration = declarations_.find(var_name);
    if (first_declaration != std::end(declarations_)) {
      return nullptr; /* error: var already declared */
    }

    ast_var::ref var = std::make_shared<ast_var>(type, var_name);
    var->set_loc(loc);
    declarations_[var->name()] = var;

    return var;
  }

  ast_var::ref declare_var(const ast_type::ref type, const std::string& var_name, const location& loc) {
    ast_var::ref var = declare_struct_var(type, var_name, loc);

    if (!var) {
      return nullptr;
    }

    if (type->array_type()) {

      ast_type::ref element_type;

      if (type->array_type()->dimensions() == 1) {
        element_type = type->array_type()->element_type();
      } else { /* still an array */
        ast_var_array::ref sub_array = std::make_shared<ast_var_array>(*type->array_type());
        sub_array->sizes_.erase(std::begin(sub_array->sizes_)); /* reduce dimension */
        element_type = std::make_shared<ast_type>(sub_array);
      }

      for (size_t i = 0; i < type->array_type()->sizes_[0]; ++i) {
        std::stringstream ss;
        ss << var->name() << "[" << i << "]";
        declare_var(element_type, ss.str(), loc);
      }

    } else if (type->struct_type()) {
      for (auto map_item : type->struct_type()->declarations_) {
        std::stringstream ss;
        ss << var->name() << "." << map_item.second->name();
        declare_var(map_item.second->type(), ss.str(), loc);
      }
    }

    return var;
  }
  ast_var::ref find(const std::string& name) const {
    auto map_item = declarations_.find(name);
    if (map_item != std::end(declarations_)) {
      /* clone the var to give it a unique pointer as an id */
      return std::make_shared<ast_var>(*map_item->second);
    } else {
      return nullptr;
    }
  }
  std::map<std::string, ast_var::ref> declarations_;
};

class ast_scope : public ast_var_struct {
public:
  typedef std::shared_ptr<ast_scope> ref;
  std::vector<ast_statement::ref> statements_;
};

class ast_loop : public ast_scope {
public:
  typedef std::shared_ptr<ast_loop> ref;
  ast_expression::ref condition_first_;
  ast_expression::ref condition_last_;
  ast_expression::ref increment_;
};

class ast_conditional_branch : public ast_statement {
public:
  typedef std::shared_ptr<ast_conditional_branch> ref;
  ast_expression::ref condition_;
  ast_scope::ref true_path_;
  ast_scope::ref false_path_;
};

class ast_switch : public ast_scope {
public:
  typedef std::shared_ptr<ast_switch> ref;
  ast_expression::ref expression_;
  std::map<size_t, size_t> cases_; /* expression value -> statement index */
  std::shared_ptr<size_t> default_case_; /* statement index of the default switch case */
};

class ast_function : public ast_scope {
public:
  typedef std::shared_ptr<ast_function> ref;
  std::string name() const {
    return name_;
  }
  ast_type::ref return_type() const {
    return retval_var_->type();
  }
  std::string name_;
  ast_var::ref retval_var_;
  std::vector<ast_var::ref> parameters_;
};

class ast_function_call : public ast_expression {
public:
  typedef std::shared_ptr<ast_function_call> ref;
  ast_function_call(const ast_function::ref& function) : ast_expression(function->return_type()), function_(function) {
  }
  std::vector<ast_expression::ref> sub_expressions() const override {
    return args_; /* evaluate arguments left-to-right */
  }
  ast_function::ref function_;
  ast_var::ref retval_var_;
  std::vector<ast_expression::ref> args_;
};

class ast_type_constructor : public ast_expression {
public:
  typedef std::shared_ptr<ast_type_constructor> ref;
  ast_type_constructor(const ast_type::ref& type) : ast_expression(type) {
  }
  std::vector<ast_expression::ref> sub_expressions() const override {
    return args_; /* evaluate constructor arguments left-to-right */
  }
  ast_type::ref type_;
  std::vector<ast_expression::ref> args_;
};

class ast_initializer_list : public ast_expression {
public:
  typedef std::shared_ptr<ast_initializer_list> ref;
  ast_initializer_list(const ast_type::ref& type) : ast_expression(type) {
  }
  ast_type::ref type_;
  std::vector<ast_expression::ref> args_;
};

class syntax_tree {
public:
  friend class syntax_tree_builder;
  typedef std::shared_ptr<syntax_tree> ref;
  ast_type::ref find_struct_declaration(const std::string& struct_name) const {
    auto map_item = structures_.find(struct_name);
    if (map_item != std::end(structures_)) {
      return map_item->second;
    } else {
      return nullptr;
    }
  }
  ast_function::ref find_function_definition(const std::string& function_name) const {
    auto map_item = functions_.find(function_name);
    if (map_item != std::end(functions_)) {
      return map_item->second;
    } else {
      return nullptr;
    }
  }
  std::map<std::string, ast_type::ref> structures_;
  std::map<std::string, ast_function::ref> functions_;
};

} /* namespace */

#endif /* __AST_H__ */
