#include "trade.h"

#include "common/common_types.h"

trade::trade() : m_maker(), m_price(0) {}

trade::trade(const maker &maker, double price)
    : m_maker(maker), m_price(price) {}

const maker &trade::mk() const { return m_maker; }

double trade::price() const { return m_price; }

bool trade::isValid() const {
  return m_maker.isValid() && m_price > PRICE_ELLIPSIS;
}

full_trade::full_trade()
    : m_currencyPair(), m_inst(INVALID), m_valueDate(0), m_maker(), m_price(0) {

}

full_trade::full_trade(const currency_pair &currencyPair, instrument inst,
                       uint64_t valueDate, const maker &maker, double price)
    : m_currencyPair(currencyPair), m_inst(inst), m_valueDate(valueDate),
      m_maker(maker), m_price(price) {}

const currency_pair &full_trade::currencyPair() const { return m_currencyPair; }

instrument full_trade::inst() const { return m_inst; }

uint64_t full_trade::valueDate() const { return m_valueDate; }

const maker &full_trade::mk() const { return m_maker; }

double full_trade::price() const { return m_price; }

void full_trade::setPrice(double price) { m_price = price; }

bool full_trade::isValid() const {
  return !m_currencyPair.empty() && m_inst != INVALID && m_valueDate > 0 &&
         m_maker.isValid() && m_price > PRICE_ELLIPSIS;
}
