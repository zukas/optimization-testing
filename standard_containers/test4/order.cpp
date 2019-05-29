#include "order.h"

order::order()
    : m_orderId(0), m_currentyPair(), m_inst(INVALID), m_valueDate(0),
      m_amount(0) {}

order::order(int orderId, const std::string &currentyPair, instrument inst,
             uint64_t valueDate, double amount)
    : m_orderId(orderId), m_currentyPair(currentyPair), m_inst(inst),
      m_valueDate(valueDate), m_amount(amount) {}

int order::orderId() const { return m_orderId; }

const std::string &order::currencyPair() const { return m_currentyPair; }

instrument order::inst() const { return m_inst; }

uint64_t order::valueDate() const { return m_valueDate; }

double order::amount() { return m_amount; }
