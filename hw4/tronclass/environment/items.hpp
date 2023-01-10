#pragma once
#include "../item/item.hpp"
#include "../item/lollipop.hpp"
#include <GL/glut.h>
#include <set>
namespace environment {
std::set<item::item *> items;
void init_items() {
  // items.insert(new item::lollipop(12, 34));
  // items.insert(new item::lollipop(7, 8));
  // items.insert(new item::lollipop(37, 12));
  // items.insert(new item::lollipop(-10, 20));
  for (int i = 0; i < 10; i++) {
    items.insert(
        new item::lollipop(rand() % 70 - 10, rand() % 45 - 15, rand() % 360));
  }
}
void draw_items() {
  for (auto &i : items) {
    i->draw(1);
  }
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