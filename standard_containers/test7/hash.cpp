#include "hash.h"

#include "currency_pair.h"
#include "dealcode.h"
#include "maker.h"

#include <functional>

size_t combine_hash(size_t lhs, size_t rhs) {
  return lhs ^ (rhs + 0x9e3779b9 + (lhs << 6) + (lhs >> 2));
}

size_t compute_hash(const char *begin, size_t size) {
  std::hash<char> hash_fn;
  size_t hash = hash_fn(begin[0]);
  for (size_t i = 1; i < size; ++i) {
    hash = combine_hash(hash, hash_fn(begin[i]));
  }
  return hash;
}

size_t compute_hash(const dealcode &dc, int uuid) {
  return combine_hash(compute_hash(dc.data, 4), std::hash<int>()(uuid));
}

size_t compute_hash(const currency_pair &cp, instrument inst,
                    uint64_t valueDate) {
  return combine_hash(
      combine_hash(compute_hash(cp.data, 6), std::hash<uint64_t>()(valueDate)),
      std::hash<int>()(inst));
}
