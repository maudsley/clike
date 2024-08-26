#ifndef __EXTERNAL_VARIABLES_H__
#define __EXTERNAL_VARIABLES_H__

#include "ast.h"
#include <memory>
#include <vector>
#include <string>

namespace clike {

class external_variables {
public:
  typedef std::shared_ptr<external_variables> ref;
  external_variables();
  ast_scope::ref parser_scope() const {return parser_scope_;}
  void add_var(const std::string& type, const std::string& name, const constant_value::ref& value);
  std::vector<ast_var::ref> all_vars() const {return vars_;}
  constant_value::ref value(const ast_var::ref& var) const;
private:
  ast_scope::ref parser_scope_;
  std::vector<ast_var::ref> vars_;
  std::map<ast_var::ref, constant_value::ref> values_;
};

} /* namespace */

#endif /* __EXTERNAL_VARIABLES_H__ */
