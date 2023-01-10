#pragma once
#include "../item/item.hpp"
#include "../item/lollipop.hpp"
#include "../texture/texture.hpp"
#include <GL/glut.h>
#include <set>
#include <iostream>
namespace environment {
std::set<item::item *> items;
texture::Texture tex;
void init_items() {
  for (int i = 0; i < 10; i++) {
    items.insert(
        new item::lollipop(rand() % 41 + 10, rand() % 21 - 20, rand() % 360));
  }
  std::cerr << "?";
  tex.load("0032.bmp");
}
void draw_items() {
  glEnable(GL_TEXTURE_2D);
  tex.bind();
  for (auto &i : items) {
    i->draw(1);
  }
  tex.unbind();
  glDisable(GL_TEXTURE_2D);
}
item::item *get_item(int x, int y) {
  item::item *d_ret = nullptr;
  double dis = 100000000;
  for (auto &i : items) {
    double d = i->dis(x, y);
    if (d < dis) {
      dis = d;
      d_ret = i;
    }
  }
  if (dis < 5) {
    item::item *ret = d_ret->clone();
    items.erase(d_ret);
    return ret;
  }
  return nullptr;
}
void push_item(item::item *i) { items.insert(i); }
} // namespace environment