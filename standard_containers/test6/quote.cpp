#include "quote.h"

#include <string.h>

quote::quote()
    : m_dealcode(), m_uuid(0), m_valueDate(0), m_price(0), m_currencyPair(),
      m_inst(INVALID) {}

quote::quote(const currency_pair &currencyPair, uint64_t valueDate,
             instrument inst, double price, const struct dealcode &dealcode,
             int uuid)
    : m_dealcode(dealcode), m_uuid(uuid), m_valueDate(valueDate),
      m_price(price), m_currencyPair(currencyPair), m_inst(inst) {}

const currency_pair &quote::currencyPair() const { return m_currencyPair; }

uint64_t quote::valueDate() const { return m_valueDate; }

instrument quote::inst() const { return m_inst; }

double quote::price() const { return m_price; }

const struct dealcode &quote::dealcode() const { return m_dealcode; }

int quote::uuid() const { return m_uuid; }

void quote::setPrice(double price) { m_price = price; }

bool operator<(const quote &lhs, const quote &rhs) {
  const int cmp1 = strncmp(lhs.m_dealcode.data, rhs.m_dealcode.data, 4);
  const int cmp2 = strncmp(lhs.m_currencyPair.data, rhs.m_currencyPair.data, 6);
  return cmp2 < 0 || ((cmp2 == 0 && lhs.m_valueDate < rhs.m_valueDate) ||
                      ((cmp2 == 0 && lhs.m_valueDate == rhs.m_valueDate &&
                        lhs.m_inst < rhs.m_inst) ||
                       ((cmp2 == 0 && lhs.m_valueDate == rhs.m_valueDate &&
                         lhs.m_inst == rhs.m_inst && cmp1 < 0) ||
                        (cmp2 == 0 && lhs.m_valueDate == rhs.m_valueDate &&
                         lhs.m_inst == rhs.m_inst && cmp1 == 0 &&
                         lhs.m_uuid < rhs.m_uuid))));
}
