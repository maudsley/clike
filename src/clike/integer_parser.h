#ifndef __INTEGER_PARSER_H__
#define __INTEGER_PARSER_H__

/* parsing of decimal and hex strings to "big integer" representation */

#include "digit_vector.h"

namespace clike {

bool parse_integer(digit_vector* result_digits, const std::string& digit_string);
bool parse_integer_decimal(digit_vector* result_digits, const std::string& digit_string);
bool parse_integer_hexadecimal(digit_vector* result_digits, const std::string& digit_string);

} /* namespace */

#endif /* __INTEGER_PARSER_H__ */
