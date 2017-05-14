#include "node1.h"

Node1::Node1(Node1 *parent) : _parent(parent) {}

Node1::~Node1() {}

void Node1::addChild(std::shared_ptr<Node1> child) {
  _children.push_back(child);
}

void Node1::remChild(std::shared_ptr<Node1> child) { _children.remove(child); }

const std::list<std::shared_ptr<Node1>> &Node1::children() const {
  return _children;
}

void Node1::move(const Pos &position) {
  _nextPosition = position;
  _needUpdate = true;
}

void Node1::resize(const Size &size) {
  _nextSize = size;
  _needUpdate = true;
}

Pos Node1::position() const { return _position; }

Size Node1::size() const { return _size; }

void Node1::performUpdates() {
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

void Node1::update() {
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

bool Node1::needUpdate() const { return _needUpdate; }
