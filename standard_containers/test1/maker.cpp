#include "maker.h"

maker::maker() : m_dealcode(), m_uuid(0) {}

maker::maker(const std::string &dealcode, int uuid)
    : m_dealcode(dealcode), m_uuid(uuid) {}

const std::string &maker::dealcode() const { return m_dealcode; }

int maker::uuid() const { return m_uuid; }

bool maker::isValid() const { return !m_dealcode.empty(); }

bool maker::operator==(const maker &rhs) const {
  return this->m_dealcode == rhs.m_dealcode && this->m_uuid == rhs.m_uuid;
}

bool maker::operator<(const maker &rhs) const {
  return this->m_dealcode < rhs.m_dealcode && this->m_uuid < rhs.m_uuid;
}
