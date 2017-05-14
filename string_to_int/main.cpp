#include <benchmark/benchmark.h>
#include <cstdlib>
#include <random>

class string_data_fixture : public ::benchmark::Fixture {
public:
  static int gen_range(int val) {
    int r = 1;
    for (int i = 0; i < val; i++)
      r *= 10;
    return r;
  }

  void SetUp(const ::benchmark::State &st) {
    int size = st.range(0);
    int length = st.range(1);
    strings = std::vector<std::string>();
    strings.reserve(static_cast<size_t>(size));

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(gen_range(length),
                                        gen_range(length + 1) - 1);
    for (int i = 0; i < size; i++) {
      int val = dis(gen);
      char buff[32]{0};
      int l = snprintf(buff, 32, "%d", val);
      strings.push_back(std::string(buff, static_cast<size_t>(l)));
    }
  }

  void TearDown(const ::benchmark::State &) { strings.clear(); }
  std::vector<std::string> strings;
};

constexpr int string_set_size{500};

BENCHMARK_DEFINE_F(string_data_fixture, std_atoi)(benchmark::State &state) {
  while (state.KeepRunning()) {

    for (const auto &str : strings) {
      int val = atoi(str.c_str());
      benchmark::DoNotOptimize(&val);
    }
  }
}

BENCHMARK_REGISTER_F(string_data_fixture, std_atoi)->Args({string_set_size, 2});
BENCHMARK_REGISTER_F(string_data_fixture, std_atoi)->Args({string_set_size, 3});
BENCHMARK_REGISTER_F(string_data_fixture, std_atoi)->Args({string_set_size, 4});
BENCHMARK_REGISTER_F(string_data_fixture, std_atoi)->Args({string_set_size, 5});
BENCHMARK_REGISTER_F(string_data_fixture, std_atoi)->Args({string_set_size, 6});
BENCHMARK_REGISTER_F(string_data_fixture, std_atoi)->Args({string_set_size, 7});
BENCHMARK_REGISTER_F(string_data_fixture, std_atoi)->Args({string_set_size, 8});
BENCHMARK_REGISTER_F(string_data_fixture, std_atoi)->Args({string_set_size, 9});

/**
 * http://www.geeksforgeeks.org/write-your-own-atoi/
 **/
// A utility function to check whether x is numeric
bool is_num(char x) { return (x >= '0' && x <= '9') ? true : false; }

// A simple atoi() function. If the given string contains
// any invalid character, then this function returns 0
int atoi_opt_1(const char *str) {
  if (str == nullptr)
    return 0;

  int res = 0;  // Initialize result
  int sign = 1; // Initialize sign as positive
  int i = 0;    // Initialize index of first digit

  // If number is negative, then update sign
  if (str[0] == '-') {
    sign = -1;
    i++; // Also update index of first digit
  }

  // Iterate through all digits of input string and update result
  for (; str[i] != '\0'; ++i) {
    if (is_num(str[i]) == false)
      return 0; // You may add some lines to write error message
                // to error stream
    res = res * 10 + str[i] - '0';
  }

  // Return result with sign
  return sign * res;
}

BENCHMARK_DEFINE_F(string_data_fixture, atoi_opt_1)(benchmark::State &state) {
  while (state.KeepRunning()) {

    for (const auto &str : strings) {
      int val = atoi_opt_1(str.c_str());
      benchmark::DoNotOptimize(&val);
    }
  }
}

BENCHMARK_REGISTER_F(string_data_fixture, atoi_opt_1)
    ->Args({string_set_size, 2});
BENCHMARK_REGISTER_F(string_data_fixture, atoi_opt_1)
    ->Args({string_set_size, 3});
BENCHMARK_REGISTER_F(string_data_fixture, atoi_opt_1)
    ->Args({string_set_size, 4});
BENCHMARK_REGISTER_F(string_data_fixture, atoi_opt_1)
    ->Args({string_set_size, 5});
BENCHMARK_REGISTER_F(string_data_fixture, atoi_opt_1)
    ->Args({string_set_size, 6});
BENCHMARK_REGISTER_F(string_data_fixture, atoi_opt_1)
    ->Args({string_set_size, 7});
BENCHMARK_REGISTER_F(string_data_fixture, atoi_opt_1)
    ->Args({string_set_size, 8});
