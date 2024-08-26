#include "ast_type.h"
#include "ast.h"

namespace clike {

ast_type::~ast_type() {
}

ast_type::ast_type(const std::string& type_name) : type_name_(type_name), const_(true) {
}

ast_type::ast_type(const std::shared_ptr<ast_var_struct>& struct_type, const std::string& struct_name) : type_name_(struct_name), struct_(struct_type), const_(true) {
}

ast_type::ast_type(const std::shared_ptr<ast_var_array>& array) : type_name_(array->array_type_name()), array_(array), const_(true) {
}

std::string ast_type::type_name() const {
  return type_name_;
}

std::shared_ptr<ast_var_struct> ast_type::struct_type() const {
  return struct_;
}

std::shared_ptr<ast_var_array> ast_type::array_type() const {
  return array_;
}

bool ast_type::is_const() const {
  return const_;
}

void ast_type::set_const(const bool is_const) {
  const_ = is_const;
}

location ast_type::loc() const {
  return loc_;
}

void ast_type::set_loc(const location& loc) {
  loc_ = loc;
}

} /* namespace */
