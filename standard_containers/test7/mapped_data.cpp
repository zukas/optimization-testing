#include "mapped_data.h"

#include "hash.h"

#include <algorithm>
#include <limits>

mapped_data::mapped_data() {}

void mapped_data::addSubscription(const maker &maker) {
  if (!validateSubscription(maker)) {
    m_subscriptions.insert(
        std::lower_bound(m_subscriptions.begin(), m_subscriptions.end(), maker),
        maker);
  }
}

void mapped_data::addOrder(const order &order) {

  if (!validateOrder(order)) {
    m_orders.insert(std::lower_bound(m_orders.begin(), m_orders.end(), order),
                    order);
  }
}

void mapped_data::handleQuote(const quote &quote) {

  const size_t maker_hash = compute_hash(quote.dealcode(), quote.uuid());
  const HashTable::const_iterator sub_begin = m_subHashes.begin();
  const HashTable::const_iterator sub_end = m_subHashes.end();
  const HashTable::const_iterator sub_it =
      std::lower_bound(sub_begin, sub_end, maker_hash);
  const size_t maker_index =
      static_cast<size_t>(std::distance(sub_begin, sub_it));

  if (sub_it == sub_end) {
    return; // not subscribed
  }

  const HashTable::const_iterator order_begin = m_orderHashes.begin();
  const HashTable::const_iterator order_end = m_orderHashes.end();
  const HashTable::const_iterator order_it =
      std::lower_bound(order_begin, order_end, quote.hash());
  const size_t order_index =
      static_cast<size_t>(std::distance(order_begin, order_it));

  if (order_it == order_end) {
    return; // no such order
  }

  best_price &best = m_bestPrices[order_index];
  if (!(best.price > PRICE_ELLIPSIS) || best.price > quote.price()) {
    best.maker_hash = maker_hash;
    best.price = quote.price();
  }

  m_quots[order_index * m_subHashes.size() + maker_index].setPrice(
      quote.price());
}

void mapped_data::setupForTrading() {
  m_quots.clear();
  m_quots.reserve(m_orders.size() * m_subscriptions.size());
  for (const auto &order : m_orders) {
    for (const auto &trader : m_subscriptions) {
      m_quots.push_back(quote(order.currencyPair(), order.valueDate(),
                              order.inst(), 0, trader.dealcode(),
                              trader.uuid()));
    }
  }

  m_subHashes.clear();
  m_orderHashes.clear();
  m_bestPrices.clear();

  m_subHashes.reserve(m_subscriptions.size());
  m_orderHashes.reserve(m_orders.size());
  m_bestPrices.resize(m_orders.size());

  for (const auto &maker : m_subscriptions) {
    m_subHashes.push_back(maker.hash());
  }

  best_price best;
  best.maker_hash = 0;
  best.price = 0;

  for (const auto &order : m_orders) {
    m_orderHashes.push_back(order.hash());
    m_bestPrices.push_back(best);
  }
}

bool mapped_data::tradeBestPrice(const currency_pair &currencyPair,
                                 uint64_t valueDate, instrument inst,
                                 trade &trade) {
  const size_t order_hash = compute_hash(currencyPair, inst, valueDate);
  const HashTable::const_iterator order_begin = m_orderHashes.begin();
  const HashTable::const_iterator order_end = m_orderHashes.end();
  const HashTable::const_iterator order_it =
      std::lower_bound(order_begin, order_end, order_hash);
  const size_t order_index =
      static_cast<size_t>(std::distance(order_begin, order_it));

  const best_price &best = m_bestPrices[order_index];

  if (!(best.price > PRICE_ELLIPSIS) || best.maker_hash == 0) {
    return false;
  }

  const HashTable::const_iterator sub_begin = m_subHashes.begin();
  const HashTable::const_iterator sub_end = m_subHashes.end();
  const HashTable::const_iterator sub_it =
      std::lower_bound(sub_begin, sub_end, best.maker_hash);
  const size_t maker_index =
      static_cast<size_t>(std::distance(sub_begin, sub_it));

  trade = ::trade(m_subscriptions[maker_index], best.price);
  return true;
}

void mapped_data::tradeBestAll(std::vector<full_trade> &trades) {
  trades.clear();
  trades.reserve(m_bestPrices.size());

  for (size_t i = 0, size = m_bestPrices.size(); i < size; ++i) {
    const best_price &best = m_bestPrices[i];
    if (best.price > PRICE_ELLIPSIS && best.maker_hash > 0) {
      const HashTable::const_iterator sub_begin = m_subHashes.begin();
      const HashTable::const_iterator sub_end = m_subHashes.end();
      const HashTable::const_iterator sub_it =
          std::lower_bound(sub_begin, sub_end, best.maker_hash);
      const size_t maker_index =
          static_cast<size_t>(std::distance(sub_begin, sub_it));

      const order &o = m_orders[i];
      const maker &m = m_subscriptions[maker_index];
      trades.push_back(
          full_trade(o.currencyPair(), o.inst(), o.valueDate(), m, best.price));
    }
  }
}

const std::vector<maker> mapped_data::subscriptions() const {
  return m_subscriptions;
}

const mapped_data::Orders mapped_data::orders() const { return m_orders; }

const mapped_data::Quotes mapped_data::quotes() const { return m_quots; }

bool mapped_data::validateSubscription(const maker &maker) const {
  return std::binary_search(m_subscriptions.begin(), m_subscriptions.end(),
                            maker);
}

bool mapped_data::validateOrder(const order &order) const {

  return std::binary_search(m_orders.begin(), m_orders.end(), order);
}
