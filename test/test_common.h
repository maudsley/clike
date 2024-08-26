#ifndef __TEST_COMMON_H__
#define __TEST_COMMON_H__

#include "clike/ast.h"
#include <memory>
#include <gtest/gtest.h>

class BasicTestInterpreter {
public:
  BasicTestInterpreter(const std::string& name);
  clike::syntax_tree::ref tree() {
    return ast_;
  }
  uint64_t evaluate();
  uint64_t evaluate(const uint64_t x);
  bool error_on_line(const size_t line_number) const;
private:
  clike::type_system::ref type_system_;
  clike::syntax_tree::ref ast_;
  std::vector<clike::location_error> errors_;
  std::string file_name_;
};

#endif /* __TEST_COMMON_H__ */
