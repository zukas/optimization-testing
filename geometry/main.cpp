#include <benchmark/benchmark.h>
#include <limits>
#include <random>

#include "common.h"
#include "node1.h"
#include "node2.h"
#include "node3.h"
#include "node4.h"
#include "node5.h"
#include "node6.h"

class node1_fixture : public ::benchmark::Fixture {
public:
  void SetUp(const ::benchmark::State &st) {
    root = new Node1();
    create_children(root, 0, st.range(0));
  }

  Pos get_position() { return Pos{dist(gen), dist(gen)}; }

  void TearDown(const ::benchmark::State &) { delete root; }
  Node1 *root;

private:
  static void create_children(Node1 *node, int lvl, int maxLvl) {
    int children = (lvl + 1) * 2;

    for (int i = 0; i < children; i++) {
      std::shared_ptr<Node1> c = std::make_shared<Node1>(node);
      node->addChild(c);
      if (lvl < maxLvl)
        create_children(c.get(), lvl + 1, maxLvl);
    }
  }

  std::random_device rd;
  std::mt19937 gen{rd()};
  std::uniform_real_distribution<double> dist{
      std::numeric_limits<double>::min(), std::numeric_limits<double>::max()};
};

BENCHMARK_DEFINE_F(node1_fixture, obj)(benchmark::State &state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    Pos p = get_position();
    state.ResumeTiming();
    root->move(p);
    root->performUpdates();
  }
}

BENCHMARK_REGISTER_F(node1_fixture, obj)->Arg(2);
BENCHMARK_REGISTER_F(node1_fixture, obj)->Arg(3);
BENCHMARK_REGISTER_F(node1_fixture, obj)->Arg(4);
BENCHMARK_REGISTER_F(node1_fixture, obj)->Arg(5);
BENCHMARK_REGISTER_F(node1_fixture, obj)->Arg(6);

class node2_fixture : public ::benchmark::Fixture {
public:
  void SetUp(const ::benchmark::State &st) {
    root = new Node2();
    create_children(root, 0, st.range(0));
  }

  Pos get_position() { return Pos{dist(gen), dist(gen)}; }

  void TearDown(const ::benchmark::State &) { delete root; }
  Node2 *root;

private:
  static void create_children(Node2 *node, int lvl, int maxLvl) {
    int children = (lvl + 1) * 2;

    for (int i = 0; i < children; i++) {
      std::shared_ptr<Node2> c = std::make_shared<Node2>(node);
      node->addChild(c);
      if (lvl < maxLvl)
        create_children(c.get(), lvl + 1, maxLvl);
    }
  }

  std::random_device rd;
  std::mt19937 gen{rd()};
  std::uniform_real_distribution<double> dist{
      std::numeric_limits<double>::min(), std::numeric_limits<double>::max()};
};

BENCHMARK_DEFINE_F(node2_fixture, obj)(benchmark::State &state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    Pos p = get_position();
    state.ResumeTiming();
    root->move(p);
    root->performUpdates();
  }
}

BENCHMARK_REGISTER_F(node2_fixture, obj)->Arg(2);
BENCHMARK_REGISTER_F(node2_fixture, obj)->Arg(3);
BENCHMARK_REGISTER_F(node2_fixture, obj)->Arg(4);
BENCHMARK_REGISTER_F(node2_fixture, obj)->Arg(5);
BENCHMARK_REGISTER_F(node2_fixture, obj)->Arg(6);

class node3_fixture : public ::benchmark::Fixture {
public:
  void SetUp(const ::benchmark::State &st) {
    root = new Node3();
    create_children(root, 0, st.range(0));
  }

  Pos get_position() { return Pos{dist(gen), dist(gen)}; }

  void TearDown(const ::benchmark::State &) { delete root; }
  Node3 *root;

private:
  static void create_children(Node3 *node, int lvl, int maxLvl) {
    int children = (lvl + 1) * 2;

    for (int i = 0; i < children; i++) {
      std::shared_ptr<Node3> c = std::make_shared<Node3>(node);
      node->addChild(c);
      if (lvl < maxLvl)
        create_children(c.get(), lvl + 1, maxLvl);
    }
  }

  std::random_device rd;
  std::mt19937 gen{rd()};
  std::uniform_real_distribution<double> dist{
      std::numeric_limits<double>::min(), std::numeric_limits<double>::max()};
};

BENCHMARK_DEFINE_F(node3_fixture, obj)(benchmark::State &state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    Pos p = get_position();
    state.ResumeTiming();
    root->move(p);
    root->performUpdates();
  }
}

BENCHMARK_REGISTER_F(node3_fixture, obj)->Arg(2);
BENCHMARK_REGISTER_F(node3_fixture, obj)->Arg(3);
BENCHMARK_REGISTER_F(node3_fixture, obj)->Arg(4);
BENCHMARK_REGISTER_F(node3_fixture, obj)->Arg(5);
BENCHMARK_REGISTER_F(node3_fixture, obj)->Arg(6);

