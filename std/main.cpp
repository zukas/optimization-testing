#include <benchmark/benchmark.h>
#include <bits/stdc++.h>
#include <cmath>
#include <cstdlib>
#include <random>

struct type_64 {
  char buffer[64];
};

struct type_128 {
  char buffer[128];
};

struct type_256 {
  char buffer[256];
};

#define UNLIKLY(x) __builtin_expect(static_cast<bool>(x), 0)

static std::string gen_string() {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  static std::uniform_int_distribution<char> lex_dis('A', 'Z');
  static std::uniform_int_distribution<size_t> range_dis(5, 25);

  size_t size = range_dis(gen);
  std::string res;
  res.resize(size);
  for (size_t i = 0; i < size; ++i) {
    res[i] = lex_dis(gen);
  }
  return res;
}

static void bench_vector_64_iterate(benchmark::State &state) {

  size_t count = static_cast<size_t>(state.range(0));

  std::vector<std::pair<std::string, type_64>> data;
  data.reserve(count);

  for (size_t i = 0; i < count; ++i) {
    data.push_back(std::make_pair(gen_string(), type_64()));
  }

  benchmark::DoNotOptimize(data.data());

  for (auto _ : state) {

    int64_t sum = 0;
    for (const auto &e : data) {
      sum += e.second.buffer[0];
    }
    benchmark::DoNotOptimize(sum);
    benchmark::ClobberMemory();
  }
}

BENCHMARK(bench_vector_64_iterate)->Arg(2 << 4)->Arg(2 << 8)->Arg(2 << 12);

static void bench_map_64_iterate(benchmark::State &state) {

  size_t count = static_cast<size_t>(state.range(0));

  std::map<std::string, type_64> data;

  for (size_t i = 0; i < count; ++i) {
    data.insert(std::make_pair(gen_string(), type_64()));
  }

  benchmark::DoNotOptimize(data);

  for (auto _ : state) {

    int64_t sum = 0;
    for (const auto &e : data) {
      sum += e.second.buffer[0];
    }
    benchmark::DoNotOptimize(sum);
    benchmark::ClobberMemory();
  }
}

BENCHMARK(bench_map_64_iterate)->Arg(2 << 4)->Arg(2 << 8)->Arg(2 << 12);

static void bench_unordered_map_64_iterate(benchmark::State &state) {

  size_t count = static_cast<size_t>(state.range(0));

  std::unordered_map<std::string, type_64> data;

  for (size_t i = 0; i < count; ++i) {
    data.insert(std::make_pair(gen_string(), type_64()));
  }

  benchmark::DoNotOptimize(data);

  for (auto _ : state) {

    int64_t sum = 0;
    for (const auto &e : data) {
      sum += e.second.buffer[0];
    }
    benchmark::DoNotOptimize(sum);
    benchmark::ClobberMemory();
  }
}

BENCHMARK(bench_unordered_map_64_iterate)
    ->Arg(2 << 4)
    ->Arg(2 << 8)
    ->Arg(2 << 12);

static void bench_vector_128_iterate(benchmark::State &state) {

  size_t count = static_cast<size_t>(state.range(0));

  std::vector<std::pair<std::string, type_128>> data;
  data.reserve(count);

  for (size_t i = 0; i < count; ++i) {
    data.push_back(std::make_pair(gen_string(), type_128()));
  }

  benchmark::DoNotOptimize(data.data());

  for (auto _ : state) {

    int64_t sum = 0;
    for (const auto &e : data) {
      sum += e.second.buffer[0];
    }
    benchmark::DoNotOptimize(sum);
    benchmark::ClobberMemory();
  }
}

BENCHMARK(bench_vector_128_iterate)->Arg(2 << 4)->Arg(2 << 8)->Arg(2 << 12);

