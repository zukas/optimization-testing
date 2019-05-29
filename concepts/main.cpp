#include <benchmark/benchmark.h>
#include <cstdlib>
#include <random>

#include "concept_idioms.h"
#include "virtual.h"

template <> void execute<size_t>(const size_t &v) noexcept {
  benchmark::DoNotOptimize(v);
}

class testing_virtual : public virtual_class {

public:
  testing_virtual(size_t val) : val_(val) {}
  virtual ~testing_virtual() = default;
  virtual void execute() override { benchmark::DoNotOptimize(val_); }

private:
  size_t val_;
};

static void basic1(benchmark::State &state) {
  while (state.KeepRunning()) {
    std::vector<size_t> c;
    c.reserve(1024);
    for (size_t i = 0; i < 1024; ++i) {
      c.push_back(state.items_processed() + i);
    }
    benchmark::DoNotOptimize(c.data());
  }
}

BENCHMARK(basic1);

static void basic2(benchmark::State &state) {
  while (state.KeepRunning()) {
    std::vector<size_t> c;
    c.reserve(1024);
    for (size_t i = 0; i < 1024; ++i) {
      c.push_back(state.items_processed() + i);
    }
    for (const auto &v : c) {
      execute(v);
    }
  }
}

BENCHMARK(basic2);

static void idioms1(benchmark::State &state) {
  while (state.KeepRunning()) {
    concept_container_t c;
    c.reserve(1024);
    for (size_t i = 0; i < 1024; ++i) {
      c.push_back(state.items_processed() + i);
    }
    benchmark::DoNotOptimize(c.data());
  }
}

BENCHMARK(idioms1);

static void idioms2(benchmark::State &state) {
  while (state.KeepRunning()) {
    concept_container_t c;
    c.reserve(1024);
    for (size_t i = 0; i < 1024; ++i) {
      c.push_back(state.items_processed() + i);
    }
    execute(c);
  }
}

BENCHMARK(idioms2);

static void virtual1(benchmark::State &state) {
  while (state.KeepRunning()) {
    std::vector<std::unique_ptr<testing_virtual>> c;
    c.reserve(1024);
    for (size_t i = 0; i < 1024; ++i) {
      c.push_back(
          std::make_unique<testing_virtual>(state.items_processed() + i));
    }
    benchmark::DoNotOptimize(c.data());
  }
}

BENCHMARK(virtual1);

static void virtual2(benchmark::State &state) {
  while (state.KeepRunning()) {
    std::vector<std::unique_ptr<testing_virtual>> c;
    c.reserve(1024);
    for (size_t i = 0; i < 1024; ++i) {
      c.push_back(
          std::make_unique<testing_virtual>(state.items_processed() + i));
    }
    for (const auto &v : c) {
      v->execute();
    }
  }
}

BENCHMARK(virtual2);

BENCHMARK_MAIN();
