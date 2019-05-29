#include "order.h"

#include "quote.h"

#include <string.h>

order::order()
    : m_valueDate(0), m_amount(0), m_orderId(0), m_inst(INVALID),
      m_currentyPair() {}

order::order(int orderId, const currency_pair &currentyPair, instrument inst,
             uint64_t valueDate, double amount)
    : m_valueDate(valueDate), m_amount(amount), m_orderId(orderId),
      m_inst(inst), m_currentyPair(currentyPair) {}

int order::orderId() const { return m_orderId; }

const currency_pair &order::currencyPair() const { return m_currentyPair; }

instrument order::inst() const { return m_inst; }

uint64_t order::valueDate() const { return m_valueDate; }

double order::amount() { return m_amount; }

bool operator<(const order &lhs, const order &rhs) {
  int cmp = strncmp(lhs.m_currentyPair.data, rhs.m_currentyPair.data, 6);
  return cmp < 0 || ((cmp == 0 && lhs.m_valueDate < rhs.m_valueDate) ||
                     (cmp == 0 && lhs.m_valueDate == rhs.m_valueDate &&
                      lhs.m_inst < rhs.m_inst));
}
