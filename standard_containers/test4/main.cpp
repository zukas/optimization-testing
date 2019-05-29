#include <benchmark/benchmark.h>
#include <bits/stdc++.h>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <random>

#include "common/common_types.h"

#include "mapped_data.h"

constexpr uint64_t two_days{100};
constexpr uint64_t one_week{500};
constexpr uint64_t two_week{1000};
constexpr uint64_t one_month{2000};
constexpr uint64_t two_month{4000};

static void bench_mapped_data_quoting(benchmark::State &state) {

  const int64_t number_of_orders = state.range(0);
  const int64_t number_of_makers = state.range(1);

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> lex_dis('A', 'Z');
  std::uniform_int_distribution<> uuid_dis(-999999 * 2, 999999);
  std::uniform_int_distribution<> inst_dis(instrument::SPOT, instrument::SWAP);
  std::uniform_int_distribution<> value_date_dis(-4, 4);
  std::uniform_real_distribution<double> amount_dis(50, 1500000000);

  uint64_t valueDates[]{two_days, one_week, two_week, one_month, two_month};

  mapped_data manager;

  struct quote_data {
    std::string currencyPair;
    uint64_t valueDate;
    instrument inst;
    double amount;
    struct dealcode dealcode;
    int uuid;
  };

  const size_t total_size =
      static_cast<size_t>(number_of_orders * number_of_makers);
  std::vector<quote_data> quotes(total_size);

  for (int64_t i = 0; i < number_of_orders; ++i) {

    int order_id = static_cast<int>(i) + 1;
    std::string currecy_pair;
    currecy_pair.resize(6);
    for (size_t j = 0; j < 6; ++j) {
      currecy_pair[j] = static_cast<char>(lex_dis(gen));
    }
    instrument inst = static_cast<instrument>(inst_dis(gen));
    uint64_t value_date = valueDates[std::max(value_date_dis(gen), 0)];
    double amount = amount_dis(gen);

    manager.addOrder(order(order_id, currecy_pair, inst, value_date, amount));

    for (int64_t n = i * number_of_makers, j = n; j < n + number_of_makers;
         ++j) {
      size_t idx = static_cast<size_t>(j);
      quotes[idx].currencyPair = currecy_pair;
      quotes[idx].valueDate = value_date;
      quotes[idx].inst = inst;
      quotes[idx].amount = amount;
    }
  }

  for (int64_t i = 0; i < number_of_makers; ++i) {
    dealcode dealcode;
    for (size_t j = 0; j < 4; ++j) {
      dealcode.data[j] = static_cast<char>(lex_dis(gen));
    }
    int uuid = std::max(uuid_dis(gen), 0);
    manager.addSubscription(maker(dealcode, uuid));

    for (size_t j = static_cast<size_t>(i); j < total_size;
         j += static_cast<size_t>(number_of_makers)) {
      quotes[j].dealcode = dealcode;
      quotes[j].uuid = uuid;
    }
  }
  std::mt19937 shuffle_gen(rd());
  std::shuffle(quotes.begin(), quotes.end(), shuffle_gen);

  benchmark::DoNotOptimize(quotes.data());
  benchmark::ClobberMemory();

  std::uniform_int_distribution<size_t> selector(0, quotes.size() - 1);
  std::uniform_real_distribution<double> scaler_dis(1.25, 2.50);
  for (auto _ : state) {
    for (int64_t i = 0; i < number_of_makers; ++i) {
      state.PauseTiming();
      const size_t idx = selector(gen);
      const quote_data &data = quotes[idx];
      const double price = data.amount * scaler_dis(gen);
      state.ResumeTiming();

      quote q(data.currencyPair, data.valueDate, data.inst, price,
              data.dealcode, data.uuid);
      benchmark::DoNotOptimize(q);
      manager.handleQuote(q);
    }
  }

  benchmark::ClobberMemory();
}

