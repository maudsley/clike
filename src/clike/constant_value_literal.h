#ifndef __CONSTANT_VALUE_LITERAL_H__
#define __CONSTANT_VALUE_LITERAL_H__

/* a type for integer constant literals appearing in the code. */
/* any arithmetic operations on the literal will return a builtin type. */

#include "type_factory.h"
#include "constant_value.h"
#include "integer.h"

namespace clike {

class constant_value_literal : public constant_value {
public:
  typedef std::shared_ptr<constant_value_literal> ref;
  typedef int64_t builtin_type; /* operations on the literal produce this builtin type */
  constant_value_literal(const integer& value);
  const integer& value() const;
  constant_value::ref builtin_integer_constant() const;
  bool get_numeric_value(size_t* value) const override;
  constant_value::ref unary_arith_negate() const override;
  constant_value::ref unary_bitwise_negate() const override;
  constant_value::ref unary_logical_negate() const override;
  constant_value::ref unary_logical_value() const override;
  constant_value::ref bitwise_or(const constant_value::ref& rhs) const override;
  constant_value::ref bitwise_xor(const constant_value::ref& rhs) const override;
  constant_value::ref bitwise_and(const constant_value::ref& rhs) const override;
  constant_value::ref inequality_eq(const constant_value::ref& rhs) const override;
  constant_value::ref inequality_neq(const constant_value::ref& rhs) const override;
  constant_value::ref inequality_lt(const constant_value::ref& rhs) const override;
  constant_value::ref inequality_gt(const constant_value::ref& rhs) const override;
  constant_value::ref inequality_lte(const constant_value::ref& rhs) const override;
  constant_value::ref inequality_gte(const constant_value::ref& rhs) const override;
  constant_value::ref bitwise_shl(const constant_value::ref& rhs) const override;
  constant_value::ref bitwise_shr(const constant_value::ref& rhs) const override;
  constant_value::ref arith_add(const constant_value::ref& rhs) const override;
  constant_value::ref arith_sub(const constant_value::ref& rhs) const override;
  constant_value::ref arith_mul(const constant_value::ref& rhs) const override;
  constant_value::ref arith_div(const constant_value::ref& rhs) const override;
  constant_value::ref arith_mod(const constant_value::ref& rhs) const override;
  integer value_;
};

class literal_type_factory : public type_factory {
public:
  typedef std::shared_ptr<literal_type_factory> ref;
  literal_type_factory(const std::string& name, const digit_vector& modulus) : type_factory(name) {
    modulus_ = std::make_shared<digit_vector>(modulus);
  }
  constant_value::ref construct_value(const std::vector<constant_value::ref>& args) const override {
    typename constant_value_literal::ref result;
    if (args.empty()) {
      return std::make_shared<constant_value_literal>(integer(modulus_));
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
    return std::make_shared<constant_value_literal>(integer(modulus_));
  }
  constant_value::ref representative_value() const override {
    return std::make_shared<constant_value_literal>(integer({1}, modulus_));
  }
  digit_vector::ref modulus_;
};

} /* namespace */

#endif /* __CONSTANT_VALUE_LITERAL_H__ */
