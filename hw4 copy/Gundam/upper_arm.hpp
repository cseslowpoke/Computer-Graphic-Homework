
#include "allmaterial.hpp"
#include <GLUT/glut.h>
#include <cmath>
namespace gundam {
class upper_arm {
  GLUquadricObj *cylinder = gluNewQuadric();
  GLUquadricObj *sphere = gluNewQuadric();

public:
  upper_arm() {
    gluQuadricDrawStyle(cylinder, GLU_FILL);
    gluQuadricNormals(cylinder, GLU_SMOOTH);
    gluQuadricTexture(cylinder, GL_TRUE);
    gluQuadricDrawStyle(sphere, GLU_FILL);
    gluQuadricNormals(sphere, GLU_SMOOTH);
    gluQuadricTexture(sphere, GL_TRUE);
  }
  void draw() {
    glPushMatrix();
    green_material();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    gluSphere(sphere, 1, 10, 10);
    white_material();
    gluCylinder(cylinder, 0.6, 0.6, 2.3, 10, 10);
    glPopMatrix();
  }
};
} // namespace gundam
