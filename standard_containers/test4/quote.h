#ifndef QUOTE_H
#define QUOTE_H

#include <string>

#include "common/common_types.h"
#include "dealcode.h"

class quote {
public:
  quote();
  quote(const std::string &currencyPair, uint64_t valueDate, instrument inst,
        double price, const struct dealcode &dealcode, int uuid);

  const std::string &currencyPair() const;
  uint64_t valueDate() const;
  instrument inst() const;
  double price() const;
  const struct dealcode &dealcode() const;
  int uuid() const;

  void setPrice(double price);

private:
  std::string m_currencyPair;
  uint64_t m_valueDate;
  instrument m_inst;
  double m_price;
  struct dealcode m_dealcode;
  int m_uuid;
};

#endif // QUOTE_H
