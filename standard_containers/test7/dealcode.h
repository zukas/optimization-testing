#ifndef DEALCODE_H
#define DEALCODE_H

#include <string.h>

struct dealcode {
  char data[4];

  bool empty() const { return data[0] == 0; }
  bool operator==(const dealcode &rhs) const {
    return strncmp(data, rhs.data, 4) == 0;
  }
  friend bool operator<(const dealcode &lhs, const dealcode &rhs) {
    return strncmp(lhs.data, rhs.data, 4) < 0;
  }

  friend bool operator>(const dealcode &lhs, const dealcode &rhs) {
    return strncmp(lhs.data, rhs.data, 4) > 0;
  }
};

#endif // DEALCODE_H
