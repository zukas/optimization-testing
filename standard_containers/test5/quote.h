#ifndef QUOTE_H
#define QUOTE_H

#include <string>

#include "common/common_types.h"
#include "currency_pair.h"
#include "dealcode.h"

class quote {
public:
  quote();
  quote(const currency_pair &currencyPair, uint64_t valueDate, instrument inst,
        double price, const struct dealcode &dealcode, int uuid);

  const currency_pair &currencyPair() const;
  uint64_t valueDate() const;
  instrument inst() const;
  double price() const;
  const struct dealcode &dealcode() const;
  int uuid() const;

  void setPrice(double price);

private:
  currency_pair m_currencyPair;
  uint64_t m_valueDate;
  instrument m_inst;
  double m_price;
  struct dealcode m_dealcode;
  int m_uuid;
};

#endif // QUOTE_H
