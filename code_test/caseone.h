#ifndef CASEONE_H
#define CASEONE_H

#include <string>
#include <vector>
#include <memory>

struct Pos {
  float x;
  float y;
};

struct Size {
  float w;
  float h;
};

struct Geom {
  Pos position;
  Size size;
};

class DomNode {
 public:
  DomNode(Geom* geom, DomNode* parent = nullptr);

  void addChild(std::shared_ptr<DomNode> child);
  void remChild(std::shared_ptr<DomNode> child);
  const std::vector<std::shared_ptr<DomNode>>& children() const;

  const Geom& geometry() const;

  static void move(Geom* geometries, int32_t count, Pos pos);

 private:
  Geom* _geom{nullptr};
  std::vector<std::shared_ptr<DomNode>> _children;
  std::string _id;
  std::string _tag;
  DomNode* _parent{nullptr};
};

#endif  // CASEONE_H
