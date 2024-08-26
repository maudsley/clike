#ifndef __TYPE_SYSTEM_H__
#define __TYPE_SYSTEM_H__

/* the type system manages all user defined types exposed in the c-like language. */

#include "constant_value.h"
#include "constant_value_builtin.h"
#include "constant_value_integer.h"
#include "constant_value_literal.h"
#include <map>

namespace clike {

/* the type system can create instances of any registered type */
class type_system {
public:

  typedef std::shared_ptr<type_system> ref;

  type_system() {
  }

  std::vector<std::string> all_type_names() const {
    std::vector<std::string> type_names;
    for (auto map_item : types_) {
      type_names.push_back(map_item.first);
    }
    return type_names;
  }

  type_factory::ref find_type(const std::string& type_name) const {
    auto map_item = types_.find(type_name);
    if (map_item == std::end(types_)) {
      return nullptr;
    } else {
      return map_item->second;
    }
  }

  bool register_type(const type_factory::ref& factory) {
    if (types_.find(factory->type_name()) != std::end(types_)) {
      return false;
    }

    types_[factory->type_name()] = factory;

    /* re-register the literal type after finding the max modulus */
    size_t max_modulus_digits = 1; /* default to 64 bits */

    for (auto map_item : types_) {
      integer_type_factory::ref integer_factory = std::dynamic_pointer_cast<integer_type_factory>(map_item.second);
      if (integer_factory && (map_item.first != literal_type_name())) {
        max_modulus_digits = std::max(max_modulus_digits, integer_factory->modulus_->size());
      }
    }

    digit_vector modulus_digits(max_modulus_digits); /* zeros */
    modulus_digits.push_back(1); /* leading bit */

    types_[literal_type_name()] = std::make_shared<literal_type_factory>(literal_type_name(), modulus_digits);

    return true;
  }

  void register_builtin_integer_types() {
    register_type(std::make_shared<builtin_integer_type_factory<int8_t>>("int8_t"));
    register_type(std::make_shared<builtin_integer_type_factory<int16_t>>("int16_t"));
    register_type(std::make_shared<builtin_integer_type_factory<int32_t>>("int32_t"));
    register_type(std::make_shared<builtin_integer_type_factory<int64_t>>("int64_t"));
    register_type(std::make_shared<builtin_integer_type_factory<uint8_t>>("uint8_t"));
    register_type(std::make_shared<builtin_integer_type_factory<uint16_t>>("uint16_t"));
    register_type(std::make_shared<builtin_integer_type_factory<uint32_t>>("uint32_t"));
    register_type(std::make_shared<builtin_integer_type_factory<uint64_t>>("uint64_t"));
  }

  std::string array_type_name(const std::string& type_name) const {
    std::string name;
    type_factory::ref factory = find_type(type_name);
    if (factory) {
      name = factory->array_type_name();
    }
    return name;
  }

  bool is_integral_type(const std::string& type_name) const {
    bool is_integral = false;
    constant_value::ref value = representative_value(type_name);
    if (value) {
      size_t integral_value = 0;
      if (value->get_numeric_value(&integral_value)) {
        is_integral = true;
      }
    }
    return is_integral;
  }

  constant_value::ref uninitialized_value(const std::string& type_name) const {
    constant_value::ref result;
    type_factory::ref factory = find_type(type_name);
    if (factory) {
      result = factory->uninitialized_value();
    }
    return result;
  }

  /* similar to uninitialized value, but we return a non-zero "representative" for type resolution */
  constant_value::ref representative_value(const std::string& type_name) const {
    constant_value::ref result;
    type_factory::ref factory = find_type(type_name);
    if (factory) {
      result = factory->representative_value();
    }
    return result;
  }

  constant_value::ref construct_value(const std::string& type_name, const std::vector<constant_value::ref>& args) const {
    constant_value::ref result;
    type_factory::ref factory = find_type(type_name);
    if (factory) {
      if (args.empty()) {
        result = factory->uninitialized_value();
      } else {
        result = factory->construct_value(args);
      }
    }
    return result;
  }

  constant_value::ref implicit_cast_value(const std::string& dest_type_name, const constant_value::ref& value) const {
    constant_value::ref result;
    type_factory::ref dest_factory = find_type(dest_type_name);
    if (dest_factory) {
      result =  dest_factory->implicit_cast_value(value);
    }
    return result;
  }

  std::string literal_type_name() const {
    /* type to hold largest representable integer */
    return "literal_t";
  }

  std::string literal_promotion_type_name() const {
    /* when operations are applied to a literal it becomes this builtin type */
    return "int64_t";
  }

  std::string boolean_type_name() const {
    /* could have a dedicated boolean type, but not needed at the moment */
    /* use a small uint so that it can be converted to other sizes without a cast */
    return "uint8_t";
  }

  std::string default_type_for_error_recovery() const {
    /* if a variable is undeclared we will assume this type in order to continue with parsing */
    return "uint64_t";
  }

private:

  std::map<std::string, type_factory::ref> types_;

};

} /* namespace */

#endif /* __TYPE_SYSTEM_H__ */
