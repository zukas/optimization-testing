#ifndef NODE2_H
#define NODE2_H

#include <memory>
#include <string>
#include <vector>

#include "common.h"

class Node2 {
public:
  Node2(Node2 *parent = nullptr);
  virtual ~Node2();

  void addChild(std::shared_ptr<Node2> child);
  void remChild(std::shared_ptr<Node2> child);
  const std::vector<std::shared_ptr<Node2>> &children() const;

  void move(const Pos &position);
  void resize(const Size &size);

  Pos position() const;
  Size size() const;

  void performUpdates();

protected:
  virtual void update();
  virtual bool needUpdate() const;

private:
  std::string _tag;
  std::string _id;
  Pos _position{0.0, 0.0};
  Pos _prevPositon{0.0, 0.0};
  Pos _nextPosition{0.0, 0.0};
  Size _size{0.0, 0.0};
  Size _prevSize{0.0, 0.0};
  Size _nextSize{0.0, 0.0};
  bool _needUpdate{false};

  Node2 *_parent{nullptr};
  std::vector<std::shared_ptr<Node2>> _children;
};
#endif // NODE2_H