static void bench_map_128_iterate(benchmark::State &state) {

  size_t count = static_cast<size_t>(state.range(0));

  std::map<std::string, type_128> data;

  for (size_t i = 0; i < count; ++i) {
    data.insert(std::make_pair(gen_string(), type_128()));
  }

  benchmark::DoNotOptimize(data);

  for (auto _ : state) {

    int64_t sum = 0;
    for (const auto &e : data) {
      sum += e.second.buffer[0];
    }
    benchmark::DoNotOptimize(sum);
    benchmark::ClobberMemory();
  }
}

BENCHMARK(bench_map_128_iterate)->Arg(2 << 4)->Arg(2 << 8)->Arg(2 << 12);

static void bench_unordered_map_128_iterate(benchmark::State &state) {

  size_t count = static_cast<size_t>(state.range(0));

  std::unordered_map<std::string, type_128> data;

  for (size_t i = 0; i < count; ++i) {
    data.insert(std::make_pair(gen_string(), type_128()));
  }

  benchmark::DoNotOptimize(data);

  for (auto _ : state) {

    int64_t sum = 0;
    for (const auto &e : data) {
      sum += e.second.buffer[0];
    }
    benchmark::DoNotOptimize(sum);
    benchmark::ClobberMemory();
  }
}

BENCHMARK(bench_unordered_map_128_iterate)
    ->Arg(2 << 4)
    ->Arg(2 << 8)
    ->Arg(2 << 12);

static void bench_vector_256_iterate(benchmark::State &state) {

  size_t count = static_cast<size_t>(state.range(0));

  std::vector<std::pair<std::string, type_256>> data;
  data.reserve(count);

  for (size_t i = 0; i < count; ++i) {
    data.push_back(std::make_pair(gen_string(), type_256()));
  }

  benchmark::DoNotOptimize(data.data());

  for (auto _ : state) {

    int64_t sum = 0;
    for (const auto &e : data) {
      sum += e.second.buffer[0];
    }
    benchmark::DoNotOptimize(sum);
    benchmark::ClobberMemory();
  }
}

BENCHMARK(bench_vector_256_iterate)->Arg(2 << 4)->Arg(2 << 8)->Arg(2 << 12);

static void bench_map_256_iterate(benchmark::State &state) {

  size_t count = static_cast<size_t>(state.range(0));

  std::map<std::string, type_256> data;

  for (size_t i = 0; i < count; ++i) {
    data.insert(std::make_pair(gen_string(), type_256()));
  }

  benchmark::DoNotOptimize(data);

  for (auto _ : state) {

    int64_t sum = 0;
    for (const auto &e : data) {
      sum += e.second.buffer[0];
    }
    benchmark::DoNotOptimize(sum);
    benchmark::ClobberMemory();
  }
}

BENCHMARK(bench_map_256_iterate)->Arg(2 << 4)->Arg(2 << 8)->Arg(2 << 12);

static void bench_unordered_map_256_iterate(benchmark::State &state) {

  size_t count = static_cast<size_t>(state.range(0));

  std::unordered_map<std::string, type_256> data;

  for (size_t i = 0; i < count; ++i) {
    data.insert(std::make_pair(gen_string(), type_256()));
  }

  benchmark::DoNotOptimize(data);

  for (auto _ : state) {

    int64_t sum = 0;
    for (const auto &e : data) {
      sum += e.second.buffer[0];
    }
    benchmark::DoNotOptimize(sum);
    benchmark::ClobberMemory();
  }
}

BENCHMARK(bench_unordered_map_256_iterate)
    ->Arg(2 << 4)
    ->Arg(2 << 8)
    ->Arg(2 << 12);

static void bench_vector_64_find(benchmark::State &state) {

  size_t count = static_cast<size_t>(state.range(0));

  std::vector<std::pair<std::string, type_64>> data;
  data.reserve(count);

  for (size_t i = 0; i < count; ++i) {
    data.push_back(std::make_pair(gen_string(), type_64()));
  }

  benchmark::DoNotOptimize(data.data());

  for (auto _ : state) {

    state.PauseTiming();
    std::string key = gen_string();
    state.ResumeTiming();

    type_64 *elem = ([&]() {
      for (auto &e : data) {
        if (e.first == key) {
          return &e.second;
        }
      }
      return static_cast<type_64 *>(nullptr);
    })();

    benchmark::DoNotOptimize(elem);
    benchmark::ClobberMemory();
  }
}

