#ifndef __CONSTANT_VALUE_BOOLEAN_H__
#define __CONSTANT_VALUE_BOOLEAN_H__

/* might need an actual boolean type in future. for now bools are uints */

#include "constant_value_builtin.h"
#include "constant_value_boolean_type.h"

namespace clike {

/* this seeminly pointless additional typedef is needed to avoid a cyclic dependency */
/* because the constant_value_builtin<> itself uses the boolean type. */
typedef constant_value_builtin<constant_value_boolean_type> constant_value_boolean;

} /* namespace */

#endif /* __CONSTANT_VALUE_BOOLEAN_H__ */
