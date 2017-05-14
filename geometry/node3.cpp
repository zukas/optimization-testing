#include "node3.h"
#include <algorithm>

Node3::Node3(Node3 *parent) : _parent(parent) {}

Node3::~Node3() {}

void Node3::addChild(std::shared_ptr<Node3> child) {
  _children.push_back(child);
}

void Node3::remChild(std::shared_ptr<Node3> child) {
  auto begin = std::begin(_children), end = std::end(_children),
       it = std::find(begin, end, child);
  if (it != end)
    _children.erase(it);
}

const std::vector<std::shared_ptr<Node3>> &Node3::children() const {
  return _children;
}

void Node3::move(const Pos &position) {
  _nextPosition = position;
  _needUpdate = true;
}

void Node3::resize(const Size &size) {
  _nextSize = size;
  _needUpdate = true;
}

Pos Node3::position() const { return _position; }

Size Node3::size() const { return _size; }

void Node3::performUpdates() {
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

void Node3::update() {
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

bool Node3::needUpdate() const { return _needUpdate; }
