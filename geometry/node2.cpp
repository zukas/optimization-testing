#include "node2.h"
#include <algorithm>

Node2::Node2(Node2 *parent) : _parent(parent) {}

Node2::~Node2() {}

void Node2::addChild(std::shared_ptr<Node2> child) {
  _children.push_back(child);
}

void Node2::remChild(std::shared_ptr<Node2> child) {
  auto begin = std::begin(_children), end = std::end(_children),
       it = std::find(begin, end, child);
  if (it != end)
    _children.erase(it);
}

const std::vector<std::shared_ptr<Node2>> &Node2::children() const {
  return _children;
}

void Node2::move(const Pos &position) {
  _nextPosition = position;
  _needUpdate = true;
}

void Node2::resize(const Size &size) {
  _nextSize = size;
  _needUpdate = true;
}

Pos Node2::position() const { return _position; }

Size Node2::size() const { return _size; }

void Node2::performUpdates() {
  bool do_update = _needUpdate;
  if (!do_update) {
    for (const auto &c : _children) {
      do_update |= c->needUpdate();
      if (do_update)
        break;
    }
  }

  if (do_update) {
    update();
    _needUpdate = false;
  }
}

void Node2::update() {
  if (_position != _nextPosition) {
    Pos offset{0, 0};

    if (_parent) {
      offset = _parent->position();
    }
    _prevPositon = _position;
    _position = offset + _nextPosition;
  }

  if (_size != _nextSize) {
    _prevSize = _size;
    _size = _nextSize;
  }

  for (auto &c : _children)
    c->update();
}

bool Node2::needUpdate() const { return _needUpdate; }
