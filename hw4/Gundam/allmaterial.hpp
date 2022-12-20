#pragma once
#include <GL/glut.h>
namespace gundam {
void green_material() {
  float mat[3];
  mat[0] = 0.0215;
  mat[1] = 0.1745;
  mat[2] = 0.0215;
  mat[3] = 1.0;
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
  mat[0] = 0.07450980392;
  mat[1] = 0.39215686274;
  mat[2] = 0.31764705882;
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
  mat[0] = 0.633;
  mat[1] = 0.727811;
  mat[2] = 0.633;
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
  glMaterialf(GL_FRONT, GL_SHININESS, 0.6 * 128.0);
}
void white_material() {
  float mat[3];
  mat[0] = 0.19225;
  mat[1] = 0.19225;
  mat[2] = 0.19225;
  mat[3] = 1.0;
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
  mat[0] = 0.85;
  mat[1] = 0.85;
  mat[2] = 0.85;
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
  mat[0] = 0.508273;
  mat[1] = 0.508273;
  mat[2] = 0.508273;
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
  glMaterialf(GL_FRONT, GL_SHININESS, 51.2 * 128.0);
}

void orange_material() {
  float mat[3];
  mat[0] = 0.0;
  mat[1] = 0.0;
  mat[2] = 0.0;
  mat[3] = 0.0;
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
  mat[0] = 0.8;
  mat[1] = 0.4;
  mat[2] = 0;
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
  mat[0] = 0.65;
  mat[1] = 0.6;
  mat[2] = 0.55;
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
  glMaterialf(GL_FRONT, GL_SHININESS, 0.25 * 128.0);
}
} // namespace gundam