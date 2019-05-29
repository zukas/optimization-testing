#include "callable.h"

void invoke(const callable_reg &obj) {
  switch (obj.type) {
  case type_t::T1: {
    (*obj.call)(obj.puser);
    break;
  }
  case type_t::T2: {
    (*obj.call)(obj.puser);
    break;
  }
  }
}
