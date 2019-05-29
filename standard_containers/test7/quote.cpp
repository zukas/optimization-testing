#include "quote.h"

#include "hash.h"

#include <string.h>

quote::quote()
    : m_hash(0), m_dealcode(), m_uuid(0), m_valueDate(0), m_price(0),
      m_currencyPair(), m_inst(INVALID) {}

quote::quote(const currency_pair &currencyPair, uint64_t valueDate,
             instrument inst, double price, const struct dealcode &dealcode,
             int uuid)
    : m_hash(compute_hash(currencyPair, inst, valueDate)), m_dealcode(dealcode),
      m_uuid(uuid), m_valueDate(valueDate), m_price(price),
      m_currencyPair(currencyPair), m_inst(inst) {}

size_t quote::hash() const { return m_hash; }

const currency_pair &quote::currencyPair() const { return m_currencyPair; }

uint64_t quote::valueDate() const { return m_valueDate; }

instrument quote::inst() const { return m_inst; }

double quote::price() const { return m_price; }

const struct dealcode &quote::dealcode() const { return m_dealcode; }

int quote::uuid() const { return m_uuid; }

void quote::setPrice(double price) { m_price = price; }

bool operator<(const quote &lhs, const quote &rhs) {
  return lhs.m_hash < rhs.m_hash;
}
