#include <benchmark/benchmark.h>
#include <bits/stdc++.h>
#include <cmath>
#include <cstdlib>
#include <random>

class dataFix : public benchmark::Fixture {
public:
  void SetUp(const ::benchmark::State &state) {
    count = state.range(0);
    int64_t elem = state.range(1);
    int64_t bits = state.range(2);

    data = static_cast<uint64_t *>(malloc(sizeof(uint64_t) * count));
    memset(data, 0, sizeof(sizeof(uint64_t) * count));
    data[elem] = bits;
  }

  void TearDown(const ::benchmark::State &) {
    free(data);
    data = nullptr;
  }

protected:
  int64_t count{0};
  uint64_t *data{nullptr};
  int32_t elem;
  int32_t idx;
};

BENCHMARK_DEFINE_F(dataFix, bitfind)(benchmark::State &state) {
  for (auto _ : state) {
    for (int i = 0; i < 64; ++i) {
      const uint64_t test = (1u << i);
      const uint64_t mask = (data[0] & test);
      const bool val = mask == test;
      if (val) {
        idx = i;
        break;
      }
    }
    elem = 0;

    benchmark::DoNotOptimize(elem);
    benchmark::DoNotOptimize(idx);
    benchmark::ClobberMemory();
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
    for (int i = 0; i < 64; ++i) {
      const bool val = states[i];
      if (val) {
        idx = i;
        break;
      }
    }
    elem = 0;
    benchmark::DoNotOptimize(elem);
    benchmark::DoNotOptimize(idx);
    benchmark::ClobberMemory();
  }
}

BENCHMARK_DEFINE_F(dataFix, logfind)(benchmark::State &state) {
  for (auto _ : state) {
    const uint64_t x = data[0];
    benchmark::DoNotOptimize(x);
    benchmark::ClobberMemory();
    idx = std::log2(x & -x);
    elem = 0;
    benchmark::DoNotOptimize(elem);
    benchmark::DoNotOptimize(idx);
    benchmark::ClobberMemory();
  }
}

BENCHMARK_DEFINE_F(dataFix, ffsfind)(benchmark::State &state) {
  for (auto _ : state) {
    const uint64_t x = data[0];
    benchmark::DoNotOptimize(x);
    benchmark::ClobberMemory();
    idx = ffsl(x) - 1;
    elem = 0;
    benchmark::DoNotOptimize(elem);
    benchmark::DoNotOptimize(idx);
    benchmark::ClobberMemory();
  }
}

BENCHMARK_DEFINE_F(dataFix, ffsarrayfind)(benchmark::State &state) {
  for (auto _ : state) {
    for (int i = 0; i < count; ++i) {
      int index = __builtin_ffsl(static_cast<int64_t>(data[i]));
      if (index != 0) {
        elem = i;
        idx = index - 1;
        break;
      }
    }
    benchmark::DoNotOptimize(elem);
    benchmark::DoNotOptimize(idx);
    benchmark::ClobberMemory();
  }
}

static constexpr int32_t scale(int32_t i) {
  i--;
  i |= i >> 1;
  i |= i >> 2;
  i |= i >> 4;
  i |= i >> 8;
  i |= i >> 16;
  i++;
  return i;
}

static void test_div(benchmark::State &state) {

  int32_t v = state.range(0);
  int32_t h = state.range(1);

  int32_t a = scale(v);
  int32_t b = scale(h);

  int32_t p = __builtin_ffs(a) - 1;
  int32_t q = __builtin_ffs(v) - 1;
  int32_t r = p - q;

  int32_t n = (b - h);
  int32_t m = std::max(n - a, 0);
  int32_t o = m >> r;

  printf("v = %d, h = %d, div = %d | a = %d, b = %d, p = %d, q = %d, n = %d, m "
         "= %d, div = %d, div2 =%d\n",
         v, h, h / v, a, b, p, q, n, m, (b >> p), o);

  //  for (auto _ : state) {
  //  }
}

BENCHMARK(test_div)
    ->Args({16, 16 * 16})
    ->Args({16, 16 * 48})
    ->Args({24, 24 * 16})
    ->Args({24, 24 * 72})
    ->Args({48, 48 * 16})
    ->Args({48 * 8, 48 * 8 * 1000});

BENCHMARK_REGISTER_F(dataFix, bitfind)
    ->Args({1, 0, 1 << 6})
    ->Args({1, 0, (1 << 6) + (1 << 8)})
    ->Args({1, 0, (1 << 3) + (1 << 6) + (1 << 9)})
    ->Args({1, 0, (1 << 12) + (1 << 15)})
    ->Args({1, 0, (1 << 30)});

BENCHMARK_REGISTER_F(dataFix, loopfind)
    ->Args({1, 0, 1 << 6})
    ->Args({1, 0, (1 << 6) + (1 << 8)})
    ->Args({1, 0, (1 << 3) + (1 << 6) + (1 << 9)})
    ->Args({1, 0, (1 << 12) + (1 << 15)})
    ->Args({1, 0, (1 << 30)});

BENCHMARK_REGISTER_F(dataFix, logfind)
    ->Args({1, 0, 1 << 6})
    ->Args({1, 0, (1 << 6) + (1 << 8)})
    ->Args({1, 0, (1 << 3) + (1 << 6) + (1 << 9)})
    ->Args({1, 0, (1 << 12) + (1 << 15)})
    ->Args({1, 0, (1 << 30)});

BENCHMARK_REGISTER_F(dataFix, ffsfind)
    ->Args({1, 0, 1 << 6})
    ->Args({1, 0, (1 << 6) + (1 << 8)})
    ->Args({1, 0, (1 << 3) + (1 << 6) + (1 << 9)})
    ->Args({1, 0, (1 << 12) + (1 << 15)})
    ->Args({1, 0, (1 << 30)});

BENCHMARK_REGISTER_F(dataFix, ffsarrayfind)
    ->Args({1, 0, 1 << 6})
    ->Args({1, 0, (1 << 6) + (1 << 8)})
    ->Args({1, 0, (1 << 3) + (1 << 6) + (1 << 9)})
    ->Args({1, 0, (1 << 12) + (1 << 15)})
    ->Args({1, 0, (1 << 30)})
    ->Args({8, 4, 1 << 6})
    ->Args({8, 4, (1 << 6) + (1 << 8)})
    ->Args({8, 4, (1 << 3) + (1 << 6) + (1 << 9)})
    ->Args({8, 4, (1 << 12) + (1 << 15)})
    ->Args({8, 4, (1 << 30)})
    ->Args({32, 17, 1 << 6})
    ->Args({32, 17, (1 << 6) + (1 << 8)})
    ->Args({32, 17, (1 << 3) + (1 << 6) + (1 << 9)})
    ->Args({32, 17, (1 << 12) + (1 << 15)})
    ->Args({32, 17, (1 << 30)})
    ->Args({64, 57, 1 << 6})
    ->Args({64, 57, (1 << 6) + (1 << 8)})
    ->Args({64, 57, (1 << 3) + (1 << 6) + (1 << 9)})
    ->Args({64, 57, (1 << 12) + (1 << 15)})
    ->Args({64, 57, (1 << 30)})
    ->Args({512, 129, 1 << 6})
    ->Args({512, 129, (1 << 6) + (1 << 8)})
    ->Args({512, 129, (1 << 3) + (1 << 6) + (1 << 9)})
    ->Args({512, 129, (1 << 12) + (1 << 15)})
    ->Args({512, 129, (1 << 30)});

BENCHMARK_MAIN();
