#include <benchmark/benchmark.h>
#include <bits/stdc++.h>
#include <cmath>
#include <cstdlib>
#include <random>

class dataFix : public benchmark::Fixture {
public:
  void SetUp(const ::benchmark::State &state) {
    int64_t elem = state.range(0);
    int64_t bits = state.range(1);
    data[elem] = bits;
  }

  void TearDown(const ::benchmark::State &) { memset(data, 0, sizeof(data)); }

protected:
  uint64_t data[64]{0};
};

BENCHMARK_DEFINE_F(dataFix, bitfind)(benchmark::State &state) {
  for (auto _ : state) {
    int index = 0;
    for (int i = 0; i < 64; ++i) {
      const uint64_t test = (1u << i);
      const uint64_t mask = (data[0] & test);
      const bool val = mask == test;
      if (val) {
        benchmark::DoNotOptimize(index = i);
        benchmark::ClobberMemory();
        break;
      }
    }
  }
}

BENCHMARK_DEFINE_F(dataFix, loopfind)(benchmark::State &state) {
  const uint64_t x = data[0];
  benchmark::DoNotOptimize(x);
  bool states[64];
  for (uint64_t i = 0; i < 64; ++i) {
    const uint64_t test = (1u << i);
    const uint64_t mask = (x & test);
    states[i] = mask == test;
  }
  benchmark::DoNotOptimize(states);
  benchmark::ClobberMemory();

  for (auto _ : state) {
    int index = 0;
    for (int i = 0; i < 64; ++i) {
      const bool val = states[i];
      if (val) {
        benchmark::DoNotOptimize(index = i);
        benchmark::ClobberMemory();
        break;
      }
    }
  }
}

BENCHMARK_DEFINE_F(dataFix, logfind)(benchmark::State &state) {
  for (auto _ : state) {
    const uint64_t x = data[0];
    benchmark::DoNotOptimize(x);
    benchmark::ClobberMemory();
    int index = std::log2(x & -x);
    benchmark::DoNotOptimize(index);
    benchmark::ClobberMemory();
  }
}

BENCHMARK_DEFINE_F(dataFix, ffsfind)(benchmark::State &state) {
  for (auto _ : state) {
    const uint64_t x = data[0];
    benchmark::DoNotOptimize(x);
    benchmark::ClobberMemory();
    int index = ffsl(x) - 1;
    benchmark::DoNotOptimize(index);
    benchmark::ClobberMemory();
  }
}

BENCHMARK_DEFINE_F(dataFix, ffsarrayfind)(benchmark::State &state) {
  for (auto _ : state) {
    int index = 0;
    int elem = -1;
    for (int i = 0; i < 64; ++i) {
      index = ffsl(data[i]);
      if (index != 0) {
        benchmark::DoNotOptimize(elem = i);
        benchmark::DoNotOptimize(--index);
        benchmark::ClobberMemory();
        break;
      }
    };
  }
}

BENCHMARK_DEFINE_F(dataFix, DeBruijnfind)(benchmark::State &state) {

  constexpr const int MultiplyDeBruijnBitPosition[32] = {
      0,  1,  28, 2,  29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4,  8,
      31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6,  11, 5,  10, 9};

  for (auto _ : state) {
    const int64_t x = data[0];
    benchmark::DoNotOptimize(x);
    benchmark::ClobberMemory();
    int index =
        MultiplyDeBruijnBitPosition[((uint32_t)((x & -x) * 0x077CB531U)) >> 27];
    printf("%d\n", index);
    benchmark::DoNotOptimize(index);
    benchmark::ClobberMemory();
  }
}

BENCHMARK_REGISTER_F(dataFix, bitfind)
    ->ArgPair(1, 1 << 6)
    ->ArgPair(1, (1 << 6) + (1 << 8))
    ->ArgPair(1, (1 << 3) + (1 << 6) + (1 << 9))
    ->ArgPair(1, (1 << 12) + (1 << 15))
    ->ArgPair(1, (1 << 30));

BENCHMARK_REGISTER_F(dataFix, loopfind)
    ->ArgPair(1, 1 << 6)
    ->ArgPair(1, (1 << 6) + (1 << 8))
    ->ArgPair(1, (1 << 3) + (1 << 6) + (1 << 9))
    ->ArgPair(1, (1 << 12) + (1 << 15))
    ->ArgPair(1, (1 << 30));

BENCHMARK_REGISTER_F(dataFix, logfind)
    ->ArgPair(1, 1 << 6)
    ->ArgPair(1, (1 << 6) + (1 << 8))
    ->ArgPair(1, (1 << 3) + (1 << 6) + (1 << 9))
    ->ArgPair(1, (1 << 12) + (1 << 15))
    ->ArgPair(1, (1 << 30));

BENCHMARK_REGISTER_F(dataFix, ffsfind)
    ->ArgPair(1, 1 << 6)
    ->ArgPair(1, (1 << 6) + (1 << 8))
    ->ArgPair(1, (1 << 3) + (1 << 6) + (1 << 9))
    ->ArgPair(1, (1 << 12) + (1 << 15))
    ->ArgPair(1, (1 << 30));

BENCHMARK_REGISTER_F(dataFix, DeBruijnfind)
    ->ArgPair(1, 1 << 6)
    ->ArgPair(1, (1 << 6) + (1 << 8))
    ->ArgPair(1, (1 << 3) + (1 << 6) + (1 << 9))
    ->ArgPair(1, (1 << 12) + (1 << 15))
    ->ArgPair(1, (1 << 30));

BENCHMARK_REGISTER_F(dataFix, ffsarrayfind)
    ->ArgPair(1, 1 << 6)
    ->ArgPair(1, (1 << 6) + (1 << 8))
    ->ArgPair(1, (1 << 3) + (1 << 6) + (1 << 9))
    ->ArgPair(1, (1 << 12) + (1 << 15))
    ->ArgPair(1, (1 << 30))
    ->ArgPair(4, 1 << 6)
    ->ArgPair(4, (1 << 6) + (1 << 8))
    ->ArgPair(4, (1 << 3) + (1 << 6) + (1 << 9))
    ->ArgPair(4, (1 << 12) + (1 << 15))
    ->ArgPair(4, (1 << 30))
    ->ArgPair(17, 1 << 6)
    ->ArgPair(17, (1 << 6) + (1 << 8))
    ->ArgPair(17, (1 << 3) + (1 << 6) + (1 << 9))
    ->ArgPair(17, (1 << 12) + (1 << 15))
    ->ArgPair(17, (1 << 30))
    ->ArgPair(57, 1 << 6)
    ->ArgPair(57, (1 << 6) + (1 << 8))
    ->ArgPair(57, (1 << 3) + (1 << 6) + (1 << 9))
    ->ArgPair(57, (1 << 12) + (1 << 15))
    ->ArgPair(57, (1 << 30));

BENCHMARK_MAIN();
