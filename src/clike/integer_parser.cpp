#include "integer_parser.h"
#include "integer.h"

namespace clike {

bool parse_integer(digit_vector* result_digits, const std::string& digit_string) {
  /* interpret string with "0x" prefix as hex, else decimal */
  bool result_ok = false;
  static const std::string hex_prefix = "0x";
  if (digit_string.find(hex_prefix) == 0) {
    result_ok = parse_integer_hexadecimal(result_digits, digit_string.substr(hex_prefix.length()));
  } else {
    result_ok = parse_integer_decimal(result_digits, digit_string);
  }
  return result_ok;
}

bool parse_integer_decimal(digit_vector* result_digits, const std::string& digit_string) {
  integer result{digit_vector::ref()}; /* no modulus */
  bool result_ok = true;

  digit_vector ten;
  ten.push_back(10);

  for (size_t i = 0; i < digit_string.length(); ++i) {
    if ((digit_string[i] >= '0') && (digit_string[i] <= '9')) {
      digit_vector digit;
      digit.push_back(uint64_t(digit_string[i]) - uint64_t('0'));
      result = result.mul(ten).add(digit);
    } else {
      result_ok = false;
      break;
    }
  }

  result.remove_leading_zeros();

  if (result_ok && result_digits) {
    *result_digits = result;
  } else {
    result_ok = false;
  }

  return result_ok;
}

bool parse_integer_hexadecimal(digit_vector* result_digits, const std::string& digit_string) {
  integer result{digit_vector::ref()}; /* no modulus */
  bool result_ok = true;

  digit_vector sixteen;
  sixteen.push_back(16);

  for (size_t i = 0; i < digit_string.length(); ++i) {
    digit_vector digit;
    if ((digit_string[i] >= '0') && (digit_string[i] <= '9')) {
      digit.push_back(uint64_t(digit_string[i]) - uint64_t('0'));
    } else if ((digit_string[i] >= 'a') && (digit_string[i] <= 'f')) {
      digit.push_back(uint64_t(digit_string[i]) - uint64_t('a') + 10);
    } else if ((digit_string[i] >= 'A') && (digit_string[i] <= 'F')) {
      digit.push_back(uint64_t(digit_string[i]) - uint64_t('A') + 10);
    } else {
      result_ok = false;
      break;
    }
    result = result.mul(sixteen).add(digit);
  }

  result.remove_leading_zeros();

  if (result_ok && result_digits) {
    *result_digits = result;
  } else {
    result_ok = false;
  }

  return result_ok;
}

} /* namespace */
