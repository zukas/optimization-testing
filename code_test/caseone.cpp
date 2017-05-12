#include "caseone.h"

DomNode::DomNode(DomNode* parent) : _parent(parent) {}

DomNode::~DomNode() {}

void DomNode::addChild(std::shared_ptr<DomNode> child) {
  _children.push_back(child);
}

void DomNode::remChild(std::shared_ptr<DomNode> child) {
  _children.remove(child);
}

const std::list<std::shared_ptr<DomNode> >& DomNode::children() const {
  return _children;
}

void DomNode::move(const Pos& position) {
  _nextPosition = position;
  _needUpdate = true;
}

void DomNode::resize(const Size& size) {
  _nextSize = size;
  _needUpdate = true;
}

Pos DomNode::position() const {
  return _position;
}

Size DomNode::size() const {
  return _size;
}

void DomNode::performUpdates() {
  bool do_update = _needUpdate;
  if (!do_update) {
    for (const auto& c : _children) {
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

void DomNode::update() {
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

  for (auto& c : _children)
    c->update();
}

bool DomNode::needUpdate() const {
  return _needUpdate;
}