BENCHMARK_REGISTER_F(string_data_fixture, atoi_opt_1)
    ->Args({string_set_size, 9});

/**
 * Attempt to remove additional function call and invert the test branch from
 * false first to true first
 */
int atoi_opt_2(const char *str) {
  if (str == nullptr)
    return 0;

  int res = 0;  // Initialize result
  int sign = 1; // Initialize sign as positive
  int i = 0;    // Initialize index of first digit

  // If number is negative, then update sign
  if (str[0] == '-') {
    sign = -1;
    ++i; // Also update index of first digit
  }

  // Iterate through all digits of input string and update result
  for (; str[i] != '\0'; ++i) {
    if (str[i] >= '0' && str[i] <= '9')
      res = res * 10 + str[i] - '0';
    else
      return 0; // You may add some lines to write error message
                // to error stream
  }

  // Return result with sign
  return sign * res;
}

BENCHMARK_DEFINE_F(string_data_fixture, atoi_opt_2)(benchmark::State &state) {
  while (state.KeepRunning()) {

    for (const auto &str : strings) {
      int val = atoi_opt_2(str.c_str());
      benchmark::DoNotOptimize(&val);
    }
  }
}

BENCHMARK_REGISTER_F(string_data_fixture, atoi_opt_2)
    ->Args({string_set_size, 2});
BENCHMARK_REGISTER_F(string_data_fixture, atoi_opt_2)
    ->Args({string_set_size, 3});
BENCHMARK_REGISTER_F(string_data_fixture, atoi_opt_2)
    ->Args({string_set_size, 4});
BENCHMARK_REGISTER_F(string_data_fixture, atoi_opt_2)
    ->Args({string_set_size, 5});
BENCHMARK_REGISTER_F(string_data_fixture, atoi_opt_2)
    ->Args({string_set_size, 6});
BENCHMARK_REGISTER_F(string_data_fixture, atoi_opt_2)
    ->Args({string_set_size, 7});
BENCHMARK_REGISTER_F(string_data_fixture, atoi_opt_2)
    ->Args({string_set_size, 8});
BENCHMARK_REGISTER_F(string_data_fixture, atoi_opt_2)
    ->Args({string_set_size, 9});

/**
 * Compute the value using unsiged modulus behaviour before the comparison to
 * avoid performing multiple operations
**/

int atoi_opt_3(const char *str) {
  if (str == nullptr)
    return 0;

  int res = 0;  // Initialize result
  int sign = 1; // Initialize sign as positive
  int i = 0;    // Initialize index of first digit

  // If number is negative, then update sign
  if (str[0] == '-') {
    sign = -1;
    ++i; // Also update index of first digit
  }

  // Iterate through all digits of input string and update result
  for (; str[i] != '\0'; ++i) {
    unsigned c = static_cast<unsigned>(str[i] - '0');
    if (c <= 9)
      res = res * 10 + static_cast<int>(c);
    else
      return 0; // You may add some lines to write error message
                // to error stream
  }

  // Return result with sign
  return sign * res;
}

BENCHMARK_DEFINE_F(string_data_fixture, atoi_opt_3)(benchmark::State &state) {
  while (state.KeepRunning()) {

    for (const auto &str : strings) {
      int val = atoi_opt_3(str.c_str());
      benchmark::DoNotOptimize(&val);
    }
  }
}

BENCHMARK_REGISTER_F(string_data_fixture, atoi_opt_3)
    ->Args({string_set_size, 2});
BENCHMARK_REGISTER_F(string_data_fixture, atoi_opt_3)
    ->Args({string_set_size, 3});
BENCHMARK_REGISTER_F(string_data_fixture, atoi_opt_3)
    ->Args({string_set_size, 4});
BENCHMARK_REGISTER_F(string_data_fixture, atoi_opt_3)
    ->Args({string_set_size, 5});
BENCHMARK_REGISTER_F(string_data_fixture, atoi_opt_3)
    ->Args({string_set_size, 6});
BENCHMARK_REGISTER_F(string_data_fixture, atoi_opt_3)
    ->Args({string_set_size, 7});
BENCHMARK_REGISTER_F(string_data_fixture, atoi_opt_3)
    ->Args({string_set_size, 8});
BENCHMARK_REGISTER_F(string_data_fixture, atoi_opt_3)
    ->Args({string_set_size, 9});

BENCHMARK_MAIN();
