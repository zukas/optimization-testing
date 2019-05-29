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

  m_quots[m][quote.currencyPair()][quote.inst()][quote.valueDate()] =
      quote.price();
}

bool mapped_data::tradeBestPrice(const currency_pair &currencyPair,
                                 uint64_t valueDate, instrument inst,
                                 trade &trade) {
  double current_price = std::numeric_limits<double>::max();
  maker current_maker;

  for (QuoteMap::const_iterator qit = m_quots.begin(); qit != m_quots.end();
       ++qit) {

    const maker &maker = qit->first;
    const CurrencyPairPriceMap &currencyPairs = qit->second;
    CurrencyPairPriceMap::const_iterator cit = currencyPairs.find(currencyPair);
    if (cit != currencyPairs.end()) {

      const InstrumentPriceMap &instruments = cit->second;
      InstrumentPriceMap::const_iterator iit = instruments.find(inst);
      if (iit != instruments.end()) {

        const ValueDatePriceMap &valueDates = iit->second;
        ValueDatePriceMap::const_iterator vdit = valueDates.find(valueDate);
        if (vdit != valueDates.end()) {

          double price = vdit->second;
          if (price < current_price) {
            current_price = price;
            current_maker = maker;
          }
        }
      }
    }
  }

  if (current_maker.isValid() && current_price > PRICE_ELLIPSIS) {
    trade = ::trade(current_maker, current_price);
    return true;
  }
  return false;
}

void mapped_data::tradeBestAll(std::vector<full_trade> &trades) {
  for (QuoteMap::const_iterator qit = m_quots.begin(); qit != m_quots.end();
       ++qit) {

    const maker &maker = qit->first;
    const CurrencyPairPriceMap &currencyPairs = qit->second;

    for (CurrencyPairPriceMap::const_iterator cit = currencyPairs.begin();
         cit != currencyPairs.end(); ++cit) {

      const currency_pair currencyPair = cit->first;
      const InstrumentPriceMap &instruments = cit->second;

      for (InstrumentPriceMap::const_iterator iit = instruments.begin();
           iit != instruments.end(); ++iit) {

        instrument inst = iit->first;
        const ValueDatePriceMap &valueDates = iit->second;

        for (ValueDatePriceMap::const_iterator vit = valueDates.begin();
             vit != valueDates.end(); ++vit) {

          uint64_t valueDate = vit->first;
          const double price = vit->second;

          if (price > PRICE_ELLIPSIS) {

            std::vector<full_trade>::iterator tit =
                std::find_if(trades.begin(), trades.end(),
                             TradeAllPredicate(currencyPair, inst, valueDate));

            if (tit == trades.end()) {
              trades.push_back(
                  full_trade(currencyPair, inst, valueDate, maker, price));
            } else {
              full_trade &tr = *tit;
              if (tr.price() > price) {
                tr.setPrice(price);
              }
            }
          }
        }
      }
    }
  }
}

const std::vector<maker> mapped_data::subscriptions() const {
  return m_subscriptions;
}

const mapped_data::Orders mapped_data::orders() const { return m_orders; }

const mapped_data::QuoteMap mapped_data::quotes() const { return m_quots; }

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