BENCHMARK(bench_mapped_data_quoting)
    // base
    ->ArgPair(5, 5)
    ->ArgPair(10, 5)
    ->ArgPair(20, 5)
    ->ArgPair(40, 5)
    ->ArgPair(80, 5)
    // step1
    ->ArgPair(5, 10)
    ->ArgPair(5, 20)
    ->ArgPair(5, 30)
    ->ArgPair(5, 40)
    ->ArgPair(5, 50)
    // step2
    ->ArgPair(10, 10)
    ->ArgPair(10, 20)
    ->ArgPair(10, 30)
    ->ArgPair(10, 40)
    ->ArgPair(10, 50)
    // step3
    ->ArgPair(20, 10)
    ->ArgPair(20, 20)
    ->ArgPair(20, 30)
    ->ArgPair(20, 40)
    ->ArgPair(20, 50)
    // step4
    ->ArgPair(40, 10)
    ->ArgPair(40, 20)
    ->ArgPair(40, 30)
    ->ArgPair(40, 40)
    ->ArgPair(40, 50)
    // step5
    ->ArgPair(80, 10)
    ->ArgPair(80, 20)
    ->ArgPair(80, 30)
    ->ArgPair(80, 40)
    ->ArgPair(80, 50)
    // mass
    ->ArgPair(5000, 50)
    ->ArgPair(5000, 100)
    ->ArgPair(5000, 150)
    ->ArgPair(5000, 200);

static void bench_mapped_data_quoting_and_trading(benchmark::State &state) {

  const int64_t number_of_orders = state.range(0);
  const int64_t number_of_makers = state.range(1);

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> lex_dis('A', 'Z');
  std::uniform_int_distribution<> uuid_dis(-999999 * 2, 999999);
  std::uniform_int_distribution<> inst_dis(instrument::SPOT, instrument::SWAP);
  std::uniform_int_distribution<> value_date_dis(-4, 4);
  std::uniform_real_distribution<double> amount_dis(50, 1500000000);

  uint64_t valueDates[]{two_days, one_week, two_week, one_month, two_month};

  mapped_data manager;

  struct quote_data {
    std::string currencyPair;
    uint64_t valueDate;
    instrument inst;
    double amount;
    struct dealcode dealcode;
    int uuid;
  };

  const size_t total_size =
      static_cast<size_t>(number_of_orders * number_of_makers);
  std::vector<quote_data> quotes(total_size);

  for (int64_t i = 0; i < number_of_orders; ++i) {

    int order_id = static_cast<int>(i) + 1;
    std::string currecy_pair;
    currecy_pair.resize(6);
    for (size_t j = 0; j < 6; ++j) {
      currecy_pair[j] = static_cast<char>(lex_dis(gen));
    }
    instrument inst = static_cast<instrument>(inst_dis(gen));
    uint64_t value_date = valueDates[std::max(value_date_dis(gen), 0)];
    double amount = amount_dis(gen);

    manager.addOrder(order(order_id, currecy_pair, inst, value_date, amount));

    for (int64_t n = i * number_of_makers, j = n; j < n + number_of_makers;
         ++j) {
      size_t idx = static_cast<size_t>(j);
      quotes[idx].currencyPair = currecy_pair;
      quotes[idx].valueDate = value_date;
      quotes[idx].inst = inst;
      quotes[idx].amount = amount;
    }
  }

  for (int64_t i = 0; i < number_of_makers; ++i) {
    struct dealcode dealcode;
    for (size_t j = 0; j < 4; ++j) {
      dealcode.data[j] = static_cast<char>(lex_dis(gen));
    }
    int uuid = std::max(uuid_dis(gen), 0);
    manager.addSubscription(maker(dealcode, uuid));

    for (size_t j = static_cast<size_t>(i); j < total_size;
         j += static_cast<size_t>(number_of_makers)) {
      quotes[j].dealcode = dealcode;
      quotes[j].uuid = uuid;
    }
  }
  std::mt19937 shuffle_gen(rd());
  std::shuffle(quotes.begin(), quotes.end(), shuffle_gen);

  benchmark::DoNotOptimize(quotes.data());
  benchmark::ClobberMemory();

  std::uniform_int_distribution<size_t> selector(0, quotes.size() - 1);
  std::uniform_real_distribution<double> scaler_dis(1.25, 2.50);

  std::string trade_curreny_pair;
  uint64_t trade_value_date = 0;
  instrument trade_instrument = INVALID;

  const int64_t trade_lookup_index = number_of_makers / 2;
  for (auto _ : state) {
    for (int64_t i = 0; i < number_of_makers; ++i) {
      state.PauseTiming();
      const size_t idx = selector(gen);
      const quote_data &data = quotes[idx];
      const double price = data.amount * scaler_dis(gen);

      if (i == trade_lookup_index) {
        trade_curreny_pair = data.currencyPair;
        trade_value_date = data.valueDate;
        trade_instrument = data.inst;
      }
      state.ResumeTiming();
      quote q(data.currencyPair, data.valueDate, data.inst, price,
              data.dealcode, data.uuid);
      benchmark::DoNotOptimize(q);
      manager.handleQuote(q);
    }

    trade trade;
    const bool success = manager.tradeBestPrice(
        trade_curreny_pair, trade_value_date, trade_instrument, trade);
    benchmark::DoNotOptimize(success);
    benchmark::DoNotOptimize(trade);
    benchmark::ClobberMemory();
  }

  benchmark::ClobberMemory();
}

