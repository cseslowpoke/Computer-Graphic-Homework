#pragma once
#include "../debug/debug.hpp"
#include "../environment/init.hpp"
#include "../environment/items.hpp"
#include "torso.hpp"
#include <cmath>
#include <iostream>
const float PI = 3.14159265358979323846;
namespace robot {
torso torsola;
float x, y, z;
int walk = 0;
int is_walk = 0;
float angle = 0;
int left = 0;
int right = 0;
int is_jump = 0;
int is_knee_down = 0;
int is_orz = 0;
void init(float _x, float _y, float _z) {
  x = _x;
  y = _y;
  z = _z;
  torsola.init();
}
int tmp = 0;
void draw() {
  // std::cerr << tmp++ << '\n';
  glPushMatrix();
  glTranslatef(x, y, z);
  glRotated(angle, 0, 1, 0);
  if (walk > 0) {
    for (int i = 0; i < walk / 5 + 1; i++) {
      // std::cout << '?';
      torsola.walk_forward();
      torsola.walk_forward();
      if (environment::detect_collision(x + 0.004 * std::sin(angle * PI / 180),
                                        z + 0.004 * std::cos(angle * PI / 180)))
        continue;
      x += 0.004 * std::sin(angle * PI / 180);
      z += 0.004 * std::cos(angle * PI / 180);
    }
    if (walk > is_walk / 60) {
      walk = is_walk / 60;
    }
  } else if (walk < 0) {
    for (int i = 0; i < -walk / 5 + 1; i++) {
      torsola.walk_backward();
      torsola.walk_backward();
      if (environment::detect_collision(x - 0.004 * std::sin(angle * PI / 180),
                                        z - 0.004 * std::cos(angle * PI / 180)))
        continue;
      x -= 0.004 * std::sin(angle * PI / 180);
      z -= 0.004 * std::cos(angle * PI / 180);
    }
    if (-walk > is_walk / 60) {
      walk = -is_walk / 60;
    }
  }

  if (left > 0) {
    left--;
    angle = angle + 0.06;
    torsola.turn_left();
    if (angle > 360)
      angle -= 360;
  }

  if (right > 0) {
    right--;
    angle = angle - 0.06;
    torsola.turn_right();
    if (angle < 0)
      angle += 360;
  }

  if (is_walk)
    is_walk--;
  if (is_jump) {
    is_jump += 50;
    if (is_jump >= 8000) {
      is_jump = 0;
    }
    torsola.set_jump(is_jump);
  }

  if (!is_walk &&
      (abs(torsola.get_walk() - 45) > 1 && abs(torsola.get_walk() - 135) > 1)) {
    torsola.walk_forward();
    torsola.walk_forward();
    torsola.walk_forward();
    torsola.walk_forward();
    torsola.walk_forward();
  }

  torsola.draw();
  glPopMatrix();
}

void draw_light() {
  // return;
  glPushMatrix();
  glTranslatef(x, y, z);
  glRotated(angle, 0, 1, 0);
  torsola.draw_light();
  glPopMatrix();
}

float get_x() { return x; }

float get_y() { return y; }

float get_z() { return z; }

void set_x(float _x) { x = _x; }

void set_y(float _y) { y = _y; }

void set_z(float _z) { z = _z; }

void walk_forward() {
  // if(is_jump) return;
  is_walk = 2000;
  walk++;
  walk = walk < 5 ? 5 : walk;
  walk = walk > 15 ? 15 : walk;
  // torsola.walk_forward();
  // x += 0.7 * std::sin(angle * PI / 180);
  // z += 0.7 * std::cos(angle * PI / 180);
}

void walk_backward() {
  // if(is_jump) return;
  is_walk = 2000;
  walk--;
  walk = walk > -5 ? -5 : walk;
  walk = walk < -15 ? -15 : walk;
  // torsola.walk_backward();
  // x -= 0.7 * std::sin(angle * PI / 180);
  // z -= 0.7 * std::cos(angle * PI / 180);
}

void turn_left() {
  left += 300;
  left = left > 600 ? 600 : left;
  is_walk = 0;

  // while (abs(torsola.get_walk() - 45) > 5) {
  //   torsola.walk_forward();
  // }
  // (angle += 5) %= 360;
}

void turn_right() {
  right += 300;
  right = right > 600 ? 600 : right;
  is_walk = 0;
  // while (abs(torsola.get_walk() - 45) > 5) {
  //   torsola.walk_forward();
  // }
  // (angle += 355) %= 360;
}

void jump() {
  if (is_jump != 0)
    return;
  is_walk = 0;
  while (abs(torsola.get_walk() - 45) > 0.1) {
    torsola.walk_forward();
  }
  is_jump = 1;
}

void knee_down() {
  if (is_jump != 0)
    return;
  is_walk = 0;
  while (abs(torsola.get_walk() - 45) > 0.1) {
    torsola.walk_forward();
  }
  is_knee_down = 1;
}

void grasp_or_drop_left() {
  item::item *now = torsola.get_grasp_left();
  if (now == NULL) {
    item::item *tmp = environment::get_item(x, z);
    if (tmp == NULL)
      return;
    torsola.grasp_item_left(tmp);
  } else {
    item::item *tmp = now->clone();
    tmp->setxy(x + 4 * std::sin(angle * PI / 180),
               z + 4 * std::cos(angle * PI / 180), angle);
    environment::push_item(tmp);
    torsola.grasp_item_left(nullptr);
    // environment::add_item(now);
  }
}
void grasp_or_drop_right() {
  item::item *now = torsola.get_grasp_right();
  if (now == NULL) {
    item::item *tmp = environment::get_item(x, z);
    if (tmp == NULL)
      return;
    torsola.grasp_item_right(tmp);
  } else {
    item::item *tmp = now->clone();
    tmp->setxy(x + 4 * std::sin(angle * PI / 180),
               z + 4 * std::cos(angle * PI / 180), angle);
    environment::push_item(tmp);
    torsola.grasp_item_right(nullptr);
    // environment::add_item(now);
  }
}
void orz() {
  torsola.orz();
  is_orz = !is_orz;
}
// float get_x(){
//   return x;
// }
// float get_y(){
//   return y;
// }
// float get_z(){
//   return z;`
// }
float get_angle() { return angle; }
} // namespace robot