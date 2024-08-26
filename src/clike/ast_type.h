#ifndef __AST_TYPE_H__
#define __AST_TYPE_H__

/* holds type information for AST nodes */

#include "location.hh"
#include <memory>
#include <string>

namespace clike {

class ast_var_struct;
class ast_var_array;

class ast_type {
public:
  typedef std::shared_ptr<ast_type> ref;

  virtual ~ast_type();
  ast_type(const std::string& type_name);
  ast_type(const std::shared_ptr<ast_var_struct>& struct_type, const std::string& struct_name);
  ast_type(const std::shared_ptr<ast_var_array>& array);

  std::string type_name() const; /* cannot change the type name after construction */

  std::shared_ptr<ast_var_struct> struct_type() const;
  std::shared_ptr<ast_var_array> array_type() const;

  bool is_const() const;
  void set_const(const bool is_const);

  location loc() const;
  void set_loc(const location& loc);

private:

  std::string type_name_;
  std::shared_ptr<ast_var_struct> struct_;
  std::shared_ptr<ast_var_array> array_;
  bool const_; /* is read-only */
  location loc_;

};

} /* namespace */

#endif /* __AST_TYPE_H__ */
