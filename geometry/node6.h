#ifndef NODE6_H
#define NODE6_H

#include <memory>
#include <string>
#include <vector>

#include "common.h"

class Node6 {
public:
  Node6(Geom *geom, Node6 *parent = nullptr);

  void addChild(std::shared_ptr<Node6> child);
  void remChild(std::shared_ptr<Node6> child);
  const std::vector<std::shared_ptr<Node6>> &children() const;

  const Geom &geometry() const;

  static void move(Geom *geometries, int32_t count, Pos pos);

private:
  Geom *_geom{nullptr};
  std::vector<std::shared_ptr<Node6>> _children;
  std::string _id;
  std::string _tag;
  Node6 *_parent{nullptr};
};
#endif // NODE6_H
