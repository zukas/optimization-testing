#include "caseone.h"

#include <random>

const int iteration_x{500};
const int iteration_y{500};

const int maxLvl{4};

void create_children(DomNode* node, Geom* geoms, int32_t& idx, int lvl) {
  int children = (lvl + 1) * 2;

  for (int i = 0; i < children; i++) {
    std::shared_ptr<DomNode> c = std::make_shared<DomNode>(&geoms[idx++], node);
    node->addChild(c);
    if (lvl < maxLvl)
      create_children(c.get(), geoms, idx, lvl + 1);
  }
}

int main() {
  Geom* geometries = new Geom[5120];
  int32_t idx = 1;
  DomNode* root = new DomNode(&geometries[0]);
  create_children(root, geometries, idx, 0);

  for (int x = 0; x < iteration_x; x++) {
    for (int y = 0; y < iteration_y; y++) {
      Pos p{static_cast<float>(x), static_cast<float>(y)};
      DomNode::move(geometries, idx, p);
    }
  }

  return 0;
}
