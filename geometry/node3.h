#ifndef NODE3_H
#define NODE3_H

#include <memory>
#include <string>
#include <vector>

#include "common.h"

class Node3 {
public:
  Node3(Node3 *parent = nullptr);
  virtual ~Node3();

  void addChild(std::shared_ptr<Node3> child);
  void remChild(std::shared_ptr<Node3> child);
  const std::vector<std::shared_ptr<Node3>> &children() const;

  void move(const Pos &position);
  void resize(const Size &size);

  Pos position() const;
  Size size() const;

  void performUpdates();

protected:
  virtual void update();
  virtual bool needUpdate() const;

private:
  std::vector<std::shared_ptr<Node3>> _children;
  Pos _position{0.0, 0.0};
  Pos _prevPositon{0.0, 0.0};
  Pos _nextPosition{0.0, 0.0};
  Size _size{0.0, 0.0};
  Size _prevSize{0.0, 0.0};
  Size _nextSize{0.0, 0.0};
  bool _needUpdate{false};
  std::string _tag;
  std::string _id;
  Node3 *_parent{nullptr};
};
#endif // NODE3_H
