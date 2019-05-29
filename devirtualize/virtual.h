#ifndef VIRTUAL_H
#define VIRTUAL_H

#include <cstddef>

class virtual_class {
public:
  virtual int execute() const noexcept = 0;
};

#endif // VIRTUAL_H
