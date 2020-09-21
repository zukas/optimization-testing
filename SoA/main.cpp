#include <benchmark/benchmark.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <vector>

#include <immintrin.h>
#include <memory>

struct obj {
  glm::vec3 velocity;
  glm::vec3 position;
  glm::quat rotation;
  float scale;
  glm::mat4 model;
  std::array<glm::mat4, 5> bones;
  uint32_t voa;
  uint32_t colour;
  uint32_t shadow;
  uint32_t bummap;
};

struct soa_obj {
  glm::mat4 *models;
  glm::vec4 *positions;
  glm::vec4 *velocities;
  glm::quat *rotations;
  glm::mat4 *bones;
  float *scales;
  uint32_t *colours;
  uint32_t *shadows;
  uint32_t *bummaps;
  uint32_t *voas;
};

template <size_t S> class SOA {

  template <typename T> struct aligned_deleter {
    void operator()(T *ptr) { free(ptr); }
  };

  template <typename T>
  using aligned_ptr = std::unique_ptr<T, aligned_deleter<T>>;

  template <typename T, size_t alignment>
  static aligned_ptr<T> make_aligned_ptr() {

    return {static_cast<T *>(aligned_alloc(alignment, sizeof(T) * S)),
            aligned_deleter<T>()};
  }

public:
  class iterator {

  public:
    iterator(SOA<S> &b, int32_t idx) : base(&b), idx(idx) {}

    friend bool operator==(const iterator &lhs, const iterator &rhs) {
      return lhs.idx == rhs.idx;
    }

    friend bool operator!=(const iterator &lhs, const iterator &rhs) {
      return lhs.idx != rhs.idx;
    }

    iterator &operator++() {
      idx++;
      return *this;
    }

    uint32_t &voa() { return base->voas.get()[idx]; }
    glm::mat4 &model() { return base->models.get()[idx]; }
    glm::vec4 &position() { return base->positions.get()[idx]; }
    glm::vec4 &velocitie() { return base->velocities.get()[idx]; }
    glm::quat &rotation() { return base->rotations.get()[idx]; }
    float &scale() { return base->scales.get()[idx]; }
    uint32_t &colour() { return base->colours.get()[idx]; }
    uint32_t &shadow() { return base->shadows.get()[idx]; }
    uint32_t &bummap() { return base->bummaps.get()[idx]; }
    std::array<glm::mat4, 5> &bones() { return base->boness.get()[idx]; }

    iterator &operator*() { return *this; }

  private:
    SOA<S> *base;
    int32_t idx;
  };

  class const_iterator {

  public:
    const_iterator(const SOA<S> &b, int32_t idx) : base(&b), idx(idx) {}

    friend bool operator==(const const_iterator &lhs,
                           const const_iterator &rhs) {
      return lhs.idx == rhs.idx;
    }

    friend bool operator!=(const const_iterator &lhs,
                           const const_iterator &rhs) {
      return lhs.idx != rhs.idx;
    }

    const_iterator &operator++() {
      idx++;
      return *this;
    }

    const uint32_t &voa() const { return base->voas[idx]; }
    const glm::mat4 &model() const { return base->models[idx]; }
    const glm::vec3 &position() const { return base->positions[idx]; }
    const glm::vec3 &velocitie() const { return base->velocities[idx]; }
    const glm::quat &rotation() const { return base->rotations[idx]; }
    const float &scale() const { return base->scales[idx]; }
    const uint32_t &colour() const { return base->colours[idx]; }
    const uint32_t &shadow() const { return base->shadows[idx]; }
    const uint32_t &bummap() const { return base->bummaps[idx]; }
    const std::array<glm::mat4, 5> &bones() const { return base->boness[idx]; }

    const const_iterator &operator*() const { return *this; }

  private:
    const SOA<S> *base;
    int32_t idx;
  };

  SOA()
      : voas(make_aligned_ptr<uint32_t, 4>()),
        models(make_aligned_ptr<glm::mat4, 64>()),
        positions(make_aligned_ptr<glm::vec4, 64>()),
        velocities(make_aligned_ptr<glm::vec4, 64>()),
        rotations(make_aligned_ptr<glm::quat, 64>()),
        scales(make_aligned_ptr<float, 64>()),
        colours(make_aligned_ptr<uint32_t, 4>()),
        shadows(make_aligned_ptr<uint32_t, 4>()),
        bummaps(make_aligned_ptr<uint32_t, 4>()),
        boness(make_aligned_ptr<std::array<glm::mat4, 5>, 64>()) {}

  iterator begin() { return iterator(*this, 0); }
  iterator end() { return iterator(*this, S); }

  const_iterator cbegin() { return const_iterator(*this, 0); }
  const_iterator cend() { return const_iterator(*this, S); }

  uint32_t *get_voas() { return voas.get(); }
  glm::mat4 *get_models() { return models.get(); }
  glm::vec4 *get_positions() { return positions.get(); }
  glm::vec4 *get_velocities() { return velocities.get(); }
  glm::quat *get_rotations() { return rotations.get(); }
  float *get_scales() { return scales.get(); }
  uint32_t *get_colours() { return colours.get(); }
  uint32_t *get_shadows() { return shadows.get(); }
  uint32_t *get_bummaps() { return bummaps.get(); }
  std::array<glm::mat4, 5> *get_boness() { return boness.get(); }

private:
  aligned_ptr<uint32_t> voas;
  aligned_ptr<glm::mat4> models;
  aligned_ptr<glm::vec4> positions;
  aligned_ptr<glm::vec4> velocities;
  aligned_ptr<glm::quat> rotations;
  aligned_ptr<float> scales;
  aligned_ptr<uint32_t> colours;
  aligned_ptr<uint32_t> shadows;
  aligned_ptr<uint32_t> bummaps;
  aligned_ptr<std::array<glm::mat4, 5>> boness;
};

