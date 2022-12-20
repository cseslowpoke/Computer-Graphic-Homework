#pragma once
#include "item.hpp"
#include <GL/glut.h>
#include <cmath>
namespace item {
class lollipop : public item {
  GLUquadricObj *cylinder = gluNewQuadric();
  GLUquadricObj *sphere = gluNewQuadric();

public:
  lollipop() {}
  lollipop(double x, double y, double angle = 0) {
    gluQuadricNormals(cylinder, GLU_SMOOTH);
    gluQuadricNormals(sphere, GLU_SMOOTH);

    this->x = x;
    this->y = y;
    this->angle = angle;
  }
  void draw(int mode) {
    glPushMatrix();
    if (mode) {
      glTranslated(x, 0, y);
      glRotated(angle, 0, 1, 0);
    }
    glRotated(90, 0, 1, 0);
    float mat[3]; // material
    mat[0] = 0.0;
    mat[1] = 0.0;
    mat[2] = 0.0;
    mat[3] = 1.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
    mat[0] = 0.55;
    mat[1] = 0.55;
    mat[2] = 0.55;
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
    mat[0] = 0.70;
    mat[1] = 0.70;
    mat[2] = 0.70;
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
    // glMaterialf(GL_FRONT, );
    glMaterialf(GL_FRONT, GL_SHININESS, 0.25 * 128.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    gluCylinder(cylinder, 0.2, 0.2, 10, 5, 5);
    glTranslated(0, 0, 10);
    mat[0] = 0.1745;
    mat[1] = 0.01175;
    mat[2] = 0.01175;
    mat[3] = 1.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
    mat[0] = 0.61424;
    mat[1] = 0.04136;
    mat[2] = 0.04136;
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
    mat[0] = 0.727811;
    mat[1] = 0.626959;
    mat[2] = 0.626959;
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
    glMaterialf(GL_FRONT, GL_SHININESS, 0.6 * 128.0);
    gluSphere(sphere, 2, 10, 10);
    // glTranslated(0, 0, 0.8);
    glScaled(1, 1, 0.2);
    gluSphere(sphere, 2.2, 10, 10);
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
