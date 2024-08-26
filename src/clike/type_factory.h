#ifndef __TYPE_FACTORY_H__
#define __TYPE_FACTORY_H__

/* a type factory exposes a C++ class with overloaded arithmetic operators in the c-like language. */

#include "constant_value.h"
#include <memory>
#include <string>

namespace clike {

class type_factory {
public:
  typedef std::shared_ptr<type_factory> ref;

  virtual ~type_factory() {
  }

  type_factory(const std::string& type_name) : type_name_(type_name) {
  }

  type_factory(const std::string& type_name, const std::string& array_type_name) : type_name_(type_name), array_type_name_(array_type_name) {
  }

  /* the name of the type that this factory is able to construct */
  std::string type_name() const {
    return type_name_;
  }

  /* if the type supports array access, this is the array element type */
  std::string array_type_name() const {
    return array_type_name_;
  }

  virtual constant_value::ref construct_value(const std::vector<constant_value::ref>& args) const {
    throw std::runtime_error("Type factory constructor not implemented");
  }

  virtual constant_value::ref implicit_cast_value(const constant_value::ref& src_value) const {
    throw std::runtime_error("Type factory implicit cast not implemented");
  }

  /* a default constructor for this type */
  virtual constant_value::ref uninitialized_value() const {
    throw std::runtime_error("Type factory uninitialized value not implemented");
  }

  /* similar to uninitialized value, but we return a non-zero "representitive" for type resolution */
  virtual constant_value::ref representative_value() const {
    throw std::runtime_error("Type factory representative value not implemented");
  }

private:

  std::string type_name_;
  std::string array_type_name_;

};

} /* namespace */

#endif /* __TYPE_FACTORY_H__ */
