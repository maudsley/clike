#ifndef __CONSTANT_VALUE_NAN_H__
#define __CONSTANT_VALUE_NAN_H__

/* not-a-number value for division by zero */

#include "type_factory.h"
#include "constant_value.h"

namespace clike {

class constant_value_nan : public constant_value {
public:

  typedef std::shared_ptr<constant_value_nan> ref;

  enum nan_type {
    nan_zero_divide,
    nan_unknown
  };

  constant_value_nan(const nan_type type) : type_(type) {
  }

  nan_type type() const {
    return type_;
  }

  nan_type type_;

};

} /* namespace */

#endif /* __CONSTANT_VALUE_NAN_H__ */
