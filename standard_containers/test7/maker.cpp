#include "maker.h"

#include "hash.h"

maker::maker() : m_hash(0), m_dealcode({0, 0, 0, 0}), m_uuid(0) {}

maker::maker(const struct dealcode &dealcode, int uuid)
    : m_hash(compute_hash(dealcode, uuid)), m_dealcode(dealcode), m_uuid(uuid) {
}

size_t maker::hash() const { return m_hash; }

const dealcode &maker::dealcode() const { return m_dealcode; }

int maker::uuid() const { return m_uuid; }

bool maker::isValid() const { return !m_dealcode.empty(); }

bool maker::operator==(const maker &rhs) const {
  return m_hash == rhs.m_hash;
}

bool maker::operator<(const maker &rhs) const {
  return m_hash < rhs.m_hash;
}

bool maker::operator>(const maker &rhs) const {
  return m_hash > rhs.m_hash;
}
