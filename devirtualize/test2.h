#ifndef TEST2_H
#define TEST2_H

#include "virtual.h"

class test2 final : public virtual_class {
public:
  test2();
  int execute() const noexcept override;
};

#endif // TEST2_H
