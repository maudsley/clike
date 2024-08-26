#ifndef __CONSTANT_VALUE_H__
#define __CONSTANT_VALUE_H__

/* this object holds the result of constant folding applied to an ast_node */

#include <memory>
#include <vector>

namespace clike {

class constant_value {
public:
  typedef std::shared_ptr<constant_value> ref;
  virtual bool get_numeric_value(size_t* value) const {
    /* when this constant is used to index an array or in a conditional statement */
    /* we will try to convert it to a numeric type. */
    return false;
  }
  virtual constant_value::ref read_array_element(const std::vector<size_t>& indices) const {
    return nullptr;
  }
  virtual void write_array_element(const std::vector<size_t>& indices, const constant_value::ref& value) {
    throw std::runtime_error("Constant value write array element not implemented");
  }
  virtual constant_value::ref unary_arith_negate() const {
    return nullptr;
  }
  virtual constant_value::ref unary_bitwise_negate() const {
    return nullptr;
  }
  virtual constant_value::ref unary_logical_negate() const {
    return nullptr;
  }
  virtual constant_value::ref unary_logical_value() const {
    return nullptr;
  }
  virtual constant_value::ref logical_or(const constant_value::ref& rhs) const {
    return nullptr;
  }
  virtual constant_value::ref logical_and(const constant_value::ref& rhs) const {
    return nullptr;
  }
  virtual constant_value::ref bitwise_or(const constant_value::ref& rhs) const {
    return nullptr;
  }
  virtual constant_value::ref bitwise_xor(const constant_value::ref& rhs) const {
    return nullptr;
  }
  virtual constant_value::ref bitwise_and(const constant_value::ref& rhs) const {
    return nullptr;
  }
  virtual constant_value::ref inequality_eq(const constant_value::ref& rhs) const {
    return nullptr;
  }
  virtual constant_value::ref inequality_neq(const constant_value::ref& rhs) const {
    return nullptr;
  }
  virtual constant_value::ref inequality_lt(const constant_value::ref& rhs) const {
    return nullptr;
  }
  virtual constant_value::ref inequality_gt(const constant_value::ref& rhs) const {
    return nullptr;
  }
  virtual constant_value::ref inequality_lte(const constant_value::ref& rhs) const {
    return nullptr;
  }
  virtual constant_value::ref inequality_gte(const constant_value::ref& rhs) const {
    return nullptr;
  }
  virtual constant_value::ref bitwise_shl(const constant_value::ref& rhs) const {
    return nullptr;
  }
  virtual constant_value::ref bitwise_shr(const constant_value::ref& rhs) const {
    return nullptr;
  }
  virtual constant_value::ref arith_add(const constant_value::ref& rhs) const {
    return nullptr;
  }
  virtual constant_value::ref arith_sub(const constant_value::ref& rhs) const {
    return nullptr;
  }
  virtual constant_value::ref arith_mul(const constant_value::ref& rhs) const {
    return nullptr;
  }
  virtual constant_value::ref arith_div(const constant_value::ref& rhs) const {
    return nullptr;
  }
  virtual constant_value::ref arith_mod(const constant_value::ref& rhs) const {
    return nullptr;
  }
};

/* a constant of this type indicates that the value is actually an entire struct or array */
class constant_struct_array : public constant_value {
  typedef std::shared_ptr<constant_struct_array> ref;
};

} /* namespace */

#endif /* __CONSTANT_VALUE_H__ */
