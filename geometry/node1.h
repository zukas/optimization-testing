#ifndef NODE1_H
#define NODE1_H

#include <list>
#include <memory>
#include <string>

#include "common.h"

class Node1 {
public:
  Node1(Node1 *parent = nullptr);
  virtual ~Node1();

  void addChild(std::shared_ptr<Node1> child);
  void remChild(std::shared_ptr<Node1> child);
  const std::list<std::shared_ptr<Node1>> &children() const;

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

  Node1 *_parent{nullptr};
  std::list<std::shared_ptr<Node1>> _children;
};

#endif // NODE1_H
