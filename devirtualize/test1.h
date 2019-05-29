#ifndef TEST1_H
#define TEST1_H

#include "virtual.h"

class test1 final : public virtual_class {
public:
  test1();
  int execute() const noexcept override;
};

#endif // TEST1_H
