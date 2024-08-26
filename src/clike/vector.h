#ifndef __VECTOR_H__
#define __VECTOR_H__

/* vector arithmetic */

namespace clike {

class vector_exception : public std::exception {
public:
};

template <typename T> class vector {
public:

  vector() {
  }

  vector(const size_t size) : m_(size) {
  }

  vector(const size_t size, const T& initial_value) : m_(size, initial_value) {
  }

  bool empty() const {
    return m_.empty();
  }

  size_t size() const {
    return m_.size();
  }

  T& operator [](const size_t i) {
    return m_[i];
  }

  const T& operator [](const size_t i) const {
    return m_[i];
  }

  vector operator -() const {
    vector r(*this);
    for (size_t i = 0; i < size(); ++i) {
      r[i] = -r.m_[i];
    }
    return r;
  }

  vector operator +(const vector& rhs) const {
    if (size() != rhs.size()) {
      throw vector_exception();
    }
    vector r(*this);
    for (size_t i = 0; i < size(); ++i) {
      r[i] += rhs[i];
    }
    return r;
  }

  vector& operator +=(const vector& rhs) {
    *this = *this + rhs;
    return *this;
  }

  vector operator -(const vector& rhs) const {
    if (size() != rhs.size()) {
      throw vector_exception();
    }
    vector r(size());
    for (size_t i = 0; i < size(); ++i) {
      r[i] = m_[i] - rhs[i];
    }
    return r;
  }

  vector& operator -=(const vector& rhs) {
    *this = *this - rhs;
    return *this;
  }

  vector operator *(const T& rhs) const {
    vector r(size());
    for (size_t i = 0; i < size(); ++i) {
      r[i] = m_[i] * rhs;
    }
    return r;
  }

  vector& operator *=(const T& rhs) {
    *this = *this * rhs;
    return *this;
  }

  std::vector<T> m_;

};

} /* namespace */

#endif /* __VECTOR_H__ */
