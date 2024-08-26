#ifndef __CONSTANT_VALUE_INTEGER_H__
#define __CONSTANT_VALUE_INTEGER_H__

/* the arithmetic implementation for "big integer" types */

#include "type_factory.h"
#include "constant_value.h"
#include "constant_value_boolean.h"
#include "constant_value_nan.h"
#include "integer.h"

namespace clike {

class constant_value_integer : public constant_value {
public:
  typedef std::shared_ptr<constant_value_integer> ref;
  constant_value_integer(const integer& value) : value_(value) {
  }
  const integer& value() const {
    return value_;
  }
  constant_value::ref unary_arith_negate() const override {
    return std::make_shared<constant_value_integer>(-value_);
  }
  constant_value::ref unary_bitwise_negate() const override {
    return std::make_shared<constant_value_integer>(value_.unary_bitwise_negate());
  }
  constant_value::ref unary_logical_negate() const override {
    return std::make_shared<constant_value_boolean>(value_.is_zero() ? 1 : 0);
  }
  constant_value::ref unary_logical_value() const override {
    /* interpret the value as boolean */
    return std::make_shared<constant_value_boolean>(value_.is_zero() ? 0 : 1);
  }
  constant_value::ref inequality_eq(const constant_value::ref& rhs) const override {
    constant_value::ref ret;
    constant_value_integer::ref rhs_int = std::dynamic_pointer_cast<constant_value_integer>(rhs);
    if (rhs_int) {
      uint64_t result_value = (value_ == rhs_int->value() ? 1 : 0);
      ret = std::make_shared<constant_value_boolean>(result_value);
    }
    return ret;
  }
  constant_value::ref inequality_neq(const constant_value::ref& rhs) const override {
    constant_value::ref ret;
    constant_value_integer::ref rhs_int = std::dynamic_pointer_cast<constant_value_integer>(rhs);
    if (rhs_int) {
      uint64_t result_value = (value_ != rhs_int->value() ? 1 : 0);
      ret = std::make_shared<constant_value_boolean>(result_value);
    }
    return ret;
  }
  constant_value::ref inequality_lt(const constant_value::ref& rhs) const override {
    constant_value::ref ret;
    constant_value_integer::ref rhs_int = std::dynamic_pointer_cast<constant_value_integer>(rhs);
    if (rhs_int) {
      uint64_t result_value = (value_ < rhs_int->value() ? 1 : 0);
      ret = std::make_shared<constant_value_boolean>(result_value);
    }
    return ret;
  }
  constant_value::ref arith_add(const constant_value::ref& rhs) const override {
    constant_value::ref ret;
    constant_value_integer::ref rhs_int = std::dynamic_pointer_cast<constant_value_integer>(rhs);
    if (rhs_int) {
      integer result_value = (value_ + rhs_int->value());
      ret = std::make_shared<constant_value_integer>(result_value);
    }
    return ret;
  }
  constant_value::ref arith_sub(const constant_value::ref& rhs) const override {
    constant_value::ref ret;
    constant_value_integer::ref rhs_int = std::dynamic_pointer_cast<constant_value_integer>(rhs);
    if (rhs_int) {
      integer result_value = (value_ - rhs_int->value());
      ret = std::make_shared<constant_value_integer>(result_value);
    }
    return ret;
  }
  constant_value::ref arith_mul(const constant_value::ref& rhs) const override {
    constant_value::ref ret;
    constant_value_integer::ref rhs_int = std::dynamic_pointer_cast<constant_value_integer>(rhs);
    if (rhs_int) {
      integer result_value = (value_ * rhs_int->value());
      ret = std::make_shared<constant_value_integer>(result_value);
    }
    return ret;
  }
  constant_value::ref arith_div(const constant_value::ref& rhs) const override {
    constant_value::ref ret;
    constant_value_integer::ref rhs_int = std::dynamic_pointer_cast<constant_value_integer>(rhs);
    if (rhs_int) {
      integer rhs_value = rhs_int->value();
      if (rhs_value.is_zero()) {
        ret = std::make_shared<constant_value_nan>(constant_value_nan::nan_zero_divide);
      } else {
        integer result_value = (value_ / rhs_value);
        ret = std::make_shared<constant_value_integer>(result_value);
      }
    }
    return ret;
  }
  integer value_;
};

class integer_type_factory : public type_factory {
public:
  typedef std::shared_ptr<integer_type_factory> ref;
  integer_type_factory(const std::string& name, const digit_vector& modulus) : type_factory(name) {
    modulus_ = std::make_shared<digit_vector>(modulus);
  }
  constant_value::ref construct_value(const std::vector<constant_value::ref>& args) const override {
    typename constant_value_integer::ref result;
    if (args.empty()) {
      return std::make_shared<constant_value_integer>(integer(modulus_));
    } else if (args.size() == 1) {
      return nullptr;
    }
    return result;
  }
  constant_value::ref implicit_cast_value(const constant_value::ref& src_value) const override {
    std::vector<constant_value::ref> args = {src_value};
    return construct_value(args);
  }
  constant_value::ref uninitialized_value() const override {
    return std::make_shared<constant_value_integer>(integer(modulus_));
  }
  constant_value::ref representative_value() const override {
    return std::make_shared<constant_value_integer>(integer({1}, modulus_));
  }
  digit_vector::ref modulus_;
};

} /* namespace */

#endif /* __CONSTANT_VALUE_INTEGER_H__ */
