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
  typedef std::vector<quote> Quotes;
  typedef std::vector<order> Orders;

public:
  mapped_data();

  void addSubscription(const maker &maker);
  void addOrder(const order &order);

  void handleQuote(const quote &quote);

  void setupForTrading();

  bool tradeBestPrice(const currency_pair &currencyPair, uint64_t valueDate,
                      instrument inst, trade &trade);

  void tradeBestAll(std::vector<full_trade> &trades);

  const std::vector<maker> subscriptions() const;
  const Orders orders() const;
  const Quotes quotes() const;

private:
  bool validateSubscription(const maker &maker) const;
  bool validateOrderQuote(const quote &quote) const;
  bool validateOrder(const order &order) const;

private:
  std::vector<maker> m_subscriptions;
  Orders m_orders;
  Quotes m_quots;
};

#endif // MAPPED_DATA_H
