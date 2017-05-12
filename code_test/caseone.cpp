#include "caseone.h"
#include <algorithm>

DomNode::DomNode(Geom* geom, DomNode* parent) : _geom(geom), _parent(parent) {}

void DomNode::addChild(std::shared_ptr<DomNode> child) {
  _children.push_back(child);
}

void DomNode::remChild(std::shared_ptr<DomNode> child) {
  auto begin = std::begin(_children), end = std::end(_children),
       it = std::find(begin, end, child);
  if (it != end)
    _children.erase(it);
}

const std::vector<std::shared_ptr<DomNode> >& DomNode::children() const {
  return _children;
}

const Geom& DomNode::geometry() const {
  return *_geom;
}

void DomNode::move(Geom* geometries, int32_t count, Pos pos) {
  float offset_x = geometries[0].position.x - pos.x;
  float offset_y = geometries[0].position.y - pos.y;
  geometries[0].position = pos;
  for (int32_t i = 1; i < count; i++) {
    geometries[i].position.x += offset_x;
    geometries[i].position.x += offset_y;
  }
}
