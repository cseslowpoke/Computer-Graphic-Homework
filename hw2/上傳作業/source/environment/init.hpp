#pragma once
#include "ground.hpp"
#include "items.hpp"
#include "obstacles.hpp"
#include <GL/glut.h>
namespace environment {
obstacles obs = obstacles();
void draw() {
  // glTranslated(0, 0, 0);
  // glScalef(2, 2, 2);
  ground::draw();
  obs.draw();
  draw_items();
}
void init() { init_items(); }
bool detect_collision(float x0, float y0) {
  return obs.detect_collision(x0, y0);
}
} // namespace environment