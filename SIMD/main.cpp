
#include <map>
#include <random>
#include <vector>

#include <stdlib.h>

#include <benchmark/benchmark.h>

#include <immintrin.h>

// https://software.intel.com/sites/landingpage/IntrinsicsGuide/#techs=AVX

enum class Type { T1, T2, T3, TMAX };

class Obj {
public:
  Obj(Type type, float t1, float t2, float t3)
      : t(type), t1_val(t1), t2_val(t2), t3_val(t3), res_val(0) {}

  Type getType() const { return t; }

  float getT1Val() const { return t1_val; }

  float getT2Val() const { return t2_val; }

  float getT3Val() const { return t3_val; }

  float getResVal() const { return res_val; }

  void setResVal(float res) { res_val = res; }

private:
  Type t;
  float t1_val;
  float t2_val;
  float t3_val;
  float res_val;
};

class Scl {
public:
  Scl(float s1, float s2) : s1_val(s1), s2_val(s2) {}

  float getS1Val() const { return s1_val; }

  float getS2Val() const { return s2_val; }

private:
  float s1_val;
  float s2_val;
};

constexpr int size = 10000;

static void baseline(benchmark::State &state) {

  std::random_device rd;
  std::mt19937 gen(rd());

  std::uniform_real_distribution<float> float_dis(0.0, 100.0);

  std::uniform_int_distribution<int> int_dis(0, 11);

  Scl scl(float_dis(gen), float_dis(gen));

  std::vector<Obj> objs;
  objs.reserve(size);

  for (int i = 0; i < size; ++i) {
    objs.emplace_back(
        static_cast<Type>(int_dis(gen) % static_cast<int>(Type::TMAX)),
        float_dis(gen), float_dis(gen), float_dis(gen));
  }

  for (auto _ : state) {
    for (auto &obj : objs) {
      switch (obj.getType()) {
      case Type::T1: {

        float res = obj.getT1Val() * scl.getS1Val();
        obj.setResVal(res);
        break;
      }
      case Type::T2: {
        float res = obj.getT2Val() * scl.getS2Val();
        obj.setResVal(res);
        break;
      }
      case Type::T3: {
        float res = obj.getT3Val() / scl.getS2Val();
        obj.setResVal(res);

        break;
      }
      default:
        break;
      }
    }
    benchmark::DoNotOptimize(objs.data());
    benchmark::ClobberMemory();
  }
}

BENCHMARK(baseline);

static void parallel_base(benchmark::State &state) {

  std::random_device rd;
  std::mt19937 gen(rd());

  std::uniform_real_distribution<float> float_dis(0.0, 100.0);

  std::uniform_int_distribution<int> int_dis(0, 11);

  Scl scl(float_dis(gen), float_dis(gen));

  std::map<Type, std::vector<float>> objs;

  for (int i = 0; i < size; ++i) {
    Type t = static_cast<Type>(int_dis(gen) % static_cast<int>(Type::TMAX));
    objs[t].push_back(float_dis(gen));
  }

  std::map<Type, std::vector<float>> res;
  res[Type::T1].resize(objs[Type::T1].size());
  res[Type::T2].resize(objs[Type::T2].size());
  res[Type::T3].resize(objs[Type::T3].size());

  for (auto _ : state) {

    {
      const std::vector<float> &o1 = objs[Type::T1];
      std::vector<float> &r1 = res[Type::T1];
      for (int i = 0, s = o1.size(); i < s; ++i) {
        float val = o1[i] * scl.getS1Val();
        r1[i] = val;
      }
      benchmark::DoNotOptimize(r1.data());
    }
    {
      const std::vector<float> &o2 = objs[Type::T2];
      std::vector<float> &r2 = res[Type::T2];
      for (int i = 0, s = o2.size(); i < s; ++i) {
        float val = o2[i] * scl.getS2Val();
        r2[i] = val;
      }
      benchmark::DoNotOptimize(r2.data());
    }

    {
      const std::vector<float> &o3 = objs[Type::T3];
      std::vector<float> &r3 = res[Type::T3];
      for (int i = 0, s = o3.size(); i < s; ++i) {
        float val = o3[i] / scl.getS2Val();
        r3[i] = val;
      }
      benchmark::DoNotOptimize(r3.data());
    }

    benchmark::ClobberMemory();
  }
}

BENCHMARK(parallel_base);

struct vector_data {
  float data[8];
};

