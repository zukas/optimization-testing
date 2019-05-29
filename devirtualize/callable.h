#ifndef CALLABLE_H
#define CALLABLE_H

enum type_t { T1, T2 };

typedef void (*execute)(void *puser);

struct callable_reg {
  type_t type;
  execute call;
  void *puser;
};

void invoke(const callable_reg &obj);

#endif // CALLABLE_H
