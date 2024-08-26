#ifndef __CONSTANT_VALUE_INTEGER_VECTOR_H__
#define __CONSTANT_VALUE_INTEGER_VECTOR_H__

/* the arithmetic implementation for "big integer" vector types */

#include "type_factory.h"
#include "constant_value.h"
#include "integer.h"
#include "vector.h"

namespace clike {

class constant_value_integer_vector : public constant_value {
public:
  typedef std::shared_ptr<constant_value_integer_vector> ref;
  constant_value_integer_vector(const vector<integer>& value) : value_(value) {
  }
  const vector<integer>& value() const {
    return value_;
  }
  constant_value::ref unary_arith_negate() const override {
    return std::make_shared<constant_value_integer_vector>(-value_);
  }
  constant_value::ref arith_add(const constant_value::ref& rhs) const override {
    std::shared_ptr<constant_value_integer_vector> rhs_int = std::dynamic_pointer_cast<constant_value_integer_vector>(rhs);
    if (rhs_int) {
      vector<integer> result_value = (value_ + rhs_int->value());
      return std::make_shared<constant_value_integer_vector>(result_value);
    }
    throw std::runtime_error("Integer vector ADD not defined for RHS type");
    return nullptr;
  }
  vector<integer> value_;
};

class integer_vector_type_factory : public type_factory {
public:
  typedef std::shared_ptr<integer_vector_type_factory> ref;
  integer_vector_type_factory(const std::string& name, const std::string& element_name, const digit_vector& modulus) : type_factory(name, element_name) {
    modulus_ = std::make_shared<digit_vector>(modulus);
  }
  constant_value::ref construct_value(const std::vector<constant_value::ref>& args) const override {
    constant_value::ref result;
    if (args.empty()) {
      result = std::make_shared<constant_value_integer_vector>(vector<integer>()); /* constructor called with no arguments */
    } else if (args.size() == 1) {
      size_t new_vector_length = 0;
      if (args[0]->get_numeric_value(&new_vector_length)) {
        vector<integer> empty_vector(new_vector_length, integer(modulus_));
        result = std::make_shared<constant_value_integer_vector>(empty_vector);
      }
    } else {
      throw std::runtime_error("Too many arguments to vector constructor");
    }
    return result;
  }
  constant_value::ref implicit_cast_value(const constant_value::ref& src_value) const override {
    std::vector<constant_value::ref> args = {src_value};
    return construct_value(args);
  }
  constant_value::ref uninitialized_value() const override {
    return std::make_shared<constant_value_integer_vector>(vector<integer>());
  }
  constant_value::ref representative_value() const override {
    return std::make_shared<constant_value_integer_vector>(vector<integer>(1, integer({1}, modulus_)));
  }
  digit_vector::ref modulus_;
};

} /* namespace */

#endif /* __CONSTANT_VALUE_INTEGER_VECTOR_H__ */