static void parallel_intrinsics_base(benchmark::State &state) {

  std::random_device rd;
  std::mt19937 gen(rd());

  std::uniform_real_distribution<float> float_dis(0.0, 100.0);

  std::uniform_int_distribution<int> int_dis(0, 11);

  Scl scl(float_dis(gen), float_dis(gen));

  std::map<Type, std::vector<vector_data>> objs;

  for (int i = 0, s = size / 8 + 1; i < s; ++i) {
    Type t = static_cast<Type>(int_dis(gen) % static_cast<int>(Type::TMAX));
    objs[t].push_back({float_dis(gen), float_dis(gen), float_dis(gen),
                       float_dis(gen), float_dis(gen), float_dis(gen),
                       float_dis(gen), float_dis(gen)});
  }

  std::map<Type, std::vector<vector_data>> res;
  res[Type::T1].resize(objs[Type::T1].size());
  res[Type::T2].resize(objs[Type::T2].size());
  res[Type::T3].resize(objs[Type::T3].size());

  for (auto _ : state) {

    {
      const std::vector<vector_data> &o1 = objs[Type::T1];
      std::vector<vector_data> &r1 = res[Type::T1];
      for (int i = 0, sz = o1.size(); i < sz; ++i) {

        __m256 v = _mm256_loadu_ps(o1[i].data);
        __m256 s = _mm256_set1_ps(scl.getS1Val());
        __m256 r = _mm256_mul_ps(v, s);

        _mm256_storeu_ps(r1[i].data, r);
      }
      benchmark::DoNotOptimize(r1.data());
    }
    {
      const std::vector<vector_data> &o2 = objs[Type::T2];
      std::vector<vector_data> &r2 = res[Type::T2];
      for (int i = 0, sz = o2.size(); i < sz; ++i) {

        __m256 v = _mm256_loadu_ps(o2[i].data);
        __m256 s = _mm256_set1_ps(scl.getS2Val());
        __m256 r = _mm256_mul_ps(v, s);

        _mm256_storeu_ps(r2[i].data, r);
      }
      benchmark::DoNotOptimize(r2.data());
    }

    {
      const std::vector<vector_data> &o3 = objs[Type::T3];
      std::vector<vector_data> &r3 = res[Type::T3];
      for (int i = 0, sz = o3.size(); i < sz; ++i) {

        __m256 v = _mm256_loadu_ps(o3[i].data);
        __m256 s = _mm256_set1_ps(scl.getS2Val());
        __m256 r = _mm256_div_ps(v, s);

        _mm256_storeu_ps(r3[i].data, r);
      }
      benchmark::DoNotOptimize(r3.data());
    }

    benchmark::ClobberMemory();
  }
}

BENCHMARK(parallel_intrinsics_base);

static void parallel_intrinsics_aligned(benchmark::State &state) {

  std::random_device rd;
  std::mt19937 gen(rd());

  std::uniform_real_distribution<float> float_dis(0.0, 100.0);

  std::uniform_int_distribution<int> int_dis(0, 11);

  Scl scl(float_dis(gen), float_dis(gen));

  int t1_size = 0;
  int t2_size = 0;
  int t3_size = 0;

  for (int i = 0, s = size / 8 + 1; i < s; ++i) {
    Type t = static_cast<Type>(int_dis(gen) % static_cast<int>(Type::TMAX));
    switch (t) {
    case Type::T1:
      t1_size++;
      break;
    case Type::T2:
      t2_size++;
      break;
    case Type::T3:
      t3_size++;
      break;
    default:
      break;
    }
  }

  vector_data *t1_objs = static_cast<vector_data *>(
      aligned_alloc(32, sizeof(vector_data) * t1_size));

  vector_data *t2_objs = static_cast<vector_data *>(
      aligned_alloc(32, sizeof(vector_data) * t2_size));

  vector_data *t3_objs = static_cast<vector_data *>(
      aligned_alloc(32, sizeof(vector_data) * t3_size));

  vector_data *t1_res = static_cast<vector_data *>(
      aligned_alloc(32, sizeof(vector_data) * t1_size));

  vector_data *t2_res = static_cast<vector_data *>(
      aligned_alloc(32, sizeof(vector_data) * t2_size));

  vector_data *t3_res = static_cast<vector_data *>(
      aligned_alloc(32, sizeof(vector_data) * t3_size));

  for (int i = 0; i < t1_size; ++i) {
    t1_objs[i] = {float_dis(gen), float_dis(gen), float_dis(gen),
                  float_dis(gen), float_dis(gen), float_dis(gen),
                  float_dis(gen), float_dis(gen)};
  }

  for (int i = 0; i < t2_size; ++i) {
    t2_objs[i] = {float_dis(gen), float_dis(gen), float_dis(gen),
                  float_dis(gen), float_dis(gen), float_dis(gen),
                  float_dis(gen), float_dis(gen)};
  }

  for (int i = 0; i < t3_size; ++i) {
    t3_objs[i] = {float_dis(gen), float_dis(gen), float_dis(gen),
                  float_dis(gen), float_dis(gen), float_dis(gen),
                  float_dis(gen), float_dis(gen)};
  }

  __m256 s1 = _mm256_set1_ps(scl.getS1Val());
  __m256 s2 = _mm256_set1_ps(scl.getS2Val());

  for (auto _ : state) {

    {
      for (int i = 0; i < t1_size; ++i) {
        __m256 v = _mm256_load_ps(t1_objs[i].data);
        __m256 r = _mm256_mul_ps(v, s1);

        _mm256_store_ps(t1_res[i].data, r);
      }
      benchmark::DoNotOptimize(t1_res);
    }
    {
      for (int i = 0; i < t2_size; ++i) {
        __m256 v = _mm256_load_ps(t2_objs[i].data);
        __m256 r = _mm256_mul_ps(v, s2);

        _mm256_store_ps(t2_res[i].data, r);
      }
      benchmark::DoNotOptimize(t2_res);
    }

    {
      for (int i = 0; i < t3_size; ++i) {
        __m256 v = _mm256_load_ps(t3_objs[i].data);
        __m256 r = _mm256_div_ps(v, s2);

        _mm256_store_ps(t3_res[i].data, r);
      }
      benchmark::DoNotOptimize(t3_res);
    }

    benchmark::ClobberMemory();
  }

  free(t1_objs);
  free(t2_objs);
  free(t3_objs);
  free(t1_res);
  free(t2_res);
  free(t3_res);
}

BENCHMARK(parallel_intrinsics_aligned);

BENCHMARK_MAIN();
