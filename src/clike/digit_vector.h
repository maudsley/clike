#ifndef __DIGIT_VECTOR_H__
#define __DIGIT_VECTOR_H__

/* a wrapper around std::vector that we can use as a base class for "big integer" types */

#include <memory>
#include <vector>
#include <algorithm>

namespace clike {

template <typename T> class digit_vector_radix {
public:
  typedef std::shared_ptr<digit_vector_radix<T>> ref;
  digit_vector_radix() {
  }
  digit_vector_radix(const std::initializer_list<T>& vec) : digits_(vec) {
  }
  digit_vector_radix(const std::vector<T>& vec) : digits_(vec) {
  }
  explicit digit_vector_radix(const size_t initial_size) : digits_(initial_size) {
  }
  bool empty() const {
    return digits_.empty();
  }
  size_t size() const {
    return digits_.size();
  }
  size_t radix_size_bits() const {
    return sizeof(T) * 8;
  }
  size_t size_bits() const {
    return size() * radix_size_bits();
  }
  const std::vector<T>& digits() const {
    return digits_;
  }
  T& at(const size_t i) {
    return digits_.at(i);
  }
  const T& at(const size_t i) const {
    return digits_.at(i);
  }
  T bit_at(const size_t i) const {
    return (digits_[i / radix_size_bits()] >> (i % radix_size_bits())) & 1;
  }
  T& operator [](const size_t i) {
    return digits_[i];
  }
  const T& operator [](const size_t i) const {
    return digits_[i];
  }
  void clear() {
    digits_.clear();
  }
  void resize(const size_t new_size) {
    digits_.resize(new_size);
  }
  T& back() {
    return digits_.back();
  }
  const T& back() const {
    return digits_.back();
  }
  void push_back(const T& value) {
    digits_.push_back(value);
  }
  void pop_back() {
    digits_.pop_back();
  }
  bool operator ==(const digit_vector_radix& rhs) const {
    if (this != &rhs) {
      if (size() != rhs.size()) {
        return false;
      } else {
        for (size_t i = 0; i < size(); ++i) {
          if (digits_[i] != rhs.digits_[i]) {
            return false;
          }
        }
      }
    }
    return true;
  }
  bool operator !=(const digit_vector_radix& rhs) const {
    return !(*this == rhs);
  }
  void reverse() {
    std::reverse(std::begin(digits_), std::end(digits_));
  }
  void remove_leading_zeros() {
    while (!digits_.empty() && (digits_.back() == 0)) {
      digits_.pop_back();
    }
  }
  std::vector<T> digits_;
};

typedef digit_vector_radix<uint64_t> digit_vector;

} /* namespace */

#endif /* __DIGIT_VECTOR_H__ */
