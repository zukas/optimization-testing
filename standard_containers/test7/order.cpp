#include "order.h"

#include "hash.h"
#include "quote.h"

#include <string.h>

order::order()
    : m_hash(0), m_valueDate(0), m_amount(0), m_orderId(0), m_inst(INVALID),
      m_currentyPair() {}

order::order(int orderId, const currency_pair &currentyPair, instrument inst,
             uint64_t valueDate, double amount)
    : m_hash(compute_hash(currentyPair, inst, valueDate)),
      m_valueDate(valueDate), m_amount(amount), m_orderId(orderId),
      m_inst(inst), m_currentyPair(currentyPair) {}

size_t order::hash() const { return m_hash; }

int order::orderId() const { return m_orderId; }

const currency_pair &order::currencyPair() const { return m_currentyPair; }

instrument order::inst() const { return m_inst; }

uint64_t order::valueDate() const { return m_valueDate; }

double order::amount() { return m_amount; }

bool operator<(const order &lhs, const order &rhs) {
  return lhs.m_hash < rhs.m_hash;
}
