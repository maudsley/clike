#ifndef __CONSTANT_VALUE_BUILTIN_H__
#define __CONSTANT_VALUE_BUILTIN_H__

/* the arithmetic implementation for basic integer types */

#include "type_factory.h"
#include "constant_value_literal.h"
#include "constant_value_boolean_type.h"
#include "constant_value_nan.h"
#include <memory>
#include <vector>

namespace clike {

template <typename T> class constant_value_builtin : public constant_value {
public:
  typedef std::shared_ptr<constant_value_builtin> ref;
  typedef constant_value_builtin<constant_value_boolean_type> constant_value_boolean;
  constant_value_builtin() : value_(0) {
  }
  constant_value_builtin(const T value) : value_(value) {
  }
  static size_t num_bits() {
    return sizeof(T) * 8;
  }
  static bool is_signed() {
    return T(-1) < T(0);
  }
  T value() const {
    return value_;
  }
  bool get_numeric_value(size_t* value) const override {
    bool ok = false;
    if (value) {
      *value = size_t(value_);
      ok = true;
    }
    return ok;
  }
  bool integer_cast(T* result_value, const constant_value::ref& rhs) const {
    bool value_ok = false;
    if (std::dynamic_pointer_cast<constant_value_builtin<T>>(rhs)) {
      *result_value = std::dynamic_pointer_cast<constant_value_builtin<T>>(rhs)->value();
      value_ok = true;
    }
    return value_ok;
  }
  constant_value::ref unary_arith_negate() const override {
    return std::make_shared<constant_value_builtin<T>>(-value_);
  }
  constant_value::ref unary_bitwise_negate() const override {
    return std::make_shared<constant_value_builtin<T>>(~value_);
  }
  constant_value::ref unary_logical_negate() const override {
    return std::make_shared<constant_value_boolean>((value_ == 0) ? 1 : 0);
  }
  constant_value::ref unary_logical_value() const override {
    /* interpret the value as boolean */
    return std::make_shared<constant_value_boolean>((value_ == 0) ? 0 : 1);
  }
  constant_value::ref logical_or(const constant_value::ref& rhs) const override {
    /* note that this is only used for static type checking. the interpreter does not use it because of short-circuiting. */
    std::shared_ptr<constant_value_boolean> ret;
    T rhs_value = 0;
    if (integer_cast(&rhs_value, rhs)) {
      T result_value = ((value_ || rhs_value) ? 1 : 0);
      ret = std::make_shared<constant_value_boolean>(result_value);
    }
    return ret;
  }
  constant_value::ref logical_and(const constant_value::ref& rhs) const override {
    /* note that this is only used for static type checking. the interpreter does not use it because of short-circuiting. */
    std::shared_ptr<constant_value_boolean> ret;
    T rhs_value = 0;
    if (integer_cast(&rhs_value, rhs)) {
      T result_value = ((value_ && rhs_value) ? 1 : 0);
      ret = std::make_shared<constant_value_boolean>(result_value);
    }
    return ret;
  }
  constant_value::ref bitwise_or(const constant_value::ref& rhs) const override {
    constant_value_builtin<T>::ref ret;
    T rhs_value = 0;
    if (integer_cast(&rhs_value, rhs)) {
      T result_value = (value_ | rhs_value);
      ret = std::make_shared<constant_value_builtin<T>>(result_value);
    }
    return ret;
  }
  constant_value::ref bitwise_xor(const constant_value::ref& rhs) const override {
    constant_value_builtin<T>::ref ret;
    T rhs_value = 0;
    if (integer_cast(&rhs_value, rhs)) {
      T result_value = (value_ ^ rhs_value);
      ret = std::make_shared<constant_value_builtin<T>>(result_value);
    }
    return ret;
  }
  constant_value::ref bitwise_and(const constant_value::ref& rhs) const override {
    constant_value_builtin<T>::ref ret;
    T rhs_value = 0;
    if (integer_cast(&rhs_value, rhs)) {
      T result_value = (value_ & rhs_value);
      ret = std::make_shared<constant_value_builtin<T>>(result_value);
    }
    return ret;
  }
  constant_value::ref inequality_eq(const constant_value::ref& rhs) const override {
    std::shared_ptr<constant_value_boolean> ret;
    T rhs_value = 0;
    if (integer_cast(&rhs_value, rhs)) {
      T result_value = (value_ == rhs_value ? 1 : 0);
      ret = std::make_shared<constant_value_boolean>(result_value);
    }
    return ret;
  }
  constant_value::ref inequality_neq(const constant_value::ref& rhs) const override {
    std::shared_ptr<constant_value_boolean> ret;
    T rhs_value = 0;
    if (integer_cast(&rhs_value, rhs)) {
      T result_value = (value_ != rhs_value ? 1 : 0);
      ret = std::make_shared<constant_value_boolean>(result_value);
    }
    return ret;
  }
  constant_value::ref inequality_lt(const constant_value::ref& rhs) const override {
    std::shared_ptr<constant_value_boolean> ret;
    T rhs_value = 0;
    if (integer_cast(&rhs_value, rhs)) {
      T result_value = (value_ < rhs_value ? 1 : 0);
      ret = std::make_shared<constant_value_boolean>(result_value);
    }
    return ret;
  }
  constant_value::ref inequality_gt(const constant_value::ref& rhs) const override {
    std::shared_ptr<constant_value_boolean> ret;
    T rhs_value = 0;
    if (integer_cast(&rhs_value, rhs)) {
      T result_value = (value_ > rhs_value ? 1 : 0);
      ret = std::make_shared<constant_value_boolean>(result_value);
    }
    return ret;
  }
  constant_value::ref inequality_lte(const constant_value::ref& rhs) const override {
    std::shared_ptr<constant_value_boolean> ret;
    T rhs_value = 0;
    if (integer_cast(&rhs_value, rhs)) {
      T result_value = (value_ <= rhs_value ? 1 : 0);
      ret = std::make_shared<constant_value_boolean>(result_value);
    }
    return ret;
  }
  constant_value::ref inequality_gte(const constant_value::ref& rhs) const override {
    std::shared_ptr<constant_value_boolean> ret;
    T rhs_value = 0;
    if (integer_cast(&rhs_value, rhs)) {
      T result_value = (value_ >= rhs_value ? 1 : 0);
      ret = std::make_shared<constant_value_boolean>(result_value);
    }
    return ret;
  }
  constant_value::ref bitwise_shl(const constant_value::ref& rhs) const override {
    constant_value_builtin<T>::ref ret;
    T rhs_value = 0;
    if (integer_cast(&rhs_value, rhs)) {
      size_t shift_size = size_t(rhs_value);
      T result_value = 0;
      if (shift_size < (sizeof(T) * 8)) {
        result_value = (value_ << shift_size);
      }
      ret = std::make_shared<constant_value_builtin<T>>(result_value);
    }
    return ret;
  }
  constant_value::ref bitwise_shr(const constant_value::ref& rhs) const override {
    constant_value_builtin<T>::ref ret;
    T rhs_value = 0;
    if (integer_cast(&rhs_value, rhs)) {
      size_t shift_size = size_t(rhs_value);
      T result_value = 0;
      if (shift_size < (sizeof(T) * 8)) {
        result_value = (value_ >> shift_size);
      }
      ret = std::make_shared<constant_value_builtin<T>>(result_value);
    }
    return ret;
  }
  constant_value::ref arith_add(const constant_value::ref& rhs) const override {
    constant_value_builtin<T>::ref ret;
    T rhs_value = 0;
    if (integer_cast(&rhs_value, rhs)) {
      T result_value = (value_ + rhs_value);
      ret = std::make_shared<constant_value_builtin<T>>(result_value);
    }
    return ret;
  }
  constant_value::ref arith_sub(const constant_value::ref& rhs) const override {
    constant_value_builtin<T>::ref ret;
    T rhs_value = 0;
    if (integer_cast(&rhs_value, rhs)) {
      T result_value = (value_ - rhs_value);
      ret = std::make_shared<constant_value_builtin<T>>(result_value);
    }
    return ret;
  }
  constant_value::ref arith_mul(const constant_value::ref& rhs) const override {
    constant_value_builtin<T>::ref ret;
    T rhs_value = 0;
    if (integer_cast(&rhs_value, rhs)) {
      T result_value = (value_ * rhs_value);
      ret = std::make_shared<constant_value_builtin<T>>(result_value);
    }
    return ret;
  }
  constant_value::ref arith_div(const constant_value::ref& rhs) const override {
    constant_value::ref ret;
    T rhs_value = 0;
    if (integer_cast(&rhs_value, rhs)) {
      if (rhs_value == 0) {
        ret = std::make_shared<constant_value_nan>(constant_value_nan::nan_zero_divide);
      } else {
        T result_value = (value_ / rhs_value);
        ret = std::make_shared<constant_value_builtin<T>>(result_value);
      }
    }
    return ret;
  }
  constant_value::ref arith_mod(const constant_value::ref& rhs) const override {
    constant_value::ref ret;
    T rhs_value = 0;
    if (integer_cast(&rhs_value, rhs)) {
      if (rhs_value == 0) {
        ret = std::make_shared<constant_value_nan>(constant_value_nan::nan_zero_divide);
      } else {
        T result_value = (value_ % rhs_value);
        ret = std::make_shared<constant_value_builtin<T>>(result_value);
      }
    }
    return ret;
  }
  T value_;
};

/* this type factory covers builtin integer types: uint64_t, int8_t, .etc */
template <typename T> class builtin_integer_type_factory : public type_factory {
public:
  typedef std::shared_ptr<builtin_integer_type_factory> ref;
  builtin_integer_type_factory(const std::string& name) : type_factory(name) {
  }
  enum cast_type {cast_explicit, cast_implicit};
  template <typename S> constant_value::ref builtin_cast_value(const constant_value::ref& src_value, const cast_type type) const {
    constant_value::ref result;
    bool do_cast = false;
    if (type == cast_explicit) {
      do_cast = true; /* explicit cast: truncate if necessary */
    } else { /* implicit cast: avoid truncation and sign changes */
      if (constant_value_builtin<T>::is_signed() == constant_value_builtin<S>::is_signed()) {
        if (constant_value_builtin<T>::num_bits() >= constant_value_builtin<S>::num_bits()) {
          do_cast = true; /* allow implicit cast */
        }
      }
    }
    if (do_cast) {
      typename constant_value_builtin<S>::ref value = std::dynamic_pointer_cast<constant_value_builtin<S>>(src_value);
      if (value) {
        result = std::make_shared<constant_value_builtin<T>>(value->value_);
      }
    }
    return result;
  }
  constant_value::ref builtin_cast_value_all(const constant_value::ref& src_value, const cast_type type) const {
    constant_value::ref result;
    if ((result = builtin_cast_value<int8_t>(src_value, type))) {
      return result;
    } else if ((result = builtin_cast_value<int16_t>(src_value, type))) {
      return result;
    } else if ((result = builtin_cast_value<int32_t>(src_value, type))) {
      return result;
    } else if ((result = builtin_cast_value<int64_t>(src_value, type))) {
      return result;
    } else if ((result = builtin_cast_value<uint8_t>(src_value, type))) {
      return result;
    } else if ((result = builtin_cast_value<uint16_t>(src_value, type))) {
      return result;
    } else if ((result = builtin_cast_value<uint32_t>(src_value, type))) {
      return result;
    } else if ((result = builtin_cast_value<uint64_t>(src_value, type))) {
      return result;
    }
    return nullptr; /* no cast possible */
  }
  constant_value::ref construct_value(const std::vector<constant_value::ref>& args) const override {
    constant_value::ref result;
    if (args.size() == 1) {
      result = implicit_cast_value(args[0]); /* try cast conversion first */
      if (!result) {
        result = builtin_cast_value_all(args[0], cast_explicit); /* try truncation */
      }
    }
    return result;
  }
  constant_value::ref implicit_cast_value(const constant_value::ref& src_value) const override {
    constant_value::ref result;
    if (std::dynamic_pointer_cast<constant_value_literal>(src_value)) {
      constant_value_literal::ref literal = std::dynamic_pointer_cast<constant_value_literal>(src_value);
      if (literal->value_.is_zero()) {
        result = std::make_shared<constant_value_builtin<T>>(0);
      } else { /* truncate */
        result = std::make_shared<constant_value_builtin<T>>(literal->value_.digits_.at(0));
      }
    } else {
      result = builtin_cast_value_all(src_value, cast_implicit);
    }
    return result;
  }
  constant_value::ref uninitialized_value() const override {
    return std::make_shared<constant_value_builtin<T>>(0);
  }
  constant_value::ref representative_value() const override {
    return std::make_shared<constant_value_builtin<T>>(1);
  }
};

} /* namespace */

#endif /* __CONSTANT_VALUE_BUILTIN_H__ */
