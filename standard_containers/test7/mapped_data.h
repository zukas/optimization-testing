#ifndef MAPPED_DATA_H
#define MAPPED_DATA_H

#include <map>
#include <memory>
#include <utility>
#include <vector>

#include "maker.h"
#include "order.h"
#include "quote.h"
#include "trade.h"

class mapped_data {
public:
  typedef std::vector<quote> Quotes;
  typedef std::vector<order> Orders;
  typedef std::vector<size_t> HashTable;
  struct best_price {
    size_t maker_hash;
    double price;
  };
  typedef std::vector<best_price> BestPrices;

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
  bool validateOrder(const order &order) const;

private:
  HashTable m_subHashes;
  HashTable m_orderHashes;

  std::vector<maker> m_subscriptions;
  Orders m_orders;
  Quotes m_quots;
  BestPrices m_bestPrices;
};

#endif // MAPPED_DATA_H
