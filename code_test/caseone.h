#ifndef CASEONE_H
#define CASEONE_H

#include <string>
#include <vector>
#include <memory>

struct Pos {
  double x;
  double y;
  bool operator==(const Pos& other) const {
    return x == other.x && y == other.y;
  }
  bool operator!=(const Pos& other) const {
    return x != other.x || y == other.y;
  }
  friend Pos operator+(const Pos& a, const Pos& b) {
    return Pos{a.x + b.x, a.y + b.y};
  }
};

struct Size {
  double w;
  double h;
  bool operator==(const Size& other) const {
    return w == other.w && h == other.h;
  }
  bool operator!=(const Size& other) const {
    return w != other.w || h == other.h;
  }
};

class DomNode {
 public:
  DomNode(DomNode* parent = nullptr);
  virtual ~DomNode();

  void addChild(std::shared_ptr<DomNode> child);
  void remChild(std::shared_ptr<DomNode> child);
  const std::vector<std::shared_ptr<DomNode>>& children() const;

  void move(const Pos& position);
  void resize(const Size& size);

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

  DomNode* _parent{nullptr};
  std::vector<std::shared_ptr<DomNode>> _children;
};

#endif  // CASEONE_H
