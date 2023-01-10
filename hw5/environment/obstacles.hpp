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
    // stones.push_back({57, 27});
    // stones.push_back({3, 27});
    // stones.push_back({3, -27});
    // stones.push_back({57, -27});
    for (int i = 3; i <= 60; i += 7) {
      stones.push_back({i, 27});
    }
    // for (int i = 0; i < 10; i++) {
    //   stones.push_back({rand() % 45 + 10, rand() % 45 - 30});
    // }
  }
  void init() {
    for (auto &i : stones) {
      i.init();
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