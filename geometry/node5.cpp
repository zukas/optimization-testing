#include "node5.h"
#include <algorithm>

Node5::Node5(Node5 *parent) : _parent(parent) {}

Node5::~Node5() {}

void Node5::addChild(std::shared_ptr<Node5> child) {
  _children.push_back(child);
}

void Node5::remChild(std::shared_ptr<Node5> child) {
  auto begin = std::begin(_children), end = std::end(_children),
       it = std::find(begin, end, child);
  if (it != end)
    _children.erase(it);
}

const std::vector<std::shared_ptr<Node5>> &Node5::children() const {
  return _children;
}

void Node5::move(const Pos &position) {

  Pos offset{0, 0};

  if (_parent) {
    offset = _parent->position() - _position;
  }

  _prevPositon = _position;
  _position = offset + position;

  for (auto &c : _children)
    c->move({0, 0});
}

void Node5::resize(const Size &size) { _size = size; }

Pos Node5::position() const { return _position; }

Size Node5::size() const { return _size; }
