#ifndef VIRTUAL_H
#define VIRTUAL_H

#include <cstddef>

class virtual_class {
public:
  virtual ~virtual_class();
  virtual void execute() = 0;
};

#endif // VIRTUAL_H
