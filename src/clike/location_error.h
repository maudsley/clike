#ifndef __LOCATION_ERROR_H__
#define __LOCATION_ERROR_H__

#include "location.hh"
#include <sstream>

namespace clike {

class location_error {
public:
  location_error(const std::string& message, const location& where) : message_(message), loc_(where) {
  }
  std::string message_only() const {
    return message_;
  }
  location loc() const {
    return loc_;
  }
  std::string message_;
  location loc_;
};

} /* namespace */

#endif /* __LOCATION_ERROR_H__ */
