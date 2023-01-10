#include "allmaterial.hpp"
#include <GLUT/glut.h>
#include <cmath>
namespace gundam {
class thigh {
  GLUquadricObj *cylinder = gluNewQuadric();
  GLUquadricObj *sphere = gluNewQuadric();

public:
  thigh() {
    gluQuadricDrawStyle(cylinder, GLU_FILL);
    gluQuadricNormals(cylinder, GLU_SMOOTH);
    gluQuadricTexture(cylinder, GL_TRUE);
  }

  void draw() {
    glPushMatrix();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glRotatef(-90, 1, 0, 0);
    white_material();
    gluCylinder(cylinder, 1, 1, 4, 10, 10);
    glPopMatrix();
  }
};
} // namespace gundam
