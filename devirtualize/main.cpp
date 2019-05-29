#include <benchmark/benchmark.h>
#include <cstdlib>
#include <random>

#include "test1.h"
#include "test2.h"

#include "callable.h"

#include <memory>
#include <random>

static void virtual_1(benchmark::State &state) {

  std::random_device
      rd; // Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<> dis(0, 57);
  std::vector<std::unique_ptr<virtual_class>> c;
  c.reserve(1024);
  for (size_t i = 0; i < 1024; ++i) {
    if (dis(gen) % 2 == 0) {
      c.push_back(std::make_unique<test1>());
    } else {
      c.push_back(std::make_unique<test2>());
    }
  }
  while (state.KeepRunning()) {
    int sum = 0;
    for (auto &p : c) {
      sum += p->execute();
    }
    benchmark::DoNotOptimize(sum);
  }
}

BENCHMARK(virtual_1);

void execute1(void *puser) noexcept { *static_cast<int *>(puser) += 10; }

void execute2(void *puser) noexcept { *static_cast<int *>(puser) += 20; }

static void callback_c(benchmark::State &state) {

  std::random_device
      rd; // Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<> dis(0, 57);
  std::vector<callable_reg> c;
  c.reserve(1024);
  int sum;
  for (size_t i = 0; i < 1024; ++i) {
    if (dis(gen) % 2 == 0) {
      c.push_back(callable_reg{type_t::T1, execute1, &sum});
    } else {
      c.push_back(callable_reg{type_t::T2, execute2, &sum});
    }
  }
  while (state.KeepRunning()) {
    sum = 0;
    for (auto &p : c) {
      invoke(p);
    }
    benchmark::DoNotOptimize(sum);
  }
}

BENCHMARK(callback_c);

BENCHMARK_MAIN();
