#ifndef NODE5_H
#define NODE5_H

#include <memory>
#include <string>
#include <vector>

#include "common.h"

class Node5 {
public:
  Node5(Node5 *parent = nullptr);
  virtual ~Node5();

  void addChild(std::shared_ptr<Node5> child);
  void remChild(std::shared_ptr<Node5> child);
  const std::vector<std::shared_ptr<Node5>> &children() const;

  void move(const Pos &position);
  void resize(const Size &size);

  Pos position() const;
  Size size() const;

private:
  std::vector<std::shared_ptr<Node5>> _children;
  Pos _position{0.0, 0.0};
  Pos _prevPositon{0.0, 0.0};
  Size _size{0.0, 0.0};
  Size _prevSize{0.0, 0.0};
  std::string _tag;
  std::string _id;
  Node5 *_parent{nullptr};
};

#endif // NODE5_H