BENCHMARK(bench_vector_64_find)->Arg(2 << 4)->Arg(2 << 8)->Arg(2 << 12);

static void bench_map_64_find(benchmark::State &state) {

  size_t count = static_cast<size_t>(state.range(0));

  std::map<std::string, type_64> data;

  for (size_t i = 0; i < count; ++i) {
    data.insert(std::make_pair(gen_string(), type_64()));
  }

  benchmark::DoNotOptimize(data);

  for (auto _ : state) {

    state.PauseTiming();
    std::string key = gen_string();
    state.ResumeTiming();

    type_64 *elem = ([&]() {
      auto it = data.find(key);
      if (it != data.end()) {
        return &it->second;
      }
      return static_cast<type_64 *>(nullptr);
    })();

    benchmark::DoNotOptimize(elem);
    benchmark::ClobberMemory();
  }
}

BENCHMARK(bench_map_64_find)->Arg(2 << 4)->Arg(2 << 8)->Arg(2 << 12);

static void bench_unordered_map_64_find(benchmark::State &state) {

  size_t count = static_cast<size_t>(state.range(0));

  std::unordered_map<std::string, type_64> data;

  for (size_t i = 0; i < count; ++i) {
    data.insert(std::make_pair(gen_string(), type_64()));
  }

  benchmark::DoNotOptimize(data);

  for (auto _ : state) {

    state.PauseTiming();
    std::string key = gen_string();
    state.ResumeTiming();

    type_64 *elem = ([&]() {
      auto it = data.find(key);
      if (it != data.end()) {
        return &it->second;
      }
      return static_cast<type_64 *>(nullptr);
    })();

    benchmark::DoNotOptimize(elem);
    benchmark::ClobberMemory();
  }
}

BENCHMARK(bench_unordered_map_64_find)->Arg(2 << 4)->Arg(2 << 8)->Arg(2 << 12);

static void bench_vector_128_find(benchmark::State &state) {

  size_t count = static_cast<size_t>(state.range(0));

  std::vector<std::pair<std::string, type_128>> data;
  data.reserve(count);

  for (size_t i = 0; i < count; ++i) {
    data.push_back(std::make_pair(gen_string(), type_128()));
  }

  benchmark::DoNotOptimize(data.data());

  for (auto _ : state) {

    state.PauseTiming();
    std::string key = gen_string();
    state.ResumeTiming();

    type_128 *elem = ([&]() {
      for (auto &e : data) {
        if (e.first == key) {
          return &e.second;
        }
      }
      return static_cast<type_128 *>(nullptr);
    })();

    benchmark::DoNotOptimize(elem);
    benchmark::ClobberMemory();
  }
}

BENCHMARK(bench_vector_128_find)->Arg(2 << 4)->Arg(2 << 8)->Arg(2 << 12);

static void bench_map_128_find(benchmark::State &state) {

  size_t count = static_cast<size_t>(state.range(0));

  std::map<std::string, type_128> data;

  for (size_t i = 0; i < count; ++i) {
    data.insert(std::make_pair(gen_string(), type_128()));
  }

  benchmark::DoNotOptimize(data);

  for (auto _ : state) {

    state.PauseTiming();
    std::string key = gen_string();
    state.ResumeTiming();

    type_128 *elem = ([&]() {
      auto it = data.find(key);
      if (it != data.end()) {
        return &it->second;
      }
      return static_cast<type_128 *>(nullptr);
    })();

    benchmark::DoNotOptimize(elem);
    benchmark::ClobberMemory();
  }
}

