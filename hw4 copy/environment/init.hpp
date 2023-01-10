#pragma once
#include "ground.hpp"
#include "items.hpp"
#include "light.hpp"
#include "obstacles.hpp"
// #include "../robot/robot.hpp"
#include <GLUT/glut.h>
namespace environment {
obstacles obs = obstacles();
void draw() {
  ground::draw();
  obs.draw();
  draw_items();
}
void draw_light0() {
  light::draw();
  light::draw_light0();
  light::draw_light1();
  // robot::draw_light();
}
void init() {
  init_items();
  ground::init();
  light::init();
}
bool detect_collision(float x0, float y0) {
  return obs.detect_collision(x0, y0);
}
} // namespace environment