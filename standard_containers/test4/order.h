#ifndef ORDER_H
#define ORDER_H

#include "common/common_types.h"

#include <string>

class order {
public:
  order();
  order(int orderId, const std::string &currencyPair, instrument inst,
        uint64_t valueDate, double amount);

  int orderId() const;
  const std::string &currencyPair() const;
  instrument inst() const;
  uint64_t valueDate() const;
  double amount();

private:
  int m_orderId;
  std::string m_currentyPair;
  instrument m_inst;
  uint64_t m_valueDate;
  double m_amount;
};

#endif // ORDER_H
