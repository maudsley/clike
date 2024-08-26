#include "constant_value_literal.h"
#include "constant_value_builtin.h"
#include "constant_value_boolean.h"

namespace clike {

constant_value_literal::constant_value_literal(const integer& value) : value_(value) {
}

const integer& constant_value_literal::value() const {
  return value_;
}

constant_value::ref constant_value_literal::builtin_integer_constant() const {
  constant_value_builtin<builtin_type>::ref result;
  if (value_.is_zero()) {
    result = std::make_shared<constant_value_builtin<builtin_type>>(0);
  } else { /* truncate */
    result = std::make_shared<constant_value_builtin<builtin_type>>(value_.at(0));
  }
  return result;
}

/* todo: generate error if literal size exceeds native integer size */
bool constant_value_literal::get_numeric_value(size_t* value) const {
  bool ok = false;
  if (value) {
    if (value_.is_zero()) {
      *value = 0;
      ok = true;
    } else {
      *value = size_t(value_.at(0));
      ok = true;
    }
  }
  return ok;
}

constant_value::ref constant_value_literal::unary_arith_negate() const {
  return builtin_integer_constant()->unary_arith_negate();
}

constant_value::ref constant_value_literal::unary_bitwise_negate() const {
  return builtin_integer_constant()->unary_bitwise_negate();
}

constant_value::ref constant_value_literal::unary_logical_negate() const {
  return builtin_integer_constant()->unary_logical_negate();
}

constant_value::ref constant_value_literal::unary_logical_value() const {
  return builtin_integer_constant()->unary_logical_value();
}

constant_value::ref constant_value_literal::bitwise_or(const constant_value::ref& rhs) const {
  constant_value::ref ret;
  constant_value_literal::ref rhs_literal = std::dynamic_pointer_cast<constant_value_literal>(rhs);
  if (rhs_literal) {
    constant_value::ref lhs_value = builtin_integer_constant();
    constant_value::ref rhs_value = rhs_literal->builtin_integer_constant();
    ret = lhs_value->bitwise_or(rhs_value);
  }
  return ret;
}

constant_value::ref constant_value_literal::bitwise_xor(const constant_value::ref& rhs) const {
  constant_value::ref ret;
  constant_value_literal::ref rhs_literal = std::dynamic_pointer_cast<constant_value_literal>(rhs);
  if (rhs_literal) {
    constant_value::ref lhs_value = builtin_integer_constant();
    constant_value::ref rhs_value = rhs_literal->builtin_integer_constant();
    ret = lhs_value->bitwise_xor(rhs_value);
  }
  return ret;
}

constant_value::ref constant_value_literal::bitwise_and(const constant_value::ref& rhs) const {
  constant_value::ref ret;
  constant_value_literal::ref rhs_literal = std::dynamic_pointer_cast<constant_value_literal>(rhs);
  if (rhs_literal) {
    constant_value::ref lhs_value = builtin_integer_constant();
    constant_value::ref rhs_value = rhs_literal->builtin_integer_constant();
    ret = lhs_value->bitwise_and(rhs_value);
  }
  return ret;
}

constant_value::ref constant_value_literal::inequality_eq(const constant_value::ref& rhs) const {
  constant_value::ref ret;
  constant_value_literal::ref rhs_literal = std::dynamic_pointer_cast<constant_value_literal>(rhs);
  if (rhs_literal) {
    constant_value::ref lhs_value = builtin_integer_constant();
    constant_value::ref rhs_value = rhs_literal->builtin_integer_constant();
    ret = lhs_value->inequality_eq(rhs_value);
  }
  return ret;
}

constant_value::ref constant_value_literal::inequality_neq(const constant_value::ref& rhs) const {
  constant_value::ref ret;
  constant_value_literal::ref rhs_literal = std::dynamic_pointer_cast<constant_value_literal>(rhs);
  if (rhs_literal) {
    constant_value::ref lhs_value = builtin_integer_constant();
    constant_value::ref rhs_value = rhs_literal->builtin_integer_constant();
    ret = lhs_value->inequality_neq(rhs_value);
  }
  return ret;
}

constant_value::ref constant_value_literal::inequality_lt(const constant_value::ref& rhs) const {
  constant_value::ref ret;
  constant_value_literal::ref rhs_literal = std::dynamic_pointer_cast<constant_value_literal>(rhs);
  if (rhs_literal) {
    constant_value::ref lhs_value = builtin_integer_constant();
    constant_value::ref rhs_value = rhs_literal->builtin_integer_constant();
    ret = lhs_value->inequality_lt(rhs_value);
  }
  return ret;
}

constant_value::ref constant_value_literal::inequality_gt(const constant_value::ref& rhs) const {
  constant_value::ref ret;
  constant_value_literal::ref rhs_literal = std::dynamic_pointer_cast<constant_value_literal>(rhs);
  if (rhs_literal) {
    constant_value::ref lhs_value = builtin_integer_constant();
    constant_value::ref rhs_value = rhs_literal->builtin_integer_constant();
    ret = lhs_value->inequality_gt(rhs_value);
  }
  return ret;
}

constant_value::ref constant_value_literal::inequality_lte(const constant_value::ref& rhs) const {
  constant_value::ref ret;
  constant_value_literal::ref rhs_literal = std::dynamic_pointer_cast<constant_value_literal>(rhs);
  if (rhs_literal) {
    constant_value::ref lhs_value = builtin_integer_constant();
    constant_value::ref rhs_value = rhs_literal->builtin_integer_constant();
    ret = lhs_value->inequality_lte(rhs_value);
  }
  return ret;
}

constant_value::ref constant_value_literal::inequality_gte(const constant_value::ref& rhs) const {
  constant_value::ref ret;
  constant_value_literal::ref rhs_literal = std::dynamic_pointer_cast<constant_value_literal>(rhs);
  if (rhs_literal) {
    constant_value::ref lhs_value = builtin_integer_constant();
    constant_value::ref rhs_value = rhs_literal->builtin_integer_constant();
    ret = lhs_value->inequality_gte(rhs_value);
  }
  return ret;
}

constant_value::ref constant_value_literal::bitwise_shl(const constant_value::ref& rhs) const {
  constant_value::ref ret;
  constant_value_literal::ref rhs_literal = std::dynamic_pointer_cast<constant_value_literal>(rhs);
  if (rhs_literal) {
    constant_value::ref lhs_value = builtin_integer_constant();
    constant_value::ref rhs_value = rhs_literal->builtin_integer_constant();
    ret = lhs_value->bitwise_shl(rhs_value);
  }
  return ret;
}

constant_value::ref constant_value_literal::bitwise_shr(const constant_value::ref& rhs) const {
  constant_value::ref ret;
  constant_value_literal::ref rhs_literal = std::dynamic_pointer_cast<constant_value_literal>(rhs);
  if (rhs_literal) {
    constant_value::ref lhs_value = builtin_integer_constant();
    constant_value::ref rhs_value = rhs_literal->builtin_integer_constant();
    ret = lhs_value->bitwise_shr(rhs_value);
  }
  return ret;
}

constant_value::ref constant_value_literal::arith_add(const constant_value::ref& rhs) const {
  constant_value::ref ret;
  constant_value_literal::ref rhs_literal = std::dynamic_pointer_cast<constant_value_literal>(rhs);
  if (rhs_literal) {
    constant_value::ref lhs_value = builtin_integer_constant();
    constant_value::ref rhs_value = rhs_literal->builtin_integer_constant();
    ret = lhs_value->arith_add(rhs_value);
  }
  return ret;
}

constant_value::ref constant_value_literal::arith_sub(const constant_value::ref& rhs) const {
  constant_value::ref ret;
  constant_value_literal::ref rhs_literal = std::dynamic_pointer_cast<constant_value_literal>(rhs);
  if (rhs_literal) {
    constant_value::ref lhs_value = builtin_integer_constant();
    constant_value::ref rhs_value = rhs_literal->builtin_integer_constant();
    ret = lhs_value->arith_sub(rhs_value);
  }
  return ret;
}

constant_value::ref constant_value_literal::arith_mul(const constant_value::ref& rhs) const {
  constant_value::ref ret;
  constant_value_literal::ref rhs_literal = std::dynamic_pointer_cast<constant_value_literal>(rhs);
  if (rhs_literal) {
    constant_value::ref lhs_value = builtin_integer_constant();
    constant_value::ref rhs_value = rhs_literal->builtin_integer_constant();
    ret = lhs_value->arith_mul(rhs_value);
  }
  return ret;
}

constant_value::ref constant_value_literal::arith_div(const constant_value::ref& rhs) const {
  constant_value::ref ret;
  constant_value_literal::ref rhs_literal = std::dynamic_pointer_cast<constant_value_literal>(rhs);
  if (rhs_literal) {
    constant_value::ref lhs_value = builtin_integer_constant();
    constant_value::ref rhs_value = rhs_literal->builtin_integer_constant();
    ret = lhs_value->arith_div(rhs_value);
  }
  return ret;
}

constant_value::ref constant_value_literal::arith_mod(const constant_value::ref& rhs) const {
  constant_value::ref ret;
  constant_value_literal::ref rhs_literal = std::dynamic_pointer_cast<constant_value_literal>(rhs);
  if (rhs_literal) {
    constant_value::ref lhs_value = builtin_integer_constant();
    constant_value::ref rhs_value = rhs_literal->builtin_integer_constant();
    ret = lhs_value->arith_mod(rhs_value);
  }
  return ret;
}

} /* namespace */
