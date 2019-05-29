#ifndef MAKER_H
#define MAKER_H

#include <string>

class maker {
public:
  maker();
  maker(const std::string &dealcode, int uuid);

  const std::string &dealcode() const;
  int uuid() const;

  bool isValid() const;

  bool operator==(const maker &rhs) const;

  bool operator<(const maker &rhs) const;

private:
  std::string m_dealcode;
  int m_uuid;
};

#endif // MAKER_H
