#ifndef HASH_H
#define HASH_H

#include "common/common_types.h"

#include <cstddef>
#include <cstdint>

size_t compute_hash(const char *begin, size_t size);

size_t compute_hash(const struct dealcode &dc, int uuid);

size_t compute_hash(const struct currency_pair &cp, instrument inst,
                    uint64_t valueDate);

#endif // HASH_H
