#ifndef __INTEGER_H__
#define __INTEGER_H__

/* "big integer" arithmetic */

#include "digit_vector.h"

namespace clike {

template <typename T> class integer_radix : public digit_vector_radix<T> {
public:

  typedef std::shared_ptr<integer_radix<T>> ref;
  typedef typename digit_vector_radix<T>::ref digit_vector_radix_ref;

  explicit integer_radix(const digit_vector_radix_ref modulus) : modulus_(modulus) {
  }

  integer_radix(const digit_vector_radix<T>& digits, const digit_vector_radix_ref modulus) : digit_vector_radix<T>(digits), modulus_(modulus) {
  }

  integer_radix(const digit_vector_radix<T>& digits, const digit_vector_radix<T>& modulus) : digit_vector_radix<T>(digits) {
    modulus_ = std::make_shared<digit_vector_radix<T>>(modulus);
  }

  ref make_shared() const {
    return std::make_shared<integer_radix<T>>(*this);
  }

  static integer_radix identity(const digit_vector_radix_ref& modulus) {
    static const digit_vector_radix<T> unit({1});
    return integer_radix(unit, modulus);
  }

  bool is_zero() const {
    return this->empty();
  }

  integer_radix operator -() const {
    integer_radix zero(modulus_);
    return zero - *this;
  }

  bool modulus_equal(const integer_radix& rhs) const {
    bool eq = false;
    if (!!modulus_ && !!rhs.modulus_) {
      if (*modulus_ == *rhs.modulus_) {
        eq = true;
      }
    }
    return eq;
  }

  enum bitwise_operation {
    bitwise_operation_or,
    bitwise_operation_xor,
    bitwise_operation_and
  };

  /* bitwise operation on two digit vectors then perform modular reduction */
  template <enum bitwise_operation F> integer_radix bitwise_operator(const integer_radix& rhs) const {
    const digit_vector_radix<T>& lhs_digits = this->digits();
    const digit_vector_radix<T>& rhs_digits = rhs.digits();

    const digit_vector_radix<T>* smaller = &rhs_digits;
    const digit_vector_radix<T>* bigger = &lhs_digits;
    if (smaller->size() > bigger->size()) {
      std::swap(smaller, bigger);
    }

    digit_vector_radix<T> result_digits = *bigger;
    for (size_t i = 0; i < smaller->size(); ++i) {
      switch (F) {
      case bitwise_operation_or:
        result_digits[i] |= (*smaller)[i];
        break;
      case bitwise_operation_xor:
        result_digits[i] ^= (*smaller)[i];
        break;
      case bitwise_operation_and:
        result_digits[i] &= (*smaller)[i];
        break;
      default:
        break;
      }
    }

    /* process zero-extended upper digits */
    for (size_t i = smaller->size(); i < bigger->size(); ++i) {
      switch (F) {
      case bitwise_operation_or:
        result_digits[i] |= 0;
        break;
      case bitwise_operation_xor:
        result_digits[i] ^= 0;
        break;
      case bitwise_operation_and:
        result_digits[i] &= 0;
        break;
      default:
        break;
      }
    }

    result_digits.remove_leading_zeros();

    integer_radix q(modulus_);
    integer_radix r(modulus_);
    integer_radix result(result_digits, modulus_);
    result.divide(q, r, *modulus_);
    return r;
  }

  integer_radix bitwise_or(const integer_radix& rhs) const {
    return bitwise_operator<bitwise_operation_or>(rhs);
  }

  integer_radix bitwise_xor(const integer_radix& rhs) const {
    return bitwise_operator<bitwise_operation_xor>(rhs);
  }

  integer_radix bitwise_and(const integer_radix& rhs) const {
    return bitwise_operator<bitwise_operation_and>(rhs);
  }

  /* interpret the rhs value as native int. bound shift amount by the modulus size. */
  size_t bitwise_shift_size(const integer_radix& rhs) const {
    size_t shift_size = 0;
    size_t shift_size_bits = 0;
    for (size_t i = 0; i < rhs.size(); ++i) {
      shift_size += size_t(rhs[i]) << shift_size_bits;
      shift_size_bits += rhs.radix_size_bits();
      if (shift_size >= modulus_->size_bits()) {
        shift_size = modulus_->size_bits();
        break; /* at this point we have shifted everything to zero */
      }
    }
    return shift_size;
  }

  /* this is complicated by the fact that the rhs is also a integer_radix */
  integer_radix bitwise_shl(const integer_radix& rhs) const {
    const size_t shift_size = bitwise_shift_size(rhs);
    digit_vector_radix<T> result_digits(modulus_->size());
    for (size_t i = 0; i < this->size_bits(); ++i) {
      size_t src_digit = i / this->radix_size_bits();
      size_t src_bit = i % this->radix_size_bits();
      size_t dest_digit = (i + shift_size) / this->radix_size_bits();
      size_t dest_bit = (i + shift_size) % this->radix_size_bits();
      uint64_t value = (this->digits_[src_digit] >> src_bit) & 1;
      result_digits[dest_digit] |= (value << dest_bit);
    }
    result_digits.remove_leading_zeros();
    integer_radix q(modulus_);
    integer_radix r(modulus_);
    integer_radix result(result_digits, modulus_);
    result.divide(q, r, *modulus_);
    return r;
  }

  integer_radix bitwise_shr(const integer_radix& rhs) const {
    const size_t shift_size = bitwise_shift_size(rhs);
    digit_vector_radix<T> result_digits(modulus_->size());
    for (size_t i = shift_size; i < this->size_bits(); ++i) {
      size_t src_digit = i / this->radix_size_bits();
      size_t src_bit = i % this->radix_size_bits();
      size_t dest_digit = (i - shift_size) / this->radix_size_bits();
      size_t dest_bit = (i - shift_size) % this->radix_size_bits();
      uint64_t value = (this->digits_[src_digit] >> src_bit) & 1;
      result_digits[dest_digit] |= (value << dest_bit);
    }
    result_digits.remove_leading_zeros();
    integer_radix q(modulus_);
    integer_radix r(modulus_);
    integer_radix result(result_digits, modulus_);
    result.divide(q, r, *modulus_);
    return r;
  }

  integer_radix pow(const digit_vector_radix<T>& exponent) const {
    integer_radix result(identity(modulus_));
    integer_radix prod = *this;
    for (size_t i = 0; i < exponent.size_bits(); ++i) {
      if (exponent.bit_at(i)) {
        result = result * prod;
      }
      prod = prod * prod;
    }
    return result;
  }

  void divide(integer_radix& q, integer_radix& r, const digit_vector_radix<T>& rhs) const {
    if (rhs.empty()) {
      throw std::runtime_error("Zero divisor");
    }

    if (compare_lt(rhs)) {
      q = integer_radix(modulus_);
      r = *this;
      return;
    }

    static const digit_vector_radix<T> unit({1});

    r = *this;

    while (!r.empty() && r.compare_gte(rhs)) {
      size_t t_exp = r.size() - rhs.size();
      T r_digit = r[r.size() - 1];
      T rhs_digit = rhs[rhs.size() - 1];

      integer_radix t(modulus_);
      if (r_digit < rhs_digit) {
        /* the quotient estimate would be zero */
        t.resize(t_exp);
        t[t_exp - 1] = 1;
      } else {
        /* quotient estimate */
        t.resize(t_exp + 1);
        t[t_exp] = r_digit / rhs_digit;
      }

      while (r.compare_lt(t.mul(rhs))) {
        /* slow resolution in case constraint is violated */
        t = t.sub(unit);
      }

      q = q.add(t);
      r = r.sub(t.mul(rhs));
    }
  }

  integer_radix operator /(const integer_radix& rhs) const {
    if (!modulus_equal(rhs)) {
      throw std::runtime_error("Modulus not equal");
    }
    integer_radix q(modulus_);
    integer_radix r(modulus_);
    divide(q, r, rhs);
    return q;
  }

  integer_radix& operator /=(const integer_radix& rhs) {
    *this = *this / rhs;
    return *this;
  }

  integer_radix operator %(const integer_radix& rhs) const {
    if (!modulus_equal(rhs)) {
      throw std::runtime_error("Modulus not equal");
    }
    integer_radix q(modulus_);
    integer_radix r(modulus_);
    divide(q, r, rhs);
    return r;
  }

  integer_radix& operator %=(const integer_radix& rhs) {
    *this = *this % rhs;
    return *this;
  }

  bool operator <(const integer_radix& rhs) const {
    if (!modulus_equal(rhs)) {
      throw std::runtime_error("Modulus not equal");
    }
    return compare_lt(rhs);
  }

  bool operator >(const integer_radix& rhs) const {
    if (!modulus_equal(rhs)) {
      throw std::runtime_error("Modulus not equal");
    }
    return compare_gt(rhs);
  }

  bool compare_lt(const digit_vector_radix<T>& rhs) const {
    const digit_vector_radix<T>& lhs_digits = this->digits();
    const digit_vector_radix<T>& rhs_digits = rhs.digits();
    if (lhs_digits.size() < rhs_digits.size()) {
      return true;
    } else if (lhs_digits.size() > rhs_digits.size()) {
      return false;
    }
    for (size_t i = 0; i < lhs_digits.size(); ++i) { /* same size */
      size_t j = lhs_digits.size() - i - 1;
      if (lhs_digits[j] < rhs_digits[j]) {
        return true;
      } else if (lhs_digits[j] > rhs_digits[j]) {
        return false;
      }
    }
    return false;
  }

  bool compare_gt(const digit_vector_radix<T>& rhs) const {
    const digit_vector_radix<T>& lhs_digits = this->digits();
    const digit_vector_radix<T>& rhs_digits = rhs.digits();
    if (lhs_digits.size() > rhs_digits.size()) {
      return true;
    } else if (lhs_digits.size() < rhs_digits.size()) {
      return false;
    }
    for (size_t i = 0; i < lhs_digits.size(); ++i) { /* same size */
      size_t j = lhs_digits.size() - i - 1;
      if (lhs_digits[j] > rhs_digits[j]) {
        return true;
      } else if (lhs_digits[j] < rhs_digits[j]) {
        return false;
      }
    }
    return false;
  }

  bool operator >=(const integer_radix& rhs) const {
    if (!modulus_equal(rhs)) {
      throw std::runtime_error("Modulus not equal");
    }
    return compare_gte(rhs);
  }

  bool operator <=(const integer_radix& rhs) const {
    if (!modulus_equal(rhs)) {
      throw std::runtime_error("Modulus not equal");
    }
    return compare_lte(rhs);
  }

  bool compare_gte(const digit_vector_radix<T>& rhs) const {
    return !compare_lt(rhs);
  }

  bool compare_lte(const digit_vector_radix<T>& rhs) const {
    return !compare_gt(rhs);
  }

  integer_radix operator *(const integer_radix& rhs) const {
    if (!modulus_equal(rhs)) {
      throw std::runtime_error("Modulus not equal");
    }
    integer_radix result(modulus_);
    integer_radix sum = rhs;
    for (size_t i = 0; i < this->size_bits(); ++i) {
      if (this->bit_at(i)) {
        result = result + sum;
      }
      sum = sum + sum;
    }
    return result;
  }

  integer_radix& operator *=(const integer_radix& rhs) {
    *this = *this * rhs;
    return *this;
  }

  integer_radix mul(const digit_vector_radix<T>& rhs) const {
    integer_radix result(modulus_);
    integer_radix sum(rhs, modulus_);
    for (size_t i = 0; i < this->size_bits(); ++i) {
      if (this->bit_at(i)) {
        result = result.add(sum);
      }
      sum = sum.add(sum);
    }
    return result;
  }

  integer_radix operator -(const integer_radix& rhs) const {
    if (!modulus_equal(rhs)) {
      throw std::runtime_error("Modulus not equal");
    }
    integer_radix diff = *this;
    if (compare_lt(rhs)) {
      diff = rhs.sub(*this);
      integer_radix modulus(*modulus_, modulus_);
      diff = modulus.sub(diff);
    } else {
      diff = sub(rhs);
    }
    return diff;
  }

  integer_radix unary_bitwise_negate() const {
    digit_vector_radix<T> result_digits(modulus_->size());

    for (size_t i = 0; i < this->size(); ++i) {
      result_digits[i] = ~this->digits_[i];
    }

    /* process zero-extended upper digits */
    for (size_t i = this->size(); i < result_digits.size(); ++i) {
      result_digits[i] = ~result_digits[i];
    }

    result_digits.remove_leading_zeros();

    integer_radix q(modulus_);
    integer_radix r(modulus_);
    integer_radix result(result_digits, modulus_);
    result.divide(q, r, *modulus_);
    return r;
  }

  integer_radix& operator -=(const integer_radix& rhs) {
    *this = *this - rhs;
    return *this;
  }

  integer_radix sub(const digit_vector_radix<T>& rhs) const {
    const digit_vector_radix<T>& lhs_digits = this->digits();
    const digit_vector_radix<T>& rhs_digits = rhs.digits();

    digit_vector_radix<T> result(lhs_digits.size());

    T track_borrow = 0;
    for (size_t i = 0; i < rhs_digits.size(); ++i) {
      T first_result = 0;
      T first_borrow = 0;
      sub_get_borrow(first_borrow, first_result, lhs_digits[i], rhs_digits[i]);

      T second_result = 0;
      T second_borrow = 0;
      sub_get_borrow(second_borrow, second_result, first_result, track_borrow);

      result[i] = second_result;
      track_borrow = first_borrow + second_borrow;
    }

    for (size_t i = rhs_digits.size(); i < lhs_digits.size(); ++i) {
      sub_get_borrow(track_borrow, result[i], lhs_digits[i], track_borrow);
    }

    if (track_borrow) {
      throw std::runtime_error("Subtraction result is negative");
    }

    result.remove_leading_zeros();

    return integer_radix(result, modulus_);
  }

  integer_radix operator +(const integer_radix& rhs) const {
    if (!modulus_equal(rhs)) {
      throw std::runtime_error("Modulus not equal");
    }
    integer_radix sum = add(rhs);
    integer_radix q(modulus_);
    integer_radix r(modulus_);
    sum.divide(q, r, *modulus_);
    return r;
  }

  integer_radix& operator +=(const integer_radix& rhs) {
    *this = *this + rhs;
    return *this;
  }

  integer_radix add(const digit_vector_radix<T>& rhs) const {
    const digit_vector_radix<T>& lhs_digits = this->digits();
    const digit_vector_radix<T>& rhs_digits = rhs.digits();

    const digit_vector_radix<T>* smaller = &rhs_digits;
    const digit_vector_radix<T>* bigger = &lhs_digits;
    if (smaller->size() > bigger->size()) {
      std::swap(smaller, bigger);
    }

    digit_vector_radix<T> result(bigger->size());

    T track_carry = 0;
    for (size_t i = 0; i < smaller->size(); ++i) {
      T first_result = 0;
      T first_carry = 0;
      add_get_carry(first_carry, first_result, (*smaller)[i], (*bigger)[i]);

      T second_result = 0;
      T second_carry = 0;
      add_get_carry(second_carry, second_result, first_result, track_carry);

      result[i] = second_result;
      track_carry = first_carry + second_carry;
    }

    for (size_t i = smaller->size(); i < bigger->size(); ++i) {
      add_get_carry(track_carry, result[i], (*bigger)[i], track_carry);
    }

    if (track_carry) {
      result.push_back(track_carry);
    }

    return integer_radix(result, modulus_);
  }

  /* subtract two words and also return the borrow in the case of underflow */
  void sub_get_borrow(T& borrow_out, T& result_out, const T& lhs, const T& rhs) const {
    result_out = lhs - rhs;

    /* extract the low word from both inputs */
    const size_t half = this->radix_size_bits() / 2;
    T low_mask = (T(1) << half) - 1;
    T low_lhs = lhs & low_mask;
    T low_rhs = rhs & low_mask;

    /* find the borrow of the low result */
    T low_result = low_lhs - low_rhs;
    T low_borrow = (low_result >> half) & 1;

    /* extract the high words */
    T high_lhs = lhs >> half;
    T high_rhs = rhs >> half;

    /* find the borrow of the high result */
    T high_result = high_lhs - high_rhs - low_borrow;
    borrow_out = (high_result >> half) & 1;
  }

  /* add two words and also return the carry in the case of overflow */
  void add_get_carry(T& carry_out, T& result_out, const T& lhs, const T& rhs) const {
    result_out = lhs + rhs;

    /* extract the low word from both inputs */
    const size_t half = this->radix_size_bits() / 2;
    T low_mask = (T(1) << half) - 1;
    T low_lhs = lhs & low_mask;
    T low_rhs = rhs & low_mask;

    /* find the carry of the low result */
    T low_result = low_lhs + low_rhs;
    T low_carry = low_result >> half;

    /* extract the high words */
    T high_lhs = lhs >> half;
    T high_rhs = rhs >> half;

    /* find the carry of the high result */
    T high_result = high_lhs + high_rhs + low_carry;
    carry_out = high_result >> half;
  }

  digit_vector_radix_ref modulus_;

};

/* the application always uses a 64-bit radix but we instantiate other types for testing */
typedef integer_radix<uint64_t> integer;

} /* namespace */

#endif /* __INTEGER_H__ */
