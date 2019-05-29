#ifndef ORDER_H
#define ORDER_H

#include "common/common_types.h"
#include "currency_pair.h"

#include <string>

class quote;

class order {
public:
  order();
  order(int orderId, const currency_pair &currencyPair, instrument inst,
        uint64_t valueDate, double amount);

  int orderId() const;
  const currency_pair &currencyPair() const;
  instrument inst() const;
  uint64_t valueDate() const;
  double amount();

  friend bool operator<(const order &lhs, const order &rhs);

private:
  uint64_t m_valueDate;
  double m_amount;
  int m_orderId;
  instrument m_inst;
  currency_pair m_currentyPair;
};

#endif // ORDER_H
