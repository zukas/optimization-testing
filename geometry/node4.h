#ifndef NODE4_H
#define NODE4_H

#include <memory>
#include <string>
#include <vector>

#include "common.h"

class Node4 {
public:
  Node4(Node4 *parent = nullptr);
  virtual ~Node4();

  void addChild(std::shared_ptr<Node4> child);
  void remChild(std::shared_ptr<Node4> child);
  const std::vector<std::shared_ptr<Node4>> &children() const;

  void move(const Pos &position);
  void resize(const Size &size);

  Pos position() const;
  Size size() const;

  void performUpdates();

protected:
  virtual void update();
  virtual bool needUpdate() const;

private:
  std::vector<std::shared_ptr<Node4>> _children;
  Pos _position{0.0, 0.0};
  Pos _prevPositon{0.0, 0.0};
  Pos _nextPosition{0.0, 0.0};
  Size _size{0.0, 0.0};
  Size _prevSize{0.0, 0.0};
  Size _nextSize{0.0, 0.0};
  std::string _tag;
  std::string _id;
  Node4 *_parent{nullptr};
};
#endif // NODE4_H
