#ifndef __CONSTANT_VALUE_BOOLEAN_TYPE_H__
#define __CONSTANT_VALUE_BOOLEAN_TYPE_H__

/* might need an actual boolean type in future. for now bools are uints */

namespace clike {

/* use a small uint so that it can be converted to other sizes without a cast. */
/* this is used to instantiate constant_value_builtin. */
typedef uint8_t constant_value_boolean_type;

} /* namespace */

#endif /* __CONSTANT_VALUE_BOOLEAN_TYPE_H__ */