void __attribute__((noinline)) render(uint32_t voa) {
  benchmark::DoNotOptimize(voa);
}

void __attribute__((noinline)) upload(uint32_t uniform) {
  benchmark::DoNotOptimize(uniform);
}

void __attribute__((noinline)) upload(const glm::vec3 &uniform) {
  benchmark::DoNotOptimize(uniform);
}

void __attribute__((noinline)) upload(const glm::quat &uniform) {
  benchmark::DoNotOptimize(uniform);
}

void __attribute__((noinline)) upload(const glm::vec4 &uniform) {
  benchmark::DoNotOptimize(uniform);
}

void __attribute__((noinline)) upload(const glm::mat4 &uniform) {
  benchmark::DoNotOptimize(uniform);
}

void __attribute__((noinline)) upload(const glm::mat4 *uniforms, int32_t size) {
  benchmark::DoNotOptimize(uniforms);
  benchmark::DoNotOptimize(size);
}

template <uint32_t S> static void aos(benchmark::State &state) {

  std::vector<obj> a(S);
  for (auto _ : state) {

    for (auto &e : a) {
      e.position += e.velocity;
    }

    for (auto &e : a) {
      glm::mat4 &model = e.model;
      const glm::vec3 &pos = e.position;
      const glm::mat4 &rotation = glm::toMat4(e.rotation);
      const float scale = e.scale;
      model = rotation * glm::translate(glm::mat4(scale), pos);
      upload(model);
    }

    for (auto &e : a) {
      glm::mat4 *bones = e.bones.data();
      const glm::mat4 &model = e.model;
      const float time = float(state.iterations());
      bones[0] = model * time;
      upload(bones, 5);
    }
    benchmark::ClobberMemory();
  }
}

