#include "quote.h"

quote::quote()
    : m_currencyPair(), m_valueDate(0), m_price(0), m_dealcode(), m_uuid(0) {}

quote::quote(const currency_pair &currencyPair, uint64_t valueDate,
             instrument inst, double price, const struct dealcode &dealcode,
             int uuid)
    : m_currencyPair(currencyPair), m_valueDate(valueDate), m_inst(inst),
      m_price(price), m_dealcode(dealcode), m_uuid(uuid) {}

const currency_pair &quote::currencyPair() const { return m_currencyPair; }

uint64_t quote::valueDate() const { return m_valueDate; }

instrument quote::inst() const { return m_inst; }

double quote::price() const { return m_price; }

const struct dealcode &quote::dealcode() const { return m_dealcode; }

int quote::uuid() const { return m_uuid; }

void quote::setPrice(double price) { m_price = price; }
