#pragma once
#include "stone.hpp"
#include <vector>
namespace environment {
class obstacles {
  std::vector<stone> stones;

public:
  obstacles() {
    stones.push_back({0, 0});
    stones.push_back({7, 8});
    stones.push_back({37, 12});
    stones.push_back({-10, 20});
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