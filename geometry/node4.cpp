#include "node4.h"
#include <algorithm>

Node4::Node4(Node4 *parent) : _parent(parent) {}

Node4::~Node4() {}

void Node4::addChild(std::shared_ptr<Node4> child) {
  _children.push_back(child);
}

void Node4::remChild(std::shared_ptr<Node4> child) {
  auto begin = std::begin(_children), end = std::end(_children),
       it = std::find(begin, end, child);
  if (it != end)
    _children.erase(it);
}

const std::vector<std::shared_ptr<Node4>> &Node4::children() const {
  return _children;
}

void Node4::move(const Pos &position) { _nextPosition = position; }

void Node4::resize(const Size &size) { _nextSize = size; }

Pos Node4::position() const { return _position; }

Size Node4::size() const { return _size; }

void Node4::performUpdates() {
  bool do_update = _position != _nextPosition || _size != _nextSize;
  if (!do_update) {
    for (const auto &c : _children) {
      do_update |= c->needUpdate();
      if (do_update)
        break;
    }
  }

  if (do_update) {
    update();
  }
}

void Node4::update() {
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

bool Node4::needUpdate() const {
  return _position != _nextPosition || _size != _nextSize;
}
