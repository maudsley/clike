#include "test_common.h"
#include "test_type_factories.h"
#include "clike/interpreter.h"
#include "clike/ast_builder.h"
#include <iostream>
#include <fstream>

BasicTestInterpreter::BasicTestInterpreter(const std::string& name) : file_name_(name) {
  type_system_ = std::make_shared<clike::type_system>();
  type_system_->register_builtin_integer_types();
  type_system_->register_type(std::make_shared<clike::external_vector_factory>());
  type_system_->register_type(std::make_shared<clike::external_matrix_factory>());

  const std::string source_file = "./test/resources/" + file_name_;
  std::ifstream file(source_file);
  if (!file.is_open()) {
    std::cout << "Unable to load source file: " + source_file << std::endl;
    return;
  }

  std::unique_ptr<clike::syntax_tree_builder> builder(new clike::syntax_tree_builder(type_system_));
  std::string file_content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
  builder->parse(file_content);

  ast_ = builder->tree();
  errors_ = builder->parser_errors();

  if (!errors_.empty()) {
    for (const clike::location_error& error : errors_) {
      std::cout << file_name_ << ":" << error.loc_.begin.line << ": error: " << error.message_ << std::endl;
    }
    ast_ = nullptr;
  }
}

uint64_t BasicTestInterpreter::evaluate() {
  std::unique_ptr<clike::interpreter> interpreter(new clike::interpreter(ast_, type_system_));
  clike::ast_expression::ref ret_expr;
  try {
    ret_expr = interpreter->run("test", {});
  } catch (clike::interpreter_exception&) {
  }

  std::vector<clike::location_error> interpreter_errors = interpreter->interpreter_errors();
  errors_.insert(std::end(errors_), std::begin(interpreter_errors), std::end(interpreter_errors));
  if (!errors_.empty()) {
    for (const clike::location_error& error : errors_) {
      std::cout << file_name_ << ":" << error.loc_.begin.line << ": error: " << error.message_ << std::endl;
    }
    return 0;
  }

  clike::constant_value::ref ret_value = interpreter->read_value(ret_expr);
  clike::constant_value_builtin<uint64_t>::ref ret_int = std::dynamic_pointer_cast<clike::constant_value_builtin<uint64_t>>(ret_value);
  if (!ret_int) {
    return 0;
  }

  return ret_int->value_;
}

uint64_t BasicTestInterpreter::evaluate(const uint64_t x) {
  std::unique_ptr<clike::interpreter> interpreter(new clike::interpreter(ast_, type_system_));
  std::vector<clike::constant_value::ref> ast_parameters;
  ast_parameters.push_back(std::make_shared<clike::constant_value_builtin<uint64_t>>(x));
  clike::ast_expression::ref ret_expr = interpreter->run("test", ast_parameters);
  clike::constant_value::ref ret_value = interpreter->read_value(ret_expr);
  clike::constant_value_builtin<uint64_t>::ref ret_int = std::dynamic_pointer_cast<clike::constant_value_builtin<uint64_t>>(ret_value);
  if (!ret_int) {
    return 0;
  }
  return ret_int->value_;
}

bool BasicTestInterpreter::error_on_line(const size_t line_number) const {
  bool found_error = false;
  for (const clike::location_error& error : errors_) {
    if (error.loc().begin.line == line_number) {
      found_error = true;
      break;
    }
  }
  return found_error;
}
