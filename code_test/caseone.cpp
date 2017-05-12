#include "caseone.h"
#include <algorithm>

DomNode::DomNode(DomNode* parent) : _parent(parent) {}

DomNode::~DomNode() {}

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

void DomNode::move(const Pos& position) {
  _prevPositon = _position;
  _position = position;
  for (auto& c : _children)
    c->move(position);
}

void DomNode::resize(const Size& size) {
  _size = size;
}

Pos DomNode::position() const {
  return _position;
}

Size DomNode::size() const {
  return _size;
}
