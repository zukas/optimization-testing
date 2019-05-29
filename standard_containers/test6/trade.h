#ifndef TRADE_H
#define TRADE_H

#include "common/common_types.h"
#include "currency_pair.h"
#include "maker.h"

#include <cstdint>

class trade {
public:
  trade();
  trade(const maker &maker, double price);

  const maker &mk() const;
  double price() const;

  bool isValid() const;

private:
  maker m_maker;
  double m_price;
};

class full_trade {
public:
  full_trade();
  full_trade(const currency_pair &currencyPair, instrument inst,
             uint64_t valueDate, const maker &maker, double price);

  const currency_pair &currencyPair() const;
  instrument inst() const;
  uint64_t valueDate() const;

  const maker &mk() const;
  double price() const;

  void setPrice(double price);

  bool isValid() const;

private:
  currency_pair m_currencyPair;
  instrument m_inst;
  uint64_t m_valueDate;
  maker m_maker;
  double m_price;
};

#endif // TRADE_H
