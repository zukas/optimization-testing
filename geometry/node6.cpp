#include "node6.h"
#include <algorithm>

Node6::Node6(Geom *geom, Node6 *parent) : _geom(geom), _parent(parent) {}

void Node6::addChild(std::shared_ptr<Node6> child) {
  _children.push_back(child);
}

void Node6::remChild(std::shared_ptr<Node6> child) {
  auto begin = std::begin(_children), end = std::end(_children),
       it = std::find(begin, end, child);
  if (it != end)
    _children.erase(it);
}

const std::vector<std::shared_ptr<Node6>> &Node6::children() const {
  return _children;
}

const Geom &Node6::geometry() const { return *_geom; }

void Node6::move(Geom *geometries, int32_t count, Pos pos) {
  auto offset_x = geometries[0].position.x - pos.x;
  auto offset_y = geometries[0].position.y - pos.y;
  geometries[0].position = pos;
  for (int32_t i = 1; i < count; i++) {
    geometries[i].position.x += offset_x;
    geometries[i].position.x += offset_y;
  }
}
