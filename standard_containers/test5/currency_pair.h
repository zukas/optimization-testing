#ifndef CURRENCY_PAIR_H
#define CURRENCY_PAIR_H

#include <string.h>

struct currency_pair {
  char data[6];
  bool empty() const { return data[0] == 0; }
  bool operator==(const currency_pair &rhs) const {
    return strncmp(data, rhs.data, 6) == 0;
  }
  friend bool operator<(const currency_pair &lhs, const currency_pair &rhs) {
    return strncmp(lhs.data, rhs.data, 6) < 0;
  }

  friend bool operator>(const currency_pair &lhs, const currency_pair &rhs) {
    return strncmp(lhs.data, rhs.data, 6) > 0;
  }
};

#endif // CURRENCY_PAIR_H