class node4_fixture : public ::benchmark::Fixture {
public:
  void SetUp(const ::benchmark::State &st) {
    root = new Node4();
    create_children(root, 0, st.range(0));
  }

  Pos get_position() { return Pos{dist(gen), dist(gen)}; }

  void TearDown(const ::benchmark::State &) { delete root; }
  Node4 *root;

private:
  static void create_children(Node4 *node, int lvl, int maxLvl) {
    int children = (lvl + 1) * 2;

    for (int i = 0; i < children; i++) {
      std::shared_ptr<Node4> c = std::make_shared<Node4>(node);
      node->addChild(c);
      if (lvl < maxLvl)
        create_children(c.get(), lvl + 1, maxLvl);
    }
  }

  std::random_device rd;
  std::mt19937 gen{rd()};
  std::uniform_real_distribution<double> dist{
      std::numeric_limits<double>::min(), std::numeric_limits<double>::max()};
};

BENCHMARK_DEFINE_F(node4_fixture, obj)(benchmark::State &state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    Pos p = get_position();
    state.ResumeTiming();
    root->move(p);
    root->performUpdates();
  }
}

BENCHMARK_REGISTER_F(node4_fixture, obj)->Arg(2);
BENCHMARK_REGISTER_F(node4_fixture, obj)->Arg(3);
BENCHMARK_REGISTER_F(node4_fixture, obj)->Arg(4);
BENCHMARK_REGISTER_F(node4_fixture, obj)->Arg(5);
BENCHMARK_REGISTER_F(node4_fixture, obj)->Arg(6);

class node5_fixture : public ::benchmark::Fixture {
public:
  void SetUp(const ::benchmark::State &st) {
    root = new Node5();
    create_children(root, 0, st.range(0));
  }

  Pos get_position() { return Pos{dist(gen), dist(gen)}; }

  void TearDown(const ::benchmark::State &) { delete root; }
  Node5 *root;

private:
  static void create_children(Node5 *node, int lvl, int maxLvl) {
    int children = (lvl + 1) * 2;

    for (int i = 0; i < children; i++) {
      std::shared_ptr<Node5> c = std::make_shared<Node5>(node);
      node->addChild(c);
      if (lvl < maxLvl)
        create_children(c.get(), lvl + 1, maxLvl);
    }
  }

  std::random_device rd;
  std::mt19937 gen{rd()};
  std::uniform_real_distribution<double> dist{
      std::numeric_limits<double>::min(), std::numeric_limits<double>::max()};
};

BENCHMARK_DEFINE_F(node5_fixture, obj)(benchmark::State &state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    Pos p = get_position();
    state.ResumeTiming();
    root->move(p);
  }
}

BENCHMARK_REGISTER_F(node5_fixture, obj)->Arg(2);
BENCHMARK_REGISTER_F(node5_fixture, obj)->Arg(3);
BENCHMARK_REGISTER_F(node5_fixture, obj)->Arg(4);
BENCHMARK_REGISTER_F(node5_fixture, obj)->Arg(5);
BENCHMARK_REGISTER_F(node5_fixture, obj)->Arg(6);

class node6_fixture : public ::benchmark::Fixture {
public:
  void SetUp(const ::benchmark::State &st) {
    root = new Node6(0);
    create_children(root, geoms, 0, st.range(0));
  }

  Pos get_position() { return Pos{dist(gen), dist(gen)}; }

  void TearDown(const ::benchmark::State &) {
    delete root;
    geoms.clear();
  }
  Node6 *root;
  std::vector<Geom> geoms;

private:
  static void create_children(Node6 *node, std::vector<Geom> &geoms, int lvl,
                              int maxLvl) {
    int children = (lvl + 1) * 2;

    for (int i = 0; i < children; i++) {
      geoms.push_back(Geom{{0, 0}, {0, 0}});
      std::shared_ptr<Node6> c = std::make_shared<Node6>(&geoms.back(), node);
      node->addChild(c);
      if (lvl < maxLvl)
        create_children(c.get(), geoms, lvl + 1, maxLvl);
    }
  }

  std::random_device rd;
  std::mt19937 gen{rd()};
  std::uniform_real_distribution<double> dist{
      std::numeric_limits<double>::min(), std::numeric_limits<double>::max()};
};

BENCHMARK_DEFINE_F(node6_fixture, obj)(benchmark::State &state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    Pos p = get_position();
    state.ResumeTiming();
    Node6::move(geoms.data(), static_cast<int>(geoms.size()), p);
  }
}

BENCHMARK_REGISTER_F(node6_fixture, obj)->Arg(2);
BENCHMARK_REGISTER_F(node6_fixture, obj)->Arg(3);
BENCHMARK_REGISTER_F(node6_fixture, obj)->Arg(4);
BENCHMARK_REGISTER_F(node6_fixture, obj)->Arg(5);
BENCHMARK_REGISTER_F(node6_fixture, obj)->Arg(6);

BENCHMARK_MAIN();
