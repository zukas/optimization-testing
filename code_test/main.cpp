#include "caseone.h"

#include <random>

const int iteration_x{500};
const int iteration_y{500};

const int maxLvl{4};

void create_children(DomNode* node, int lvl) {
  int children = (lvl + 1) * 2;

  for (int i = 0; i < children; i++) {
    std::shared_ptr<DomNode> c = std::make_shared<DomNode>(node);
    node->addChild(c);
    if (lvl < maxLvl)
      create_children(c.get(), lvl + 1);
  }
}

int main() {
  DomNode* root = new DomNode();
  create_children(root, 0);

  for (int x = 0; x < iteration_x; x++) {
    for (int y = 0; y < iteration_y; y++) {
      Pos p{static_cast<double>(x), static_cast<double>(y)};
      root->move(p);
    }
  }

  return 0;
}
