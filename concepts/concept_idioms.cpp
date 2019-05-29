#include "concept_idioms.h"

#include <cstdio>
#include <functional>

concept_obj_t::concept_t::~concept_t() = default;

template <>
void execute<concept_container_t>(
    const concept_container_t &container) noexcept {
  for (const auto &v : container) {
    execute(v);
  }
}
