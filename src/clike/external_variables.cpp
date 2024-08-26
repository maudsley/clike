#include "external_variables.h"

namespace clike {

external_variables::external_variables() {
}

void external_variables::add_var(const std::string& type, const std::string& name, const constant_value::ref& value) {
  if (!parser_scope_) {
    parser_scope_ = std::make_shared<ast_scope>();
  }

  ast_var::ref var = parser_scope_->declare_var(std::make_shared<ast_type>(type), name, location());

  vars_.push_back(var);

  values_[var] = value;
}

constant_value::ref external_variables::value(const ast_var::ref& var) const {
  constant_value::ref value;
  auto map_item = values_.find(var);
  if (map_item != std::end(values_)) {
    value = map_item->second;
  }
  return value;
}

} /* namespace */