BENCHMARK(bench_mapped_data_quoting_and_trading)
    // base
    ->ArgPair(5, 5)
    ->ArgPair(10, 5)
    ->ArgPair(20, 5)
    ->ArgPair(40, 5)
    ->ArgPair(80, 5)
    // step1
    ->ArgPair(5, 10)
    ->ArgPair(5, 20)
    ->ArgPair(5, 30)
    ->ArgPair(5, 40)
    ->ArgPair(5, 50)
    // step2
    ->ArgPair(10, 10)
    ->ArgPair(10, 20)
    ->ArgPair(10, 30)
    ->ArgPair(10, 40)
    ->ArgPair(10, 50)
    // step3
    ->ArgPair(20, 10)
    ->ArgPair(20, 20)
    ->ArgPair(20, 30)
    ->ArgPair(20, 40)
    ->ArgPair(20, 50)
    // step4
    ->ArgPair(40, 10)
    ->ArgPair(40, 20)
    ->ArgPair(40, 30)
    ->ArgPair(40, 40)
    ->ArgPair(40, 50)
    // step5
    ->ArgPair(80, 10)
    ->ArgPair(80, 20)
    ->ArgPair(80, 30)
    ->ArgPair(80, 40)
    ->ArgPair(80, 50)
    // mass
    ->ArgPair(5000, 50)
    ->ArgPair(5000, 100)
    ->ArgPair(5000, 150)
    ->ArgPair(5000, 200);

