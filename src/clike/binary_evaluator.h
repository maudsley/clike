#ifndef __BINARY_EVALUATOR_H__
#define __BINARY_EVALUATOR_H__

/* try to implicitly cast operands when evaluating a binary operator */

#include "constant_value_boolean.h"

namespace clike {

class binary_evaluator {
public:
  enum evaluation_result {
    result_ok,
    result_error_incompatible,
    result_error_ambiguous,
    result_error_unsupported,
    result_error_zero_divide,
    result_error_unknown
  };
  binary_evaluator(const type_system::ref& types, const ast_binary::ref& binary_operator) : type_system_(types), binary_operator_(binary_operator), result_(result_error_unknown) {
  }
  void evaluate(const ast_type::ref& lhs_type, const constant_value::ref& lhs_value, const ast_type::ref& rhs_type, const constant_value::ref& rhs_value) {
    if (lhs_value && rhs_value) {
      constant_value::ref cast_lhs_value = lhs_value;
      constant_value::ref cast_rhs_value = rhs_value;
      if (lhs_type->type_name() == rhs_type->type_name()) {
        result_value_ = binary_operator_->evaluate(lhs_value, rhs_value); /* no cast needed */
      } else { /* try to cast */
        constant_value::ref cast_lhs_value = type_system_->implicit_cast_value(rhs_type->type_name(), lhs_value);
        constant_value::ref cast_rhs_value = type_system_->implicit_cast_value(lhs_type->type_name(), rhs_value);
        if (cast_lhs_value && cast_rhs_value) {
          error_message_ << "incompatible types '" << lhs_type->type_name() << "' and '" << rhs_type->type_name() << "' in operator";
          result_ = result_error_ambiguous; /* both succeeded */
        } else if (!cast_lhs_value && !cast_rhs_value) {
          error_message_ << "incompatible types '" << lhs_type->type_name() << "' and '" << rhs_type->type_name() << "' in operator";
          result_ = result_error_incompatible; /* both failed */
        } else {
          if (cast_lhs_value) { /* left ok */
            result_value_ = binary_operator_->evaluate(cast_lhs_value, rhs_value);
          } else { /* right ok */
            result_value_ = binary_operator_->evaluate(lhs_value, cast_rhs_value);
          }
        }
      }
    }

    if (!!result_value_) { /* did we get a result? */
      if (typeid(*result_value_) == typeid(*lhs_value)) { /* result has same type as lhs */
        result_type_ = std::make_shared<ast_type>(*lhs_type);
        result_type_->set_const(true); /* expression is not writable */
        result_ = result_ok;
      } else if (typeid(*result_value_) == typeid(*rhs_value)) { /* result has same type as rhs */
        result_type_ = std::make_shared<ast_type>(*rhs_type);
        result_type_->set_const(true);
        result_ = result_ok;
      } else if (std::dynamic_pointer_cast<constant_value_boolean>(result_value_)) { /* is it boolean? */
        result_type_ = std::make_shared<ast_type>(type_system_->boolean_type_name());
        result_type_->set_const(true);
        result_ = result_ok;
      } else if (std::dynamic_pointer_cast<constant_value_builtin<int64_t>>(result_value_)) { /* literal promotion? */
        /* when operations are applied to a literal it becomes this builtin type */
        result_type_ = std::make_shared<ast_type>(type_system_->literal_promotion_type_name());
        result_type_->set_const(true);
        result_ = result_ok;
      } else if (std::dynamic_pointer_cast<constant_value_nan>(result_value_)) {
        error_message_ << "expression causes division by zero";
        result_ = result_error_zero_divide;
      } else { /* operator returned something else. not implemented */
        error_message_ << "operator not valid";
        result_ = result_error_unsupported;
      }
    } else if (result_ == result_error_unknown) {
      if (lhs_type->type_name() == rhs_type->type_name()) {
        error_message_ << "'" << lhs_type->type_name() << "' does not support this operator";
        result_ = result_error_unsupported;
      } else {
        error_message_ << "incompatible types '" << lhs_type->type_name() << "' and '" << rhs_type->type_name() << "' in operator";
        result_ = result_error_incompatible;
      }
    }
  }
  evaluation_result result() const {
    return result_;
  }
  ast_type::ref result_type() const {
    return result_type_;
  }
  constant_value::ref result_value() const {
    return result_value_;
  }
  location_error error_message(const location& loc) const {
    return location_error(error_message_.str(), loc);
  }
  type_system::ref type_system_;
  ast_binary::ref binary_operator_;
  evaluation_result result_;
  constant_value::ref result_value_;
  ast_type::ref result_type_;
  std::stringstream error_message_;
};

} /* namespace */

#endif /* __BINARY_EVALUATOR_H__ */
