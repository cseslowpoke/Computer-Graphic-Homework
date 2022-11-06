#pragma once
#include "item.hpp"
#include <GL/glut.h>
#include <cmath>
#include <iostream>
namespace item {
class sword : public item {
  GLUquadricObj *cylinder = gluNewQuadric();
  GLUquadricObj *sphere = gluNewQuadric();

public:
  
};
} // namespace item
