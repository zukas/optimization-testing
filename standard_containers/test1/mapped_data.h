#ifndef MAPPED_DATA_H
#define MAPPED_DATA_H

#include <map>
#include <memory>
#include <vector>

#include "maker.h"
#include "order.h"
#include "quote.h"
#include "trade.h"

class mapped_data {
public:
  typedef std::map<uint64_t, double> ValueDatePriceMap;
  typedef std::map<instrument, ValueDatePriceMap> InstrumentPriceMap;
  typedef std::map<std::string, InstrumentPriceMap> CurrencyPairPriceMap;
  typedef std::map<maker, CurrencyPairPriceMap> QuoteMap;
  typedef std::map<int, std::shared_ptr<order>> OrderMap;

public:
  mapped_data();

  void addSubscription(const maker &maker);
  void addOrder(std::shared_ptr<order> order);

  void handleQuote(const quote &quote);

  bool tradeBestPrice(const std::string &currencyPair, uint64_t valueDate,
                      instrument inst, trade &trade);

  void tradeBestAll(std::vector<full_trade> &trades);

  const std::vector<maker> subscriptions() const;
  const OrderMap orders() const;
  const QuoteMap quotes() const;

private:
  bool validateSubscription(const maker &maker) const;
  bool validateOrderQuote(const quote &quote) const;
  bool validateOrder(const std::shared_ptr<order> &order) const;

private:
  std::vector<maker> m_subscriptions;
  OrderMap m_orders;
  QuoteMap m_quots;
};

#endif // MAPPED_DATA_H