BENCHMARK(bench_map_128_find)->Arg(2 << 4)->Arg(2 << 8)->Arg(2 << 12);

static void bench_unordered_map_128_find(benchmark::State &state) {

  size_t count = static_cast<size_t>(state.range(0));

  std::unordered_map<std::string, type_128> data;

  for (size_t i = 0; i < count; ++i) {
    data.insert(std::make_pair(gen_string(), type_128()));
  }

  benchmark::DoNotOptimize(data);

  for (auto _ : state) {

    state.PauseTiming();
    std::string key = gen_string();
    state.ResumeTiming();

    type_128 *elem = ([&]() {
      auto it = data.find(key);
      if (it != data.end()) {
        return &it->second;
      }
      return static_cast<type_128 *>(nullptr);
    })();

    benchmark::DoNotOptimize(elem);
    benchmark::ClobberMemory();
  }
}

BENCHMARK(bench_unordered_map_128_find)->Arg(2 << 4)->Arg(2 << 8)->Arg(2 << 12);

static void bench_vector_256_find(benchmark::State &state) {

  size_t count = static_cast<size_t>(state.range(0));

  std::vector<std::pair<std::string, type_256>> data;
  data.reserve(count);

  for (size_t i = 0; i < count; ++i) {
    data.push_back(std::make_pair(gen_string(), type_256()));
  }

  benchmark::DoNotOptimize(data.data());

  for (auto _ : state) {

    state.PauseTiming();
    std::string key = gen_string();
    state.ResumeTiming();

    type_256 *elem = ([&]() {
      for (auto &e : data) {
        if (e.first == key) {
          return &e.second;
        }
      }
      return static_cast<type_256 *>(nullptr);
    })();

    benchmark::DoNotOptimize(elem);
    benchmark::ClobberMemory();
  }
}

BENCHMARK(bench_vector_256_find)->Arg(2 << 4)->Arg(2 << 8)->Arg(2 << 12);

static void bench_vector_256_find2(benchmark::State &state) {

  size_t count = static_cast<size_t>(state.range(0));

  std::vector<std::pair<std::string, type_256>> data;
  data.reserve(count);

  for (size_t i = 0; i < count; ++i) {
    data.push_back(std::make_pair(gen_string(), type_256()));
  }

  benchmark::DoNotOptimize(data.data());

  for (auto _ : state) {

    state.PauseTiming();
    std::string key = gen_string();
    state.ResumeTiming();

    type_256 *elem = ([&]() {
      for (auto &e : data) {
        if (UNLIKLY(e.first == key)) {
          return &e.second;
        }
      }
      return static_cast<type_256 *>(nullptr);
    })();

    benchmark::DoNotOptimize(elem);
    benchmark::ClobberMemory();
  }
}

BENCHMARK(bench_vector_256_find2)->Arg(2 << 4)->Arg(2 << 8)->Arg(2 << 12);

static void bench_map_256_find(benchmark::State &state) {

  size_t count = static_cast<size_t>(state.range(0));

  std::map<std::string, type_256> data;

  for (size_t i = 0; i < count; ++i) {
    data.insert(std::make_pair(gen_string(), type_256()));
  }

  benchmark::DoNotOptimize(data);

  for (auto _ : state) {

    state.PauseTiming();
    std::string key = gen_string();
    state.ResumeTiming();

    type_256 *elem = ([&]() {
      auto it = data.find(key);
      if (it != data.end()) {
        return &it->second;
      }
      return static_cast<type_256 *>(nullptr);
    })();

    benchmark::DoNotOptimize(elem);
    benchmark::ClobberMemory();
  }
}

BENCHMARK(bench_map_256_find)->Arg(2 << 4)->Arg(2 << 8)->Arg(2 << 12);

