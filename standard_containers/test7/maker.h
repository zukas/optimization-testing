#ifndef MAKER_H
#define MAKER_H

#include "dealcode.h"

class maker {
public:
  maker();
  maker(const struct dealcode &dealcode, int uuid);

  size_t hash() const;

  const struct dealcode &dealcode() const;
  int uuid() const;

  bool isValid() const;

  bool operator==(const maker &rhs) const;

  bool operator<(const maker &rhs) const;
  bool operator>(const maker &rhs) const;

private:
  size_t m_hash;
  struct dealcode m_dealcode;
  int m_uuid;
};

#endif // MAKER_H