template <uint32_t S> static void soa(benchmark::State &state) {

  soa_obj a{
      static_cast<glm::mat4 *>(aligned_alloc(64, sizeof(glm::mat4) * S)),
      static_cast<glm::vec4 *>(aligned_alloc(64, sizeof(glm::vec4) * S)),
      static_cast<glm::vec4 *>(aligned_alloc(64, sizeof(glm::vec4) * S)),
      static_cast<glm::quat *>(aligned_alloc(64, sizeof(glm::quat) * S)),
      static_cast<glm::mat4 *>(aligned_alloc(64, sizeof(glm::mat4) * S * 5)),
      static_cast<float *>(aligned_alloc(64, sizeof(float) * S)),
      static_cast<uint32_t *>(aligned_alloc(4, sizeof(uint32_t) * S)),
      static_cast<uint32_t *>(aligned_alloc(4, sizeof(uint32_t) * S)),
      static_cast<uint32_t *>(aligned_alloc(4, sizeof(uint32_t) * S)),
      static_cast<uint32_t *>(aligned_alloc(4, sizeof(uint32_t) * S))};

  constexpr int32_t size{S};

  for (auto _ : state) {

    for (int32_t i = 0; i < size / 8; i += 8) {
      _mm256_store_ps(&(a.positions[i][0]),
                      _mm256_add_ps(_mm256_load_ps(&(a.positions[i][0])),
                                    _mm256_load_ps(&(a.velocities[i][0]))));
      _mm256_store_ps(&(a.positions[i + 2][0]),
                      _mm256_add_ps(_mm256_load_ps(&(a.positions[i + 2][0])),
                                    _mm256_load_ps(&(a.velocities[i + 2][0]))));
      _mm256_store_ps(&(a.positions[i + 4][0]),
                      _mm256_add_ps(_mm256_load_ps(&(a.positions[i + 4][0])),
                                    _mm256_load_ps(&(a.velocities[i + 4][0]))));

      _mm256_store_ps(&(a.positions[i + 6][0]),
                      _mm256_add_ps(_mm256_load_ps(&(a.positions[i + 6][0])),
                                    _mm256_load_ps(&(a.velocities[i + 6][0]))));

      //      a.positions[i] += a.velocities[i];
    }

    for (int32_t i = 0; i < size; ++i) {
      glm::mat4 &model = a.models[i];
      const glm::vec3 &position = a.positions[i];
      const glm::mat4 &rotation = glm::toMat4(a.rotations[i]);
      const float scale = a.scales[i];
      model = rotation * glm::translate(glm::mat4(scale), position);
    }

    upload(a.models, S);

    for (int32_t i = 0; i < size; ++i) {
      glm::mat4 *bones = &a.bones[i * 5];
      const glm::mat4 &model = a.models[i];
      const float time = float(state.iterations());
      bones[0] = model * time;
    }

    upload(a.bones, S * 5);

    benchmark::ClobberMemory();
  }

  free(a.bones);
  a.bones = nullptr;
  free(a.bummaps);
  a.bummaps = nullptr;
  free(a.shadows);
  a.shadows = nullptr;
  free(a.colours);
  a.colours = nullptr;
  free(a.scales);
  a.scales = nullptr;
  free(a.rotations);
  a.rotations = nullptr;
  free(a.velocities);
  a.velocities = nullptr;
  free(a.positions);
  a.positions = nullptr;
  free(a.models);
  a.models = nullptr;
  free(a.voas);
  a.voas = nullptr;
}

template <uint32_t S> static void aos2(benchmark::State &state) {

  std::vector<obj> a(S);
  for (auto _ : state) {

    for (auto &e : a) {
      e.position += e.velocity;

      glm::mat4 &model = e.model;
      const glm::vec3 &pos = e.position;
      const glm::mat4 &rotation = glm::toMat4(e.rotation);
      const float scale = e.scale;
      model = rotation * glm::translate(glm::mat4(scale), pos);
      upload(model);

      glm::mat4 *bones = e.bones.data();
      const float time = float(state.iterations());
      bones[0] = model * time;
      upload(bones, 5);
    }
    benchmark::ClobberMemory();
  }
}

