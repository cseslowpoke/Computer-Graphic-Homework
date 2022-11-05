#pragma once
#include "item.hpp"
#include <GL/glut.h>
#include <cmath>
#include <iostream>
namespace item {
class lollipop : public item {
  GLUquadricObj *cylinder = gluNewQuadric();
  GLUquadricObj *sphere = gluNewQuadric();

public:
  lollipop() {}
  lollipop(double x, double y, double angle = 0) {
    this->x = x;
    this->y = y;
  }
  void draw(int mode) {
    glPushMatrix();
    if (mode) {
      glTranslated(x, 0, y);
      glRotated(angle, 0, 1, 0);
    }
    glRotated(90, 0, 1, 0);
    glColor3f(0.5, 0.5, 0.5);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    gluCylinder(cylinder, 0.2, 0.2, 10, 5, 5);
    glTranslated(0, 0, 10);
    glColor3f(1, 0, 0);
    gluSphere(sphere, 2, 10, 10);
    glPopMatrix();
  }
  void setxy(double x, double y, double angle = 0) {
    this->x = x;
    this->y = y;
    this->angle = angle;
  }
  double dis(double x, double y) {
    return std::sqrt((this->x - x) * (this->x - x) +
                     (this->y - y) * (this->y - y));
  }
  lollipop *clone() const { return new lollipop(*this); }
};
} // namespace item