static void bench_unordered_map_256_find(benchmark::State &state) {

  size_t count = static_cast<size_t>(state.range(0));

  std::unordered_map<std::string, type_256> data;

  for (size_t i = 0; i < count; ++i) {
    data.insert(std::make_pair(gen_string(), type_256()));
  }

  benchmark::DoNotOptimize(data);

  for (auto _ : state) {

    state.PauseTiming();
    std::string key = gen_string();
    state.ResumeTiming();

    type_256 *elem = ([&]() {
      auto it = data.find(key);
      if (it != data.end()) {
        return &it->second;
      }
      return static_cast<type_256 *>(nullptr);
    })();

    benchmark::DoNotOptimize(elem);
    benchmark::ClobberMemory();
  }
}

BENCHMARK(bench_unordered_map_256_find)->Arg(2 << 4)->Arg(2 << 8)->Arg(2 << 12);

static void bench_vector_256_find_indexed(benchmark::State &state) {

  size_t count = static_cast<size_t>(state.range(0));

  std::vector<std::pair<std::string, type_256>> data;
  std::vector<size_t> index_table;

  data.reserve(count);
  index_table.reserve(count);

  for (size_t i = 0; i < count; ++i) {

    std::string key = gen_string();
    size_t key_hash = std::hash<std::string>()(key);

    auto hit =
        std::lower_bound(index_table.begin(), index_table.end(), key_hash);
    index_table.insert(hit, key_hash);

    size_t dist = static_cast<size_t>(std::distance(index_table.begin(), hit));

    auto eit = data.begin();
    std::advance(eit, dist);

    data.insert(eit, std::make_pair(key, type_256()));
  }

  benchmark::DoNotOptimize(data.data());

  for (auto _ : state) {

    state.PauseTiming();
    std::string key = gen_string();
    state.ResumeTiming();

    type_256 *elem = ([&]() {
      size_t key_hash = std::hash<std::string>()(key);
      auto hit =
          std::lower_bound(index_table.begin(), index_table.end(), key_hash);
      if (hit != index_table.end()) {
        size_t dist =
            static_cast<size_t>(std::distance(index_table.begin(), hit));
        return &data[dist].second;
      }
      return static_cast<type_256 *>(nullptr);
    })();

    benchmark::DoNotOptimize(elem);
    benchmark::ClobberMemory();
  }
}

BENCHMARK(bench_vector_256_find_indexed)
    ->Arg(2 << 4)
    ->Arg(2 << 8)
    ->Arg(2 << 12);

static void bench_vector_256_find_indexed2(benchmark::State &state) {

  size_t count = static_cast<size_t>(state.range(0));

  std::vector<std::pair<std::string, type_256>> data;
  std::vector<size_t> index_table;

  data.reserve(count);
  index_table.reserve(count);

  for (size_t i = 0; i < count; ++i) {

    std::string key = gen_string();
    size_t key_hash = std::hash<std::string>()(key);

    auto hit =
        std::lower_bound(index_table.begin(), index_table.end(), key_hash);
    index_table.insert(hit, key_hash);

    size_t dist = static_cast<size_t>(std::distance(index_table.begin(), hit));

    auto eit = data.begin();
    std::advance(eit, dist);

    data.insert(eit, std::make_pair(key, type_256()));
  }

  benchmark::DoNotOptimize(data.data());

  for (auto _ : state) {

    state.PauseTiming();
    std::string key = gen_string();
    state.ResumeTiming();

    type_256 *elem = ([&]() {
      size_t key_hash = std::hash<std::string>()(key);

      for (size_t i = 0, s = index_table.size(); i < s; ++i) {
        if (UNLIKLY(index_table[i] == key_hash)) {
          return &data[i].second;
        }
      }
      return static_cast<type_256 *>(nullptr);
    })();

    benchmark::DoNotOptimize(elem);
    benchmark::ClobberMemory();
  }
}

BENCHMARK(bench_vector_256_find_indexed2)
    ->Arg(2 << 4)
    ->Arg(2 << 8)
    ->Arg(2 << 12);

BENCHMARK_MAIN();
