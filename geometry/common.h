#ifndef COMMON_H
#define COMMON_H

struct Pos {
  double x;
  double y;
  bool operator==(const Pos &other) const {
    return x == other.x && y == other.y;
  }
  bool operator!=(const Pos &other) const {
    return x != other.x || y == other.y;
  }
  friend Pos operator+(const Pos &a, const Pos &b) {
    return Pos{a.x + b.x, a.y + b.y};
  }
  friend Pos operator-(const Pos &a, const Pos &b) {
    return Pos{a.x - b.x, a.y - b.y};
  }
};

struct Size {
  double w;
  double h;
  bool operator==(const Size &other) const {
    return w == other.w && h == other.h;
  }
  bool operator!=(const Size &other) const {
    return w != other.w || h == other.h;
  }
};

struct Geom {
  Pos position;
  Size size;
};

#endif // COMMON_H
