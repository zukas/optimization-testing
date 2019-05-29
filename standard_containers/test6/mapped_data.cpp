#include "mapped_data.h"

#include <algorithm>
#include <limits>

namespace {

class QuotePredicate {
public:
  bool operator()(const quote &lhs, const order &rhs) const {
    int cmp = strncmp(lhs.currencyPair().data, rhs.currencyPair().data, 6);
    return cmp < 0 || ((cmp == 0 && lhs.valueDate() < rhs.valueDate()) ||
                       (cmp == 0 && lhs.valueDate() == rhs.valueDate() &&
                        lhs.inst() < rhs.inst()));
  }

  bool operator()(const order &lhs, const quote &rhs) const {
    int cmp = strncmp(lhs.currencyPair().data, rhs.currencyPair().data, 6);
    return cmp < 0 || ((cmp == 0 && lhs.valueDate() < rhs.valueDate()) ||
                       (cmp == 0 && lhs.valueDate() == rhs.valueDate() &&
                        lhs.inst() < rhs.inst()));
  }
};

class TradeAllPredicate {
public:
  TradeAllPredicate(const currency_pair &currencyPair, instrument inst,
                    uint64_t valueDate)
      : m_currencyPair(currencyPair), m_inst(inst), m_valueDate(valueDate) {}

  bool operator()(const full_trade &trade) {
    return trade.currencyPair() == m_currencyPair && trade.inst() == m_inst &&
           trade.valueDate() == m_valueDate;
  }

private:
  const currency_pair &m_currencyPair;
  instrument m_inst;
  uint64_t m_valueDate;
};

struct trade_request {
  uint64_t valueDate;
  currency_pair currencyPair;
  char _padding1[2];
  instrument inst;
  char _padding2[4];
};

class TradePredicate {
public:
  bool operator()(const quote &lhs, const trade_request &rhs) const {
    int cmp = strncmp(lhs.currencyPair().data, rhs.currencyPair.data, 6);
    return cmp < 0 || ((cmp == 0 && lhs.valueDate() < rhs.valueDate) ||
                       (cmp == 0 && lhs.valueDate() == rhs.valueDate &&
                        lhs.inst() < rhs.inst));
  }
};

bool equal(const quote &lhs, const trade_request &rhs) {
  return strncmp(lhs.currencyPair().data, rhs.currencyPair.data, 6) == 0 &&
         lhs.valueDate() == rhs.valueDate && lhs.inst() == rhs.inst;
}

} // namespace

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

  maker m(quote.dealcode(), quote.uuid());

  if (!validateSubscription(m)) {
    return; // not subscribed
  }

  if (!validateOrderQuote(quote)) {
    return; // no such order
  }

  Quotes::iterator it = std::lower_bound(m_quots.begin(), m_quots.end(), quote);
  it->setPrice(quote.price());
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
}

bool mapped_data::tradeBestPrice(const currency_pair &currencyPair,
                                 uint64_t valueDate, instrument inst,
                                 trade &trade) {
  double current_price = std::numeric_limits<double>::max();
  maker current_maker;

  trade_request req;
  req.valueDate = valueDate;
  req.currencyPair = currencyPair;
  req.inst = inst;

  Quotes::const_iterator end = m_quots.cend();
  Quotes::const_iterator it =
      std::lower_bound(m_quots.cbegin(), end, req, TradePredicate());

  while (it != end && equal(*it, req)) {
    const quote &q = *it++;
    if (q.price() > PRICE_ELLIPSIS && q.price() < current_price) {
      current_price = q.price();
      current_maker = maker(q.dealcode(), q.uuid());
    }
  }

  if (current_maker.isValid() && current_price > PRICE_ELLIPSIS) {
    trade = ::trade(current_maker, current_price);
    return true;
  }
  return false;
}

void mapped_data::tradeBestAll(std::vector<full_trade> &trades) {

  trades.clear();
  trades.reserve(m_orders.size());

  std::vector<full_trade>::iterator tit = trades.begin();
  for (Quotes::const_iterator qit = m_quots.begin(); qit != m_quots.end();
       ++qit) {
    const quote &q = *qit;
    if (q.price() > PRICE_ELLIPSIS && !q.dealcode().empty()) {
      if (tit == trades.end()) {
        tit = trades.insert(
            trades.end(), full_trade(q.currencyPair(), q.inst(), q.valueDate(),
                                     maker(q.dealcode(), q.uuid()), q.price()));
      } else {

        full_trade &tr = *tit;
        if (q.currencyPair() == tr.currencyPair() && q.inst() == tr.inst() &&
            q.valueDate() == tr.valueDate()) {
          if (q.price() < tr.price()) {
            tr.setPrice(q.price());
          }
        } else {
          tit = trades.insert(
              trades.end(),
              full_trade(q.currencyPair(), q.inst(), q.valueDate(),
                         maker(q.dealcode(), q.uuid()), q.price()));
        }
      }
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

bool mapped_data::validateOrderQuote(const quote &quote) const {

  return std::binary_search(m_orders.begin(), m_orders.end(), quote,
                            QuotePredicate());
}

bool mapped_data::validateOrder(const order &order) const {

  return std::binary_search(m_orders.begin(), m_orders.end(), order);
}
