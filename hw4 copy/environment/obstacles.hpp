#pragma once
#include "stone.hpp"
#include <ctime>
#include <vector>
namespace environment {
class obstacles {
  std::vector<stone> stones;

public:
  obstacles() {
    srand(time(NULL));
    for (int i = 0; i < 10; i++) {
      stones.push_back(stone(rand() % 70 - 10, rand() % 45 - 15));
    }
  }
  void draw() {
    for (auto &s : stones) {
      s.draw();
    }
  }
  bool detect_collision(float x0, float y0) {
    for (auto &s : stones) {
      if (s.check(x0 - 2, y0 - 2, x0 + 2, y0 + 2)) {
        return true;
      }
    }
    return false;
  }
};
} // namespace environment