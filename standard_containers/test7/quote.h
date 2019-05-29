#ifndef QUOTE_H
#define QUOTE_H

#include <string>

#include "common/common_types.h"
#include "currency_pair.h"
#include "dealcode.h"
#include "maker.h"

class quote {
public:
  quote();
  quote(const currency_pair &currencyPair, uint64_t valueDate, instrument inst,
        double price, const struct dealcode &dealcode, int uuid);

  size_t hash() const;

  const currency_pair &currencyPair() const;
  uint64_t valueDate() const;
  instrument inst() const;
  double price() const;
  const struct dealcode &dealcode() const;
  int uuid() const;

  void setPrice(double price);

  friend bool operator<(const quote &lhs, const quote &rhs);

private:
  size_t m_hash;
  struct dealcode m_dealcode;
  int m_uuid;
  uint64_t m_valueDate;
  double m_price;
  currency_pair m_currencyPair;
  instrument m_inst;
};

#endif // QUOTE_H