static void
bench_mapped_data_quoting_and_trade_best_all(benchmark::State &state) {

  const int64_t number_of_orders = state.range(0);
  const int64_t number_of_makers = state.range(1);

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> lex_dis('A', 'Z');
  std::uniform_int_distribution<> uuid_dis(-999999 * 2, 999999);
  std::uniform_int_distribution<> inst_dis(instrument::SPOT, instrument::SWAP);
  std::uniform_int_distribution<> value_date_dis(-4, 4);
  std::uniform_real_distribution<double> amount_dis(50, 1500000000);

  uint64_t valueDates[]{two_days, one_week, two_week, one_month, two_month};

  mapped_data manager;

  struct quote_data {
    std::string currencyPair;
    uint64_t valueDate;
    instrument inst;
    double amount;
    struct dealcode dealcode;
    int uuid;
  };

  const size_t total_size =
      static_cast<size_t>(number_of_orders * number_of_makers);
  std::vector<quote_data> quotes(total_size);

  for (int64_t i = 0; i < number_of_orders; ++i) {

    int order_id = static_cast<int>(i) + 1;
    std::string currecy_pair;
    currecy_pair.resize(6);
    for (size_t j = 0; j < 6; ++j) {
      currecy_pair[j] = static_cast<char>(lex_dis(gen));
    }
    instrument inst = static_cast<instrument>(inst_dis(gen));
    uint64_t value_date = valueDates[std::max(value_date_dis(gen), 0)];
    double amount = amount_dis(gen);

    manager.addOrder(order(order_id, currecy_pair, inst, value_date, amount));

    for (int64_t n = i * number_of_makers, j = n; j < n + number_of_makers;
         ++j) {
      size_t idx = static_cast<size_t>(j);
      quotes[idx].currencyPair = currecy_pair;
      quotes[idx].valueDate = value_date;
      quotes[idx].inst = inst;
      quotes[idx].amount = amount;
    }
  }

  for (int64_t i = 0; i < number_of_makers; ++i) {
    struct dealcode dealcode;
    for (size_t j = 0; j < 4; ++j) {
      dealcode.data[j] = static_cast<char>(lex_dis(gen));
    }
    int uuid = std::max(uuid_dis(gen), 0);
    manager.addSubscription(maker(dealcode, uuid));

    for (size_t j = static_cast<size_t>(i); j < total_size;
         j += static_cast<size_t>(number_of_makers)) {
      quotes[j].dealcode = dealcode;
      quotes[j].uuid = uuid;
    }
  }
  std::mt19937 shuffle_gen(rd());
  std::shuffle(quotes.begin(), quotes.end(), shuffle_gen);

  benchmark::DoNotOptimize(quotes.data());
  benchmark::ClobberMemory();

  std::uniform_int_distribution<size_t> selector(0, quotes.size() - 1);
  std::uniform_real_distribution<double> scaler_dis(1.25, 2.50);

  std::string trade_curreny_pair;
  uint64_t trade_value_date = 0;
  instrument trade_instrument = INVALID;

  const int64_t trade_lookup_index = number_of_makers / 2;
  for (auto _ : state) {
    for (int64_t i = 0; i < number_of_makers; ++i) {
      state.PauseTiming();
      const size_t idx = selector(gen);
      const quote_data &data = quotes[idx];
      const double price = data.amount * scaler_dis(gen);

      if (i == trade_lookup_index) {
        trade_curreny_pair = data.currencyPair;
        trade_value_date = data.valueDate;
        trade_instrument = data.inst;
      }
      state.ResumeTiming();

      quote q(data.currencyPair, data.valueDate, data.inst, price,
              data.dealcode, data.uuid);
      benchmark::DoNotOptimize(q);
      manager.handleQuote(q);
    }

    std::vector<full_trade> trades;
    manager.tradeBestAll(trades);
    benchmark::DoNotOptimize(trades.data());
    benchmark::ClobberMemory();
  }

  benchmark::ClobberMemory();
}

BENCHMARK(bench_mapped_data_quoting_and_trade_best_all)
    // base
    ->ArgPair(5, 5)
    ->ArgPair(10, 5)
    ->ArgPair(20, 5)
    ->ArgPair(40, 5)
    ->ArgPair(80, 5)
    // step1
    ->ArgPair(5, 10)
    ->ArgPair(5, 20)
    ->ArgPair(5, 30)
    ->ArgPair(5, 40)
    ->ArgPair(5, 50)
    // step2
    ->ArgPair(10, 10)
    ->ArgPair(10, 20)
    ->ArgPair(10, 30)
    ->ArgPair(10, 40)
    ->ArgPair(10, 50)
    // step3
    ->ArgPair(20, 10)
    ->ArgPair(20, 20)
    ->ArgPair(20, 30)
    ->ArgPair(20, 40)
    ->ArgPair(20, 50)
    // step4
    ->ArgPair(40, 10)
    ->ArgPair(40, 20)
    ->ArgPair(40, 30)
    ->ArgPair(40, 40)
    ->ArgPair(40, 50)
    // step5
    ->ArgPair(80, 10)
    ->ArgPair(80, 20)
    ->ArgPair(80, 30)
    ->ArgPair(80, 40)
    ->ArgPair(80, 50)
    // mass
    ->ArgPair(5000, 50)
    ->ArgPair(5000, 100)
    ->ArgPair(5000, 150)
    ->ArgPair(5000, 200);

BENCHMARK_MAIN();