template <uint32_t S> static void soa2(benchmark::State &state) {

  soa_obj a{
      static_cast<glm::mat4 *>(aligned_alloc(64, sizeof(glm::mat4) * S)),
      static_cast<glm::vec4 *>(aligned_alloc(64, sizeof(glm::vec4) * S)),
      static_cast<glm::vec4 *>(aligned_alloc(64, sizeof(glm::vec4) * S)),
      static_cast<glm::quat *>(aligned_alloc(64, sizeof(glm::quat) * S)),
      static_cast<glm::mat4 *>(aligned_alloc(64, sizeof(glm::mat4) * S * 5)),
      static_cast<float *>(aligned_alloc(64, sizeof(float) * S)),
      static_cast<uint32_t *>(aligned_alloc(4, sizeof(uint32_t) * S)),
      static_cast<uint32_t *>(aligned_alloc(4, sizeof(uint32_t) * S)),
      static_cast<uint32_t *>(aligned_alloc(4, sizeof(uint32_t) * S)),
      static_cast<uint32_t *>(aligned_alloc(4, sizeof(uint32_t) * S))};

  constexpr int32_t size{S};

  for (auto _ : state) {

    for (int32_t i = 0; i < size; ++i) {
      a.positions[i] += a.velocities[i];

      glm::mat4 &model = a.models[i];
      const glm::vec3 &position = a.positions[i];
      const glm::mat4 &rotation = glm::toMat4(a.rotations[i]);
      const float scale = a.scales[i];
      model = rotation * glm::translate(glm::mat4(scale), position);

      glm::mat4 *bones = &a.bones[i * 5];
      const float time = float(state.iterations());
      bones[0] = model * time;
    }

    upload(a.models, S);
    upload(a.bones, S * 5);

    benchmark::ClobberMemory();
  }

  free(a.bones);
  a.bones = nullptr;
  free(a.bummaps);
  a.bummaps = nullptr;
  free(a.shadows);
  a.shadows = nullptr;
  free(a.colours);
  a.colours = nullptr;
  free(a.scales);
  a.scales = nullptr;
  free(a.rotations);
  a.rotations = nullptr;
  free(a.velocities);
  a.velocities = nullptr;
  free(a.positions);
  a.positions = nullptr;
  free(a.models);
  a.models = nullptr;
  free(a.voas);
  a.voas = nullptr;
}

template <uint32_t S> static void soa3(benchmark::State &state) {

  SOA<S> soa;

  for (auto _ : state) {

    for (auto &a : soa) {
      a.position() += a.velocitie();
    }

    for (auto &a : soa) {
      glm::mat4 &model = a.model();
      const glm::vec3 &position = a.position();
      const glm::mat4 &rotation = glm::toMat4(a.rotation());
      const float scale = a.scale();
      model = rotation * glm::translate(glm::mat4(scale), position);
    }

    upload(soa.get_models(), S);

    for (auto &a : soa) {
      std::array<glm::mat4, 5> &b = a.bones();
      const glm::mat4 &model = a.model();
      const float time = float(state.iterations());
      b[0] = model * time;
    }

    upload(soa.get_boness()->data(), S * 5);

    benchmark::ClobberMemory();
  }
}

#define TEST(N)                                                                \
  BENCHMARK_TEMPLATE(aos, N)->Unit(benchmark::kMicrosecond);                   \
  BENCHMARK_TEMPLATE(aos2, N)->Unit(benchmark::kMicrosecond);                  \
  BENCHMARK_TEMPLATE(soa, N)->Unit(benchmark::kMicrosecond);                   \
  BENCHMARK_TEMPLATE(soa2, N)->Unit(benchmark::kMicrosecond);                  \
  BENCHMARK_TEMPLATE(soa3, N)->Unit(benchmark::kMicrosecond)

TEST(100);
TEST(1000);
TEST(10000);
TEST(100000);
TEST(1000000);

BENCHMARK_MAIN();
