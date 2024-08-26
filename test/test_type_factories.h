#ifndef __TEST_TYPE_FACTORY_H__
#define __TEST_TYPE_FACTORY_H__

/* these types are for the unit tests only */
/* the purpose is to test the type system itself */

namespace clike {

class constant_external_vector : public constant_value {
public:
  typedef std::shared_ptr<constant_external_vector> ref;
  constant_external_vector() {
    for (size_t i = 0; i < 4; ++i) {
      elements_.push_back(std::make_shared<constant_value_builtin<uint64_t>>(0));
    }
  }
  constant_external_vector(const size_t size) {
    for (size_t i = 0; i < size; ++i) {
      elements_.push_back(std::make_shared<constant_value_builtin<uint64_t>>(0));
    }
  }
  constant_value::ref read_array_element(const std::vector<size_t>& indices) const override {
    size_t index = indices.front();
    if (index >= elements_.size()) {
      throw std::runtime_error("Invalid vector element index during read");
    }
    if (indices.size() == 1) {
      return elements_[index];
    } else {
      std::vector<size_t> next_indices = indices;
      next_indices.erase(std::begin(next_indices));
      return elements_[index]->read_array_element(next_indices);
    }
  }
  void write_array_element(const std::vector<size_t>& indices, const constant_value::ref& value) override {
    size_t index = indices.front();
    if (index >= elements_.size()) {
      throw std::runtime_error("Invalid vector element index during write");
    }
    if (indices.size() == 1) {
      constant_value_builtin<uint64_t>::ref element = std::dynamic_pointer_cast<constant_value_builtin<uint64_t>>(value);
      if (!element) {
        throw std::runtime_error("Invalid RHS type for vector element assignment");
      }
      elements_[index] = element;
    } else {
      std::vector<size_t> next_indices = indices;
      next_indices.erase(std::begin(next_indices));
      return elements_[index]->write_array_element(next_indices, value);
    }
  }
  virtual constant_value::ref add(const constant_value::ref& rhs) const {
    throw std::runtime_error("Vector-add not implemented");
  }
  std::vector<constant_value_builtin<uint64_t>::ref> elements_;
};

class external_vector_factory : public clike::type_factory {
public:
  external_vector_factory() : clike::type_factory("vector_t", "uint64_t") {
  }
  constant_value::ref construct_value(const std::vector<constant_value::ref>& args) const override {
    constant_value::ref result;
    if (args.empty()) {
      result = std::make_shared<constant_external_vector>(); /* constructor called with no arguments */
    } else if (args.size() == 1) {
      size_t new_vector_length = 0;
      if (args[0]->get_numeric_value(&new_vector_length)) {
        result = std::make_shared<constant_external_vector>(new_vector_length);
      }
    }
    return result;
  }
  virtual constant_value::ref implicit_cast_value(const constant_value::ref& src_value) const {
    return nullptr; /* no implicit casts supported */
  }
  constant_value::ref uninitialized_value() const override {
    return std::make_shared<constant_external_vector>();
  }
};

class constant_external_matrix : public constant_value {
public:
  typedef std::shared_ptr<constant_external_matrix> ref;
  constant_external_matrix() {
    for (size_t i = 0; i < 4; ++i) {
      rows_.push_back(std::make_shared<constant_external_vector>());
    }
  }
  constant_external_matrix(const size_t rows, const size_t cols) {
    for (size_t i = 0; i < rows; ++i) {
      rows_.push_back(std::make_shared<constant_external_vector>(cols));
    }
  }
  constant_value::ref read_array_element(const std::vector<size_t>& indices) const override {
    size_t index = indices.front();
    if (index >= rows_.size()) {
      throw std::runtime_error("Invalid matrix row index during read");
    }
    if (indices.size() == 1) {
      return rows_[index];
    } else {
      std::vector<size_t> next_indices = indices;
      next_indices.erase(std::begin(next_indices));
      return rows_[index]->read_array_element(next_indices);
    }
  }
  void write_array_element(const std::vector<size_t>& indices, const constant_value::ref& value) override {
    size_t index = indices.front();
    if (index >= rows_.size()) {
      throw std::runtime_error("Invalid matrix row index during write");
    }
    if (indices.size() == 1) {
      constant_external_vector::ref element = std::dynamic_pointer_cast<constant_external_vector>(value);
      if (!element) {
        throw std::runtime_error("Invalid RHS type for matrix row assignment");
      }
      rows_[index] = element;
    } else {
      std::vector<size_t> next_indices = indices;
      next_indices.erase(std::begin(next_indices));
      return rows_[index]->write_array_element(next_indices, value);
    }
  }
  constant_value::ref arith_add(const constant_value::ref& rhs) const override {
    throw std::runtime_error("Matrix-add not implemented");
  }
  std::vector<constant_external_vector::ref> rows_;
};

class external_matrix_factory : public clike::type_factory {
public:
  external_matrix_factory() : clike::type_factory("matrix_t", "vector_t") {
  }
  constant_value::ref construct_value(const std::vector<constant_value::ref>& args) const override {
    constant_value::ref result;
    if (args.empty()) {
      result = std::make_shared<constant_external_matrix>(); /* constructor called with no arguments */
    } else if (args.size() == 2) {
      size_t new_matrix_rows = 0;
      if (args[0]->get_numeric_value(&new_matrix_rows)) {
        size_t new_matrix_cols = 0;
        if (args[1]->get_numeric_value(&new_matrix_cols)) {
          result = std::make_shared<constant_external_matrix>(new_matrix_rows, new_matrix_cols);
        }
      }
    }
    return result;
  }
  virtual constant_value::ref implicit_cast_value(const constant_value::ref& src_value) const {
    return nullptr; /* no implicit casts supported */
  }
  constant_value::ref uninitialized_value() const override {
    return std::make_shared<constant_external_matrix>();
  }
};

} /* namespace */

#endif /* __TEST_TYPE_FACTORY_H__ */
