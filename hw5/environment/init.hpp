#pragma once
#include "ground.hpp"
#include "items.hpp"
#include "light.hpp"
#include "obstacles.hpp"
#include "tree.hpp"
#include "slowpoke.hpp"
// #include "../robot/robot.hpp"
#include <GL/glut.h>
namespace environment {
obstacles obs = obstacles();
tree t = tree();
slowpoke dai = slowpoke();
void draw(float w1, float w2) {
  ground::draw();
  obs.draw();
  draw_items();
  t.draw(w1, w2);
  dai.draw(w1, w2);
}
void draw_light0() {
  light::draw();
  light::draw_light0();
  light::draw_light1();
}
void init() {
  init_items();
  obs.init();
  ground::init();
  light::init();
  t.init();
  dai.init();
}
bool detect_collision(float x0, float y0) {
  return obs.detect_collision(x0, y0);
}
} // namespace environment