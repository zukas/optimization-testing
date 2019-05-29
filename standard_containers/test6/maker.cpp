#include "maker.h"

maker::maker() : m_dealcode({0, 0, 0, 0}), m_uuid(0) {}

maker::maker(const struct dealcode &dealcode, int uuid)
    : m_dealcode(dealcode), m_uuid(uuid) {}

const dealcode &maker::dealcode() const { return m_dealcode; }

int maker::uuid() const { return m_uuid; }

bool maker::isValid() const { return !m_dealcode.empty(); }

bool maker::operator==(const maker &rhs) const {
  return this->m_dealcode == rhs.m_dealcode && this->m_uuid == rhs.m_uuid;
}

bool maker::operator<(const maker &rhs) const {
  return this->m_dealcode < rhs.m_dealcode ||
         (this->m_dealcode == rhs.m_dealcode && this->m_uuid < rhs.m_uuid);
}

bool maker::operator>(const maker &rhs) const {
  return this->m_dealcode > rhs.m_dealcode ||
         (this->m_dealcode == rhs.m_dealcode && this->m_uuid > rhs.m_uuid);
}
